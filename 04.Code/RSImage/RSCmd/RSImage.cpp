/************************************************************************/
/* File: RSImage.cpp                                                    */
/* class CRSImage implementation										*/
/************************************************************************/

#include "RSImage.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>
#include <iomanip>
#include "Windows.h"	//windows

using namespace std;


// ǰ�����������û�ȡ����̨���ھ��
// ��Ϊ��Win32ȫ�ֺ�������ʹ��extern "C"
extern "C" HWND WINAPI GetConsoleWindow();

/************************************************************************/
/* ���캯��                                                             */
/************************************************************************/
CRSImage::CRSImage()
{
	m_pppData = NULL;
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
	if (m_pppData != NULL)
	{
		int			i, j;

		for (i=0; i<m_nBands; ++i)
		{
			for (j=0; j<m_nLines; ++j)
			{
			    if (0UL != m_pppData[i][j])
                {
                    delete[] m_pppData[i][j];
                    m_pppData[i][j] = 0UL;
                }
			}

			if (0UL != m_pppData[i])
			{
			    delete[] m_pppData[i];
			    m_pppData[i] = 0UL;
			}
		}

		delete[] m_pppData;	//delete 

		m_pppData = NULL;
		m_nBands = 0;
		m_nLines = 0;
		m_nSamples = 0;
	}
}

/************************************************************************/
/* ���¹���δ����ʵ��                                                   */
/************************************************************************/
void	CRSImage::PrintInfo()
{
	if (!IsOpen())
	{
		cerr << "None Opened Image." << endl;
		return;
	}

	cout << "Bands = " << m_nBands << endl;		//������
	cout << "Lines = " << m_nLines << endl;		//����
	cout << "Samples = " << m_nSamples << endl;		//����
	switch(m_eInterleave)
	{
	case BSQ:
		cout << "Interleave = BSQ" << endl;
		break;
	case BIL:
		cout << "Interleave = BIL" << endl;
		break;
	case BIP:
		cout << "Interleave = BIP" << endl;
		break;
	default:
		break;
	}

	cout << "Data Type = " << m_nDataType << endl;		//��������
}

int		CRSImage::CalcStatistics()
{
	// Min, Max, Mean, Variance
	if (!IsOpen())
	{
		cerr << "None Opened Image." << endl;
		return -1;
	}

	int		i, j, k;
	double*	dpMin = new double[m_nBands];
	double*	dpMax = new double[m_nBands];
	double*	dpMean = new double[m_nBands];
	double*	dpVar = new double[m_nBands];

	for (i=0; i<m_nBands; ++i)	//����
	{
		dpMin[i] = m_pppData[i][0][0];
		dpMax[i] = m_pppData[i][0][0];
		dpMean[i] = 0.0f;
		dpVar[i] = 0.0f;

		for (j=0; j<m_nLines; ++j)	//����
		{
			for (k=0; k<m_nSamples; ++k)	////����
			{
				dpMin[i] = min(dpMin[i], m_pppData[i][j][k]);
				dpMax[i] = max(dpMax[i], m_pppData[i][j][k]);
				dpMean[i] += m_pppData[i][j][k];
			}
		}
		dpMean[i] /= (1L*m_nLines*m_nSamples);	//Mean

		// Variance
		for (j=0; j<m_nLines; ++j)	//����
		{
			for (k=0; k<m_nSamples; ++k)	////����
			{
				dpVar[i] += pow(m_pppData[i][j][k]-dpMean[i],2);
			}
		}
		dpVar[i] = sqrt(dpVar[i]/(m_nLines*m_nSamples-1L));
	}

	// Display Statistics
	for (i=0; i<m_nBands; ++i)	//����
	{		
		cout << "Statics of Band " << i+1 << endl;
		cout << "Min = " << dpMin[i] << endl;
		cout << "Max = " << dpMax[i] << endl;
		cout << "Mean = " << dpMean[i] << endl;
		cout << "Variance = " << dpVar[i] << endl;
		cout << "###########################" << endl;
	}

	if (dpMin)	delete[] dpMin;
	if (dpMax)	delete[] dpMax;
	if (dpMean) delete[] dpMean;
	if (dpVar)	delete[] dpVar;
	return 0;
}

void	CRSImage::OnHistogram()
{
	int		nHistograms[256];
	int		nCount;
	int		i;
	for (i=0; i<m_nBands; ++i)
	{
		cout << "############# Band " << i+1 << " Histograms ###########" << endl;
		nCount = CalcHistogram(i, nHistograms);

		DrawHistogram(nHistograms, nCount);
	}
}


void	CRSImage::Rotate(float fAngle)
{
}

void	CRSImage::Zoom(float fZoom)
{
}

