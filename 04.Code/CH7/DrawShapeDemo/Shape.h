#pragma once

#ifndef PI
	#define PI 3.14159265358979323846
#endif

class CShape
{
public:
	CShape(void);
	virtual ~CShape(void);

public:
	// virtual �ӿ�
	virtual double GetArea() = 0;		//���
	virtual double GetPerimer() = 0;	//�ܳ�
	virtual void Draw(CDC* pDC) = 0;	//����ͼ��
	virtual POINT GetCenter() = 0;		//����λ��

	void DrawInfo(CDC* pDC);	
};
