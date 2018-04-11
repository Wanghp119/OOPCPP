#pragma once
#include "shape.h"
#include "MyPoint.h"
#include <iostream>
using namespace std;

class CRectangle : public CShape
{
public:
	CRectangle(double dx1=0.0f, double dy1=0.0f, double dx2=0.0f, double dy2=0.0f);
	~CRectangle(void);

	friend istream& operator>>(istream& is, CRectangle& r);
	friend ostream& operator<<(ostream& os, const CRectangle& r);

public:
	double GetArea();				//���
	double GetPerimer();			//�ܳ�
	virtual void Draw(CDC* pDC);	//����

private:
	double	m_dWidth;	//���
	double	m_dHeight;	//�߶�
	CMyPoint	m_pt1, m_pt2;
};

istream& operator>>(istream& is, CRectangle& r);
ostream& operator<<(ostream& os, const CRectangle& r);