/************************************************************************/
/* ������                                                               */
/* ��������������������												*/
/* Wang Hongping 2017.3.7												*/
/************************************************************************/
#pragma once

#include <iostream>
using namespace std;

class CComplex
{
public:
	// ���캯������������
	CComplex(double r=0.0f, double i=0.0f);
	~CComplex(void);

	// ���������
	CComplex operator-();	//��������
	bool operator<(const CComplex& c);	//С�ڸ�������

	// ���롢���������
	friend ostream& operator<<(ostream& os, const CComplex& c);
	friend istream& operator>>(istream& is, CComplex& c);

private:
	// ��Ա������ʵ��+�鲿i
	double	m_dblReal;
	double	m_dblImage;
};


// ���롢������ӿڶ���
ostream& operator<<(ostream& os, const CComplex& c);
istream& operator>>(istream& is, CComplex& c);