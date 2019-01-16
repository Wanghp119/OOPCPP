#pragma once

#include <string>
using namespace std;

class CRSImage
{
public:
	CRSImage(void);
	~CRSImage(void);

	// Methods
	void doOpen();	//# O �C Open ��Ӱ���ļ�


protected:
	// image file path to Meta Data File Path
	string getMetaDataFilePath(const char*);

	// 1. Read Meta Data �C ֪��img��¼��ͼ�������
	bool ReadMetaData(const char*);	//string::c_str();
	
	// 2. New Arrays to store Image �C ��Ҫ������������Ŷ��ͼ���ͼ��
	bool NewArrays();

	// 3. Read Image Data �C ��img�ļ������������ȡ��ǰ������������
	bool ReadImageData(const char*);
};

/*
	void doDisplay();	//# D - Display ��ʾͼ��
	void doInfo();	//# I �C Information �����ǰͼ���·�� ������ֵ �������� �������� ������ �͡����з�ʽ����Ϣ
	void doClose();	//# C �C Closed �رյ�ǰͼ��
	void doStat();	//# S �C Statistics ���ͼ������ͳ���� �����ļ�δ�� �������ʾ
	void doHist();	//# H �C Histogram ���ͼ���ֱ��ͼ
	void doSaveas();	//# A �C Save as ���뱣����ļ�·�� �����ͼ��Ϊ�������ļ�
	void doRotate();	//# R �C Rotate ͼ����ת������Ƕ���ʱ��
	void doZoom();	//# Z �C Zoom ͼ�����ţ���������߳�
	void doFilter();	//# F - Filter �����˲��ˣ�����˲���ͼ��
*/