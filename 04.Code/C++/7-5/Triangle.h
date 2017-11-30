#pragma once
#include "shape.h"

class CTriangle : public CShape
{
public:
	CTriangle(int x1=0, int y1=0, int x2=0, int y2=0, int x3=0, int y3=0);
	~CTriangle(void);

	virtual double GetArea();		//���
	virtual double GetPerimer();	//�ܳ�
	virtual void Draw(CDC* pDC);	//����ͼ��

	virtual POINT GetCenter();		//����λ��

	bool GetLen(double daryLen[]);	//�߳�
private:
	POINT	m_pt1, m_pt2, m_pt3;
};
