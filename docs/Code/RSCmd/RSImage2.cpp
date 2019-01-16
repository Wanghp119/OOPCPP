#include "RSImage.h"
#include <iostream>
#include <string>
using namespace std;

CRSImage::CRSImage(void)
{
}


CRSImage::~CRSImage(void)
{
}

// Methods
//# O �C Open ��Ӱ���ļ�
void CRSImage::doOpen()
{
	cout << "Open()." << endl;
	//����Ӱ���ļ��򿪵�����ͼ��������

	// 1. Read Meta Data �C ֪��img��¼��ͼ�������
	// �˴���Ҫ������ÿ�����������롢�������
	// �����Ԫ�����ļ�����ҪԪ�����ļ���·������ô����Ҫ
	string	strImageFilePath;
	cout << "Input Image File Path:";
	cin >> strImageFilePath;

	// .img --> .hdr
	string		strMetaDataFilePath = getMetaDataFilePath(strImageFilePath.c_str());

	// bool ����Ƿ������ȷ
	if (!ReadMetaData(strMetaDataFilePath.c_str()))//string::c_str();
	{
		cerr << "Read Meta Data Failed." << endl;
		return;
	}
	//����ֵ��ʲô�أ���������lines,samples, bands ...
	// Think??? lines, samples, bands is member variables or local variables???

	// 2. New Arrays to store Image �C ��Ҫ������������Ŷ��ͼ���ͼ��
	if (!NewArrays())
	{
		cerr << "New Arrays Failed." << endl;
		return;
	}

	// 3. Read Image Data �C ��img�ļ������������ȡ��ǰ������������
	if (!ReadImageData(strImageFilePath.c_str()))
	{
		cerr << "Read Image Data Failed." << endl;
		return;
	}

	cout << "Open Image Success." << endl;
}


string CRSImage::getMetaDataFilePath(const char*)
{
	string		strPath = "";
	return strPath;
}

// 1. Read Meta Data �C ֪��img��¼��ͼ�������
bool CRSImage::ReadMetaData(const char* lpstrFilePath)//string::c_str();
{
	return false;
}

// 2. New Arrays to store Image �C ��Ҫ������������Ŷ��ͼ���ͼ��
bool CRSImage::NewArrays()
{
	return false;
}

// 3. Read Image Data �C ��img�ļ������������ȡ��ǰ������������
bool CRSImage::ReadImageData(const char* lpstrFilePath)
{
	return false;
}

/*

//# D - Display ��ʾͼ��
void CRSImage::doDisplay()
{

}

//# I �C Information �����ǰͼ���·�� ������ֵ �������� �������� ������ �͡����з�ʽ����Ϣ
void CRSImage::doInfo()
{
}

//# C �C Closed �رյ�ǰͼ��
void CRSImage::doClose()
{
}

//# S �C Statistics ���ͼ������ͳ���� �����ļ�δ�� �������ʾ
void CRSImage::doStat()
{
}	

//# H �C Histogram ���ͼ���ֱ��ͼ
void CRSImage::doHist()
{
}	

//# A �C Save as ���뱣����ļ�·�� �����ͼ��Ϊ�������ļ�
void CRSImage::doSaveas()
{
}

//# R �C Rotate ͼ����ת������Ƕ���ʱ��
void CRSImage::doRotate()
{
}

//# Z �C Zoom ͼ�����ţ���������߳�
void CRSImage::doZoom()
{
}	

//# F - Filter �����˲��ˣ�����˲���ͼ��
void CRSImage::doFilter()
{
}
*/