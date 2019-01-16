#include "RSImage.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include "Windows.h"

using namespace std;

// ǰ�����������û�ȡ����̨���ھ��
// ��Ϊ��Win32ȫ�ֺ�������ʹ��extern "C"
extern "C" HWND WINAPI GetConsoleWindow();


CRSImage::CRSImage(void)
{
	//��ʼ��
	m_nSamples = 0;
	m_nLines = 0;
	m_nBands = 0;
	m_eInterleave = BSQ;
	m_nDataType = 0; 
	m_pppData = nullptr;
}


CRSImage::~CRSImage(void)
{
	Close();
}

void CRSImage::Close()
{
		if (m_pppData != nullptr)
	{
		for (int i=0; i<m_nBands; ++i)
		{
			for (int j=0; j<m_nLines; ++j)
			{
				if (m_pppData[i][j] != nullptr)
				{
					delete[] m_pppData[i][j];

				}
			}

			if (m_pppData[i] != nullptr)
			{
					delete[] m_pppData[i];
					m_pppData[i] = nullptr;
			}
		}

		delete[] m_pppData;
		m_pppData = nullptr;
	}
}

// Open Image File
void
CRSImage::doOpen()
{
	//0. �ļ�·�� *.img
	string		strImageFilePath;
	cout << "Input Image File Path: ";
	cin >> strImageFilePath;

	//Ԫ�����ļ���·������
	string		strMetaDataPath;
	strMetaDataPath = getMetaDataPath(strImageFilePath.c_str());

	//1. ��Ԫ�����ļ�.hdr,��ȡͼ����С��С����Ρ����з�ʽ
	if (!ReadMetaData(strMetaDataPath.c_str()))
	{
		cerr << "Read Meta Data Failed." << endl;
		return;
	}

	//2. Ϊͼ����������ڴ�ռ�
	if (!NewImageArray())
	{
		cerr << "New Image Array Failed." << endl;
		return;
	}

	//3. ��ȡͼ���ļ�
	if (!ReadImageData(strImageFilePath.c_str()))
	{
		cerr << "Read Image Data Failed." << endl;
		return;
	}

	// Open Image Success.
	cout << "Read Image Success." << endl;

	return;
}

//��ͼ���ļ�·��-->Ԫ�����ļ�·��
string CRSImage::getMetaDataPath(const char* lpstrPath)
{
	string		strPath = lpstrPath;
	int			pos = strPath.rfind('.');	//����'.'��λ��

	//
	if (pos >= 0)	//�������'.'����'.'֮ǰ���ַ�����ȡ����
		strPath = strPath.substr(0, pos);

	strPath += ".hdr";	//����".hdr"���ɵõ�Ԫ�����ļ�·��

	return strPath;
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

	ifs.open(lpstrMetaFilePath, ios_base::in);
    if (!ifs.is_open())
        return false;

    while(!ifs.eof())   //end of file
    {
        getline(ifs, strLine);	//��ȡһ�У����Ե����£�����ȡ������

        ss.clear();
        ss.str(strLine);    //"samples = 640"
        ss >> strSubTxt;

        if (strSubTxt == "samples")
        {
            ss >> strSubTxt >> m_nSamples;	//��ȡ�ı���Ҫ���棬����Ҫ�����Ա����
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


bool CRSImage::NewImageArray()				//��������
{
	Close();	//�ȹر�ͼ��

	// ֪����ͼ����С��кͲ��Σ����Է������������ͼ��
	typedef unsigned char	ImgType;
	
	m_pppData = new ImgType**[m_nBands];
	if (m_pppData == nullptr)
		return false;

	for (int i=0; i<m_nBands; ++i)
	{
		m_pppData[i] = new ImgType*[m_nLines];
		if (m_pppData[i] == nullptr)
			return false;

		for (int j=0; j<m_nLines; ++j)
		{
			m_pppData[i][j] = new ImgType[m_nSamples];
			if (m_pppData[i][j] == nullptr)
				return false;
		}
	}

	// ����Ȼ������Ҫ���ô��ڣ����ں��洦���ʶ�Ҫ����Ϊ��Ա����

	return true;
}

bool CRSImage::ReadImageData(const char* lpstrPath)	//��ȡͼ���ļ�.img to ����
{
	bool		bFlag = false;

	// ֻչʾ��BSQ��ȡ
	switch(m_eInterleave)
	{
	case BSQ:
		ReadBsqImage(lpstrPath);
		break;
	case BIL:
		ReadBilImage(lpstrPath);
		break;
	case BIP:
		ReadBipImage(lpstrPath);
		break;
	default:
		bFlag = false;
		break;
	}

	return true;
}

//��ȡBSQ
bool CRSImage::ReadBsqImage(const char* lpstrPath)
{
	ifstream	ifs(lpstrPath, ios::binary);
	if (!ifs)
		return false;

	for (int i=0; i<m_nBands; ++i)
	{
		for (int j=0; j<m_nLines; ++j)
		{
			ifs.read((char*)m_pppData[i][j], sizeof(unsigned char)*m_nSamples);
		}
	}

	ifs.close();
	return true;
}


bool CRSImage::ReadBilImage(const char* lpstrPath)		//��ȡBIL
{
	return false;
}

bool CRSImage::ReadBipImage(const char* lpstrPath)	//��ȡBIP
{
	return false;
}

//��ʾͼ��
void CRSImage::doDisplay()
{
	//0. �ж��ļ��Ƿ�򿪣��ܷ���ʾ
	if (m_pppData == nullptr || m_nLines<1 || m_nSamples < 1 || m_nBands < 1)
	{
		cerr << "Unable Image." <<endl;
		return;
	}

	//1. ������ʾ��ͨ��
	int		r, g, b;
	cout << "Input R G B bands base 0: ";
	cin >> r >> g >> b;
	if (r<0 || r>=m_nBands ||
		g<0 || g>=m_nBands ||
		b<0 || b>=m_nBands)
	{
		cerr << "Input Invalid bands no" << endl;
		return;
	}

	//2.����ͼ��
	DrawImage(r, g, b);
}

void CRSImage::DrawImage(int r, int g, int b)
{
	HWND	hWnd = GetConsoleWindow();

	if (hWnd == 0L)
	{
		cerr << "Get Window failed." << endl;
		return;
	}

	HDC		hDC = GetDC(hWnd);
	if (hDC == 0L)
	{
		cerr << "Get DC Failed." << endl;
		return;
	}

	for (int i=0; i<m_nLines; ++i)
	{
		for (int j=0; j<m_nSamples; ++j)
			SetPixel(hDC, j, i, RGB(m_pppData[r][i][j], m_pppData[g][i][j], m_pppData[b][i][j]));
	}
	return;
}