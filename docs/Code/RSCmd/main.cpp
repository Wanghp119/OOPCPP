#include "RSImage.h"
#include <iostream>
using namespace std;

/*############ Remote Sensing Image Process Tools.############
# X �C Exit Exit �˳�����
# O �C Open ��Ӱ���ļ�
# D - Display ��ʾͼ��
# I �C Information �����ǰͼ���·�� ������ֵ �������� �������� ������ �͡����з�ʽ����Ϣ
# C �C Closed �رյ�ǰͼ��
# S �C Statistics ���ͼ������ͳ���� �����ļ�δ�� �������ʾ
# H �C Histogram ���ͼ���ֱ��ͼ
# ? �C Help �������Ϣ
# A �C Save as ���뱣����ļ�·�� �����ͼ��Ϊ�������ļ�
# R �C Rotate ͼ����ת������Ƕ���ʱ��
# Z �C Zoom ͼ�����ţ���������߳�
# F - Filter �����˲��ˣ�����˲���ͼ��
#################################################################*/

// ǰ������
void Usage();

int main()
{
	bool	bExit = false;
	char	cmd;
	CRSImage	orsimg;
	
	Usage();

	do
	{
		cout << "Input Command (? for help):";
		cin >> cmd;

		switch(cmd)
		{
		case 'o':
		case 'O':
			// �򿪺���
			orsimg.doOpen();
			break;
		case 'd':
		case 'D':
			orsimg.doDisplay();//��ʾͼ��
			break;
		//case ... for others..
		case 'c':
		case 'C':
			break;
		case 'x':
		case 'X':
			bExit = true;
			break;
		case '?':
			Usage();
			break;
		default:
			cout << "Input ? for help." << endl;
			break;
		}

	}while(!bExit);

	return 0;
}

// �������ʾ��Ϣ������������ʱ�������ʾ
void Usage()
{
	cout << "############ Remote Sensing Image Process Tools.############" << endl;
	cout << "# X �C Exit Exit �˳�����" << endl;
	cout << "# O �C Open ��Ӱ���ļ�" << endl;
	cout << "# D - Display ��ʾͼ��" << endl;
	cout << "# I �C Information �����ǰͼ���·�� ������ֵ �������� �������� ������ �͡����з�ʽ����Ϣ" << endl;
	cout << "# C �C Closed �رյ�ǰͼ��" << endl;
	cout << "# S �C Statistics ���ͼ������ͳ���� �����ļ�δ�� �������ʾ" << endl;
	cout << "# H �C Histogram ���ͼ���ֱ��ͼ" << endl;
	cout << "# ? �C Help �������Ϣ" << endl;
	cout << "# A �C Save as ���뱣����ļ�·�� �����ͼ��Ϊ�������ļ�" << endl;
	cout << "# R �C Rotate ͼ����ת������Ƕ���ʱ��" << endl;
	cout << "# Z �C Zoom ͼ�����ţ���������߳�" << endl;
	cout << "# F - Filter �����˲��ˣ�����˲���ͼ��" << endl;
	cout << "#################################################################" << endl;
}