/************************************************************************/
/* File: RSImage.cpp                                                    */
/* class CRSImage implementation										*/
/************************************************************************/

#include "RSImage.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>

using namespace std;


// ǰ�����������û�ȡ����̨���ھ��
// ��Ϊ��Win32ȫ�ֺ�������ʹ��extern "C"
//extern "C" HWND WINAPI GetConsoleWindow();

/************************************************************************/
/* ���캯��                                                             */
/************************************************************************/
CRSImage::CRSImage()
{
//	m_pppData = NULL;
    m_ppData = NULL;
	m_nBands = 0;
	m_nLines = 0;
	m_nSamples = 0;
}

/************************************************************************/
/* �������캯����δʵ��                                                 */
/************************************************************************/
CRSImage::CRSImage(const CRSImage& img)
{

}

/************************************************************************/
/* ��������                                                             */
/* �ͷŷ��������														*/
/************************************************************************/
CRSImage::~CRSImage()
{
	Close();
}

//----------------------------------------------------------------------//
//----------------------------- Operation Methods ----------------------//
//----------------------------------------------------------------------//

/************************************************************************/
/* ���ܣ�Open - ��ͼ���ļ�                                            */
/* ������ const char* lpstrPath - �����ļ�·��							*/
/* ����ֵ�� bool �ɹ�-true/ʧ��-false									*/
/************************************************************************/
/* ��ʾ�������ļ�Ϊtest.img �� test.hdr������test.img Ϊ�����ļ����洢ͼ��
   DN��test.hdrΪԪ�����ļ����ı��ļ�������¼ͼ����С��С����Ρ��������͡�
   ��ȡ�ļ�����˼��ָ���������ļ���Ӳ���ϣ���ȡ���ڴ��еĹ��̡�			*/
bool	CRSImage::Open(const char* lpstrPath)
{
	// �������
	if (NULL == lpstrPath)
		return false;

	// 1. Read Meta Data
	string		strMetaFilePath = lpstrPath;	//Ԫ�����ļ��������ļ�ͬ������׺Ϊ.hdr
	int				pos = strMetaFilePath.rfind('.');
	if (pos>=0)
    {
        strMetaFilePath = strMetaFilePath.substr(0, pos);
    }
	strMetaFilePath.append(".hdr");		//�滻��׺Ϊ.hdr

	// ��Ԫ�����ı��ļ�
	if (!ReadMetaData(strMetaFilePath.c_str()))
	{
		cerr << "Read Meta Data Failed." << endl;
		return false;
	}

	// 2. Initialize Buffer
	// ������ά���飬����ͼ��Ĳ��Ρ��С���
	if (!InitBuffer())
	{
		cerr << "Initialize Buffer Failed." << endl;
		return false;
	}

	// 3. Read File
	// �������ļ��������ƣ���ע������˳��
	if (!ReadImgData(lpstrPath))
	{
		cerr << "Read Image Data Failed." << endl;
		return false;
	}

	return true;
}

/************************************************************************/
/* Save - �����ļ�������ļ��Ĺ����෴��δʵ��                          */
/************************************************************************/
bool	CRSImage::Save(const char* lpstrPath)
{
	// Write
	return false;
}

/************************************************************************/
/* Close - �ͷ�ͼ���ڴ�                                                 */
/************************************************************************/
void	CRSImage::Close()
{
    // ע���ͷŵ�˳����new��˳�����෴��
    if (m_ppData)
    {
        for (int i=0; i<m_nBands; i++)
        {
            if (m_ppData[i])
                delete[] m_ppData[i];
        }

        delete[] m_ppData;
    }

    m_ppData = NULL;
    m_nBands = 0;
    m_nLines = 0;
    m_nSamples = 0;
}

/************************************************************************/
/* ���¹���δ����ʵ��                                                   */
/************************************************************************/
void	CRSImage::PrintInfo()
{
}

int		CRSImage::CalcStatistics()
{
	return 0;
}

int		CRSImage::Histogram()
{
	return 0;
}

void	CRSImage::Rotate(float fAngle)
{
}

void	CRSImage::Zoom(float fZoom)
{
}

void	CRSImage::Filter(double* dFilterKernel, int nSize)
{
}

