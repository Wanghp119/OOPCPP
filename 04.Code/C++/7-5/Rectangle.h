#pragma once
#include "shape.h"

class CRectangle : public CShape
{
public:
	CRectangle(int xmin=0, int ymin=0, int xmax=0, int ymax=0);
	~CRectangle(void);

public:
	double GetArea();		//���
	double GetPerimer();	//�ܳ�
	POINT GetCenter();	//����λ��
	virtual void Draw(CDC* pDC);	//����

private:
	double	m_dWidth;	//���
	double	m_dHeight;	//�߶�
	POINT	m_pt1, m_pt2;
};
