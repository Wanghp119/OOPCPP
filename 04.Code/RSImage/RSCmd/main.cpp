#include <iostream>
#include <string>
#include <sstream>
#include "RSImage.h"
#include "Windows.h"	//windows

using namespace std;

// ǰ�����������û�ȡ����̨���ھ��
// ��Ϊ��Win32ȫ�ֺ�������ʹ��extern "C"
extern "C" HWND WINAPI GetConsoleWindow();

void Usage();	//declaration forward

// ǰ����������ʾͼ��
void DisplayImage(CRSImage* pRSImg);

// ������
int main()
{
	Usage();	//Command�÷�

	char			cCmd;
	bool			bExit = false;
	string			strParam;
	CRSImage	rsImg;		//RSImage����

	//ѭ���������ֱ������'X'���˳�����
	do {
		cout << "Input a command: ";
		cin >> cCmd;	//����Menu

		switch(cCmd)
		{
		case 'X':	// Exit
		case 'x':
			bExit = true;
			break;

		case 'O':	// Open Image
		case 'o':
		    cout << "Input Image file path: ";
			cin >> strParam;
			rsImg.Open(strParam.c_str());
			break;

		case 'I':	// Print Image Info
		case 'i':
			rsImg.PrintInfo();
			break;

		case 'C':	// Close Image
		case 'c':
			rsImg.Close();
			break;

		case 'D':
		case 'd':
			if (rsImg.IsOpen())
				DisplayImage(&rsImg);
			else
				cerr << "Please Open image first." << endl;
			break;

		case 'S':	// Calculate Statistics
		case 's':
			rsImg.CalcStatistics();
			break;

		case 'H':	// Calculate Histogram
		case 'h':
			rsImg.Histogram();
			break;

		case '?':	// Help
			Usage();
			break;

		case 'A':	// Save As File
		case 'a':
			rsImg.Save(NULL);
			break;

		case 'R':	// Rotate-��ת
		case 'r':
			rsImg.Rotate(0.0f);
			break;

		case 'Z':	// Zoom-�Ŵ���С
		case 'z':
			rsImg.Zoom(0.0f);
			break;

		case 'F':	// Filter - �˲�
		case 'f':
			rsImg.Filter(NULL, 0);
			break;
		}
	}while(!bExit);

	return 0;
}


//===================================================================
// �˵���ʾ��������
//===================================================================
void Usage()
{
	cout << "############ Remote Sensing Image Process Tools.############\n";
	cout << "# X �C Exit Exit\t�˳�����" << endl;
	cout << "# O �C Open \t��Ӱ���ļ�" << endl;
	cout << "# I �C Information\t�����ǰͼ���·�� ������ֵ �������� �������� ������ �͡����з�ʽ����Ϣ" << endl;
	cout << "# C �CClosed\t�رյ�ǰͼ��" << endl;
	cout << "# S �C Statistics\t���ͼ������ͳ���� �����ļ�δ�� �������ʾ" << endl;
	cout << "# H �C Histogram\t���ͼ���ֱ��" << endl;
	cout << "# ? �C Help\t�������Ϣ" << endl;
	cout << "# A �C Save as\t���뱣����ļ�·�� �����ͼ��Ϊ�������ļ�" << endl;
	cout << "# R �C Rotate\tͼ����ת������Ƕ���ʱ��" << endl;
	cout << "# Z �C Zoom\tͼ�����ţ���������߳�" << endl;
	cout << "# F - Filter\t�����˲��ˣ�����˲���ͼ��" << endl;
	cout << "#################################################################" << endl;
}

//////////////////////////////////////////////////////////////////////////
// DisplayImage - ��ʾͼ�񵽿���̨����									//
// CRSImage* pRSImg - ͼ������ָ��										//
// ����ֵ - void														//
//////////////////////////////////////////////////////////////////////////
void DisplayImage(CRSImage* pRSImg)
{
	// �����ж�
	if (pRSImg==NULL)
		return;
	
	HWND	hwnd = NULL;//��þ��
	HDC		hdc = NULL;

	// ���ھ��ΪNULL������
	hwnd = GetConsoleWindow();
	if (hwnd == NULL)
		return;

	// �豸�����ķ���NULL�����򷵻�
	hdc = GetDC(hwnd);	
	if (hdc == NULL)
		return;

	int		i, j;	
	int		nBands = pRSImg->GetBands();		//����
	int		nSamples = pRSImg->GetSamples();	//��
	int		nLines = pRSImg->GetLines();		//��
	unsigned char***	pppData = pRSImg->GetDataBuffer();	//��ά����ͷָ��
	unsigned char**		ppRed = pppData[0];		//��ɫͨ���Ĳ���
	unsigned char**		ppGrn = nBands>2 ? pppData[1] : pppData[0];	//��ɫͨ���Ĳ���
	unsigned char**		ppBlu = nBands>2 ? pppData[2] : pppData[0];	//��ɫͨ���Ĳ���

	// �������أ���ʾͼ��
	for (i=0; i<nLines; i++)
	{
		for (j=0; j<nSamples; j++)
		{	//�����Ԫ���
			SetPixel(hdc,j, i, RGB(ppRed[i][j], ppGrn[i][j], ppBlu[i][j])); 	
		}
	}

	ReleaseDC(hwnd,hdc);
}
