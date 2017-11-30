#pragma once

#include "Shape.h"

class CCircle : public CShape
{
public:
	CCircle(int r = 0, int x0=0, int yo=0);
	~CCircle(void);

public:
	virtual void Draw(CDC* pDC);	//����
	double GetArea();		//���
	double GetPerimer();	//�ܳ�

	POINT GetCenter();	
private:
	int			m_nRadius;
	POINT		m_ptCenter;	
};
