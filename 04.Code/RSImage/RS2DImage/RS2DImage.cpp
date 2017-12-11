/************************************************************************/
/* File: RSImage.cpp                                                    */
/* class CRS2DImage implementation										*/
/************************************************************************/

#include "RS2DImage.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include "Windows.h"	//windows

using namespace std;

// ǰ�����������û�ȡ����̨���ھ��
// ��Ϊ��Win32ȫ�ֺ�������ʹ��extern "C"
extern "C" HWND WINAPI GetConsoleWindow();


/************************************************************************/
/* ���캯��                                                             */
/************************************************************************/
CRS2DImage::CRS2DImage()
{
	m_ppData = NULL;
	m_nBands = 0;
	m_nLines = 0;
	m_nSamples = 0;
}

/************************************************************************/
/* �������캯����δʵ��                                                 */
/************************************************************************/
CRS2DImage::CRS2DImage(const CRS2DImage& img)
{

}

/************************************************************************/
/* ��������                                                             */
/* �ͷŷ��������														*/
/************************************************************************/
CRS2DImage::~CRS2DImage()
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
bool	CRS2DImage::Open(const char* lpstrPath)
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
bool	CRS2DImage::Save(const char* lpstrPath)
{
	// Write
	return false;
}

/************************************************************************/
/* Close - �ͷ�ͼ���ڴ�                                                 */
/************************************************************************/
void	CRS2DImage::Close()
{
	// ע���ͷŵ�˳����new��˳�����෴��
	if (m_ppData != NULL)
	{
		int			i;

		for (i=0; i<m_nBands; ++i)
		{
			if (0UL != m_ppData[i])
			{
			    delete[] m_ppData[i];
			    m_ppData[i] = 0UL;
			}
		}

		delete[] m_ppData;	//delete 

		m_ppData = NULL;
		m_nBands = 0;
		m_nLines = 0;
		m_nSamples = 0;
	}
}

/************************************************************************/
/* ���¹���δ����ʵ��                                                   */
/************************************************************************/
void	CRS2DImage::PrintInfo()
{
}

int		CRS2DImage::CalcStatistics()
{
	return 0;
}

int		CRS2DImage::Histogram()
{
	return 0;
}

void	CRS2DImage::Rotate(float fAngle)
{
}

void	CRS2DImage::Zoom(float fZoom)
{
}

void	CRS2DImage::Filter(double* dFilterKernel, int nSize)
{
}

/////////////////////////////////////////////////////////////////////
// ��ȡԪ�����ļ�
/////////////////////////////////////////////////////////////////////
bool	CRS2DImage::ReadMetaData(const char* lpstrMetaFilePath)
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
bool	CRS2DImage::InitBuffer(void)
{
    int     i;

    m_ppData = new DataType*[m_nBands];
    if (m_ppData == NULL)  return false;

    for (i=0; i<m_nBands; i++)
        m_ppData[i] = 0UL;

    for (i=0; i<m_nBands; ++i)
    {
        m_ppData[i] = new DataType[m_nLines*m_nBands];
        if (m_ppData[i] == NULL)   return false;      
    }

	return true;
}

/************************************************************************/
/* ReadImgData - ���������ļ�                                           */
/* const char* lpstrImgFilePath - �ļ�·��								*/
/************************************************************************/
bool	CRS2DImage::ReadImgData(const char* lpstrImgFilePath)
{
    bool        bFlag = true;
    int         i, j;
    ifstream    ifs;				//�ļ���
    int*        ptrBuff = NULL;
    ifs.open(lpstrImgFilePath, ios::binary);	//���������ļ���

    if (ifs.is_open())	//�ж��Ƿ�򿪳ɹ�
    {
        switch(m_eInterleave)	//���ݴ洢���з�ʽ
        {
        case BSQ:	//���������У�һ�������ڰ�������
            for (i=0; i<m_nBands && !ifs.eof(); i++)
            {
				ifs.read((char*)m_ppData[i], sizeof(DataType)*m_nSamples*m_nLines);
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
                    ifs.read((char*)m_ppData[j][i*m_nSamples], sizeof(DataType)*m_nSamples);
                }
            }
            // �����Ƿ�����
            if (i<m_nLines || j<m_nBands)
                bFlag = false;
            break;
        case BIP:	//����Ԫ��������
            ptrBuff = new int[m_nBands];
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
// Display - ��ʾͼ�񵽿���̨����										//
// ����ֵ - void														//
//////////////////////////////////////////////////////////////////////////
void CRS2DImage::Display(int nRedBand, int nGrnBand, int nBluBand)
{	
	// δͼ�����ݣ��޷���ʾ
	if (m_ppData == NULL || m_nBands<1)
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
			SetPixel(hdc,j, i, RGB(m_ppData[nRedBand][i*m_nSamples+j], m_ppData[nGrnBand][i*m_nSamples+j], m_ppData[nBluBand][i*m_nSamples+j])); 	
		}
	}
	
	ReleaseDC(hwnd,hdc);
}
