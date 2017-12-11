/*############ Remote Sensing Image Process Tools.############
# X �C Exit Exit �˳�����
# O �C Open ��Ӱ���ļ�
# D - Display ��ʾͼ��
# I �C Information �����ǰͼ���·�� ������ֵ �������� �������� ������ �͡����з�ʽ����Ϣ
# C �C Closed �رյ�ǰͼ��
# S �C Statistics ���ͼ������ͳ���� �����ļ�δ�� �������ʾ
# H �C Histogram ���ͼ���ֱ��
# ? �C Help �������Ϣ
# A �C Save as ���뱣����ļ�·�� �����ͼ��Ϊ�������ļ�
# R �C Rotate ͼ����ת������Ƕ���ʱ��
# Z �C Zoom ͼ�����ţ���������߳�
# F - Filter �����˲��ˣ�����˲���ͼ��
#################################################################*/

#include <iostream>
#include <string>
#include <sstream>
#include "RS2DImage.h"

using namespace std;


void Usage();	//declaration forward

// ������
int main()
{
	Usage();	//Command�÷�

	char			cCmd;
	bool			bExit = false;
	string			strParam;
	CRS2DImage		rsImg;		//RSImage����

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
			rsImg.Display();
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