void	CRSImage::OnFilter()
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
    int     i, j;

    m_pppData = new DataType**[m_nBands];
    if (m_pppData == NULL)  return false;

    for (i=0; i<m_nBands; i++)
        m_pppData[i] = 0UL;

    for (i=0; i<m_nBands; ++i)
    {
        m_pppData[i] = new DataType*[m_nLines];
        if (m_pppData[i] == NULL)   return false;

        for (j=0; j<m_nLines; ++j)
            m_pppData[i][j] = 0UL;

        for (j=0; j<m_nLines; ++j)
        {
            m_pppData[i][j] = new DataType[m_nSamples];
        }
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
    int*        ptrBuff = NULL;
    ifs.open(lpstrImgFilePath, ios::binary);	//���������ļ���

    if (ifs.is_open())	//�ж��Ƿ�򿪳ɹ�
    {
        switch(m_eInterleave)	//���ݴ洢���з�ʽ
        {
        case BSQ:	//���������У�һ�������ڰ�������
            for (i=0; i<m_nBands && !ifs.eof(); i++)
            {
                for (j=0; j<m_nLines && !ifs.eof(); j++)
                {
                    ifs.read((char*)m_pppData[i][j], sizeof(DataType)*m_nSamples);
                }
            }

            // �ж��Ƿ������Ӧ�е��к�����
            if (i<m_nBands || j<m_nLines)
                bFlag = false;
            break;
        case BIL:	//���������У��������ȣ����ΰ���������
            for (i=0; i<m_nLines && !ifs.eof(); i++)
            {
                for (j=0; j<m_nBands && !ifs.eof(); j++)
                {
                    ifs.read((char*)m_pppData[j][i], sizeof(DataType)*m_nSamples);
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
                    m_pppData[j][i/m_nLines][i%m_nLines] = ptrBuff[j];
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
// CalcHistogram - ����ĳ������ͼ���ֱ��ͼ								//
// Input:																//
//	int nBandIdx - ͼ�񲨶Σ�base 0										//
//	int* pHistograms - ֱ��ͼ����										//
// ����ֵ - int ֱ��ͼ�������Ч��Χ��0--Max��							//
//////////////////////////////////////////////////////////////////////////
int CRSImage::CalcHistogram(int nBandIdx, int* pHistograms)
{
	if (!IsOpen())
	{
		cerr << "Unable Open Image." << endl;
		return 0;
	}

	if (nBandIdx<0 || nBandIdx>=m_nBands)
	{
		cerr << "Band Index is Invalid." << endl;
		return 0;
	}

	if (pHistograms==NULL)
	{
		cerr << "Input Parameter is invalid." << endl;
		return 0;
	}

	memset(pHistograms, 0, sizeof(int)*256);

	int		i, j;
	for (i=0; i<m_nLines; ++i)
	{
		for (j=0; j<m_nSamples; ++j)
		{
			pHistograms[m_pppData[nBandIdx][i][j]]++;
		}
	}

	for (i=255; i>=0; --i)
		if (pHistograms[i]>0)
			break;
	return i+1;
}


//////////////////////////////////////////////////////////////////////////
// DrawHistogram - ����ĳ������ͼ���ֱ��ͼ								//
// Input:																//
//	int* pHistograms - ֱ��ͼ����										//
//	int n - �������													//
// ����ֵ - void														//
//////////////////////////////////////////////////////////////////////////
void CRSImage::DrawHistogram(int* pHistograms, int n)
{
	int		i, j;
	int		nMaxHistVal = 0;
	for (i=0; i<n; ++i)
		nMaxHistVal = max(nMaxHistVal, pHistograms[i]);

	int		nYMax = (100L*nMaxHistVal)/(m_nLines*m_nSamples);
	for (i=0; i<nYMax+2; ++i)
	{
		// ��������
		if (0 == i)
		{
			cout << "   A";
		}
		else
		{
			cout.unsetf(ios::left);
			cout.fill(' ');
			cout.width(2);
			cout << (nYMax+1-i);
			cout << "%|";
		}

		// ���� * 
		for (j=0; j<n; ++j)
		{
			if ((100L*pHistograms[j])/(m_nLines*m_nSamples) == nYMax+2-i)
				cout << "*";
			else
				cout << " ";
		}
		cout << endl;
	}

	// ���ƺ���
	cout << "   ";
	cout.setf(ios::left);
	cout.fill('-');
	for (j=0; j<n; ++j)
	{
		if (j%10==0)
		{
			cout.width(10);	
			cout << j;
		}
	}
	cout << "->" << endl;
	
	return;
}


void	CRSImage::Filter(double* dFilterKernel, int nSize)
{
}


//////////////////////////////////////////////////////////////////////////
// Display - ��ʾͼ�񵽿���̨����										//
// ����ֵ - void														//
//////////////////////////////////////////////////////////////////////////
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