/////////////////////////////////////////////////////////////////////
// ��ȡԪ�����ļ�
/////////////////////////////////////////////////////////////////////
bool	CRSImage::ReadMetaData(const char* lpstrMetaFilePath)
{
    ifstream    ifs;
    string      strLine;
    string      strSubTxt;
    stringstream    ss;

    char        sBuff[260];

	ifs.open(lpstrMetaFilePath, ios_base::in);
    if (!ifs.is_open())
        return false;

    while(!ifs.eof())   //end of file
    {
        ifs.getline(sBuff, 260);
        strLine = sBuff;

        ss.clear();
        ss.str(strLine);    //"samples = 640"
        ss >> strSubTxt;

        if (strSubTxt == "samples")
        {
            ss >> strSubTxt >> m_nSamples;
        }
        else if (strSubTxt == "lines")
        {
            ss >> strSubTxt >> m_nLines;
        }
        else if (strSubTxt == "bands")
        {
            ss >> strSubTxt >> m_nBands;
        }
        else if (strSubTxt == "interleave")
        {
            ss >> strSubTxt >> strSubTxt;
            if (strSubTxt == "bsq")
            {
                m_eInterleave = BSQ;
            }
            else if (strSubTxt == "bip")
            {
                m_eInterleave = BIP;
            }
            else if (strSubTxt == "bil")
            {
                m_eInterleave = BIL;
            }
            else
            {
                // blank
            }
        }
        else if (strSubTxt == "data")
        {
            ss >> strSubTxt;
            if(strSubTxt == "type")
            {
                ss >> strSubTxt >> m_nDataType;
            }
        }
        else
        {
            // blank
        }
    }

	return true;
}

/************************************************************************/
/* InitBuffer - �����ڴ�                                                */
/* �����Ρ��е�˳��������ݴ洢��Ԫ��ʹ�õ���3ά���飬ע����䷽ʽ��	*/
/************************************************************************/
bool	CRSImage::InitBuffer(void)
{
    int     i;

    m_ppData = new DataType* [m_nBands];
    if (m_ppData == NULL)   return false;

    for (i=0; i<m_nBands; i++)
    {
        m_ppData[i] = new DataType[m_nLines*m_nSamples];
    }

	return true;
}

/************************************************************************/
/* ReadImgData - ���������ļ�                                           */
/* const char* lpstrImgFilePath - �ļ�·��								*/
/************************************************************************/
bool	CRSImage::ReadImgData(const char* lpstrImgFilePath)
{
    bool        bFlag = true;
    int         i, j;
    ifstream    ifs;				//�ļ���
    DataType*        ptrBuff = NULL;
    ifs.open(lpstrImgFilePath, ios::binary);	//���������ļ���

    if (ifs.is_open())	//�ж��Ƿ�򿪳ɹ�
    {
        switch(m_eInterleave)	//���ݴ洢���з�ʽ
        {
        case BSQ:	//���������У�һ�������ڰ�������
            for (i=0; i<m_nBands && !ifs.eof(); i++)
            {
                ifs.read((char*)m_ppData[i], sizeof(DataType)*m_nLines*m_nSamples);
            }

            // �ж��Ƿ������Ӧ�е��к�����
            if (i<m_nBands)
                bFlag = false;
            break;
        case BIL:	//���������У��������ȣ����ΰ���������
            for (i=0; i<m_nLines && !ifs.eof(); i++)
            {
                for (j=0; j<m_nBands && !ifs.eof(); j++)
                {
                    ifs.read((char*)(m_ppData[j]+i*m_nSamples), sizeof(DataType)*m_nSamples);
                }
            }
            // �����Ƿ�����
            if (i<m_nLines || j<m_nBands)
                bFlag = false;
            break;
        case BIP:	//����Ԫ��������
            ptrBuff = new DataType[m_nBands];
            if (ptrBuff == NULL)
                bFlag = false;

            for (i=0; i<m_nSamples*m_nLines && !ifs.eof(); i++)
            {
                ifs.read((char*)ptrBuff,sizeof(DataType)*m_nBands);

                for (j=0; j<m_nBands; j++)
                {
                    m_ppData[j][i] = ptrBuff[j];
                }
            }
            delete[] ptrBuff;

			// ��������Ƿ������
            if (i<m_nSamples*m_nLines)
                bFlag = false;
            break;
        }

        ifs.close();	//�ر��ļ�����סһ��Ҫ�رգ�
    }

    return bFlag;
}

//////////////////////////////////////////////////////////////////////////
// toQImage - Transform DataBuffer to QImage    						//
// ����ֵ - QImage														//
//////////////////////////////////////////////////////////////////////////
QImage  CRSImage::toQImage(int iR, int iG, int iB, EDT eDispType)
{
    QImage      qImage;

    if (!this->IsOpen() || iR<0 || iG<0 || iB<0 ||
        iR>=m_nBands || iG>=m_nBands || iB>=m_nBands)
    {
        return qImage;
    }

    // �������
    switch(eDispType)
    {
    case EDT_Normal:
        normalImage(iR, iG, iB);
        break;
    case EDT_Linear:
        linearImage(iR, iG, iB);
        break;
    default:
        normalImage(iR, iG, iB);
        break;
    }

    // ����QImage����
    qImage = QImage((const unsigned char*)(m_aryDispBuff.data()),
                    m_nSamples, m_nLines, QImage::Format_RGB888);

    return qImage;
}

void CRSImage::normalImage(int iR, int iG, int iB)
{
    // ͼ������
    int		iBytesLine = (m_nSamples*24+31) / 32 * 4;	//ͼ���line,��4�ֽڶ���...
    m_aryDispBuff.resize(m_nLines*iBytesLine);
    m_aryDispBuff.fill(0);

    int     i, j, n=0, k=0;
    for (i=0; i<m_nLines; i++)
    {
        for (j=0; j<m_nSamples; j++)
        {
            m_aryDispBuff[k++] = m_ppData[iR][n];
            m_aryDispBuff[k++] = m_ppData[iG][n];
            m_aryDispBuff[k++] = m_ppData[iB][n++];
        }
        while(k%4) {k++;}   //4 bytes align
    }
}

void CRSImage::linearImage(int iR, int iG, int iB)
{
    // ͼ������
    int		iImageWidth = (m_nSamples*8+31) / 32 * 4;	//ͼ��Ŀ��,��4�ֽڶ���...
    m_aryDispBuff.resize(m_nLines*iImageWidth*3);
    m_aryDispBuff.fill(0);

    unsigned char     iMin[3], iMax[3];
    int     i, j, k, n;

    iMin[0] = iMax[0] = m_ppData[iR][0];
    iMin[1] = iMax[1] = m_ppData[iG][0];
    iMin[2] = iMax[2] = m_ppData[iB][0];
    for (i=0; i<m_nLines*m_nSamples; i++)
    {
        iMin[0] = min(iMin[0], m_ppData[iR][i]);
        iMin[1] = min(iMin[1], m_ppData[iG][i]);
        iMin[2] = min(iMin[2], m_ppData[iB][i]);
        iMax[0] = max(iMax[0], m_ppData[iR][i]);
        iMax[1] = max(iMax[1], m_ppData[iG][i]);
        iMax[2] = max(iMax[2], m_ppData[iB][i]);
    }

    n = k = 0;
    for (i=0; i<m_nLines; i++)
    {
        for (j=0; j<m_nSamples; j++)
        {
            m_aryDispBuff[k++] = 255L*(m_ppData[iR][n] - iMin[0])/(iMax[0]-iMin[0]);
            m_aryDispBuff[k++] = 255L*(m_ppData[iG][n] - iMin[1])/(iMax[1]-iMin[1]);
            m_aryDispBuff[k++] = 255L*(m_ppData[iB][n] - iMin[2])/(iMax[2]-iMin[2]);
        }
        while(k%4) {k++;}   //4 bytes align
    }
}
//////////////////////////////////////////////////////////////////////////
// Display - ��ʾͼ�񵽿���̨����										//
// ����ֵ - void														//
//////////////////////////////////////////////////////////////////////////
/// \brief CRSImage::Display
/// \param nRedBand
/// \param nGrnBand
/// \param nBluBand
/*
void CRSImage::Display(int nRedBand, int nGrnBand, int nBluBand)
{	
	// δͼ�����ݣ��޷���ʾ
	if (m_pppData == NULL || m_nBands<1)
		return;

	HWND	hwnd = NULL;//��þ��
	HDC		hdc = NULL;
	int		i, j;

	// ���ھ��ΪNULL������
	hwnd = GetConsoleWindow();
	if (hwnd == NULL)
		return;
	
	// �豸�����ķ���NULL�����򷵻�
	hdc = GetDC(hwnd);	
	if (hdc == NULL)
		return;

	//RGB����, �����Ϸ������õ�һ��������Ϊȱʡֵ
	nRedBand = nRedBand<0||nRedBand>=m_nBands ? 0 : nRedBand;
	nGrnBand = nGrnBand<0||nGrnBand>=m_nBands ? 0 : nGrnBand;
	nBluBand = nBluBand<0||nBluBand>=m_nBands ? 0 : nBluBand;

	// �������أ���ʾͼ��
	for (i=0; i<m_nLines; i++)
	{
		for (j=0; j<m_nSamples; j++)
		{	//�����Ԫ���
			SetPixel(hdc,j, i, RGB(m_pppData[nRedBand][i][j], m_pppData[nGrnBand][i][j], m_pppData[nBluBand][i][j])); 	
		}
	}
	
	ReleaseDC(hwnd,hdc);
}
*/
