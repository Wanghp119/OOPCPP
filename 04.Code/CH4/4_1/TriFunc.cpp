#include "TriFunc.h"
#include <iostream>
#include <cmath>

using namespace std;

// ����һ���ӽ�0��Сֵ
const double	EPLISON = 1.0E-10;

// �������ܳ�
double GetPerimeter(double a, double b, double c)
{
	double	dPerimeter = 0.0f;

	if (IsValidTriangle(a, b, c))
		dPerimeter = a + b + c;
	
	return dPerimeter;
}

// ���������
double GetArea(double a, double b, double c)
{
	double		dArea = 0.0f;
	double		dS;
	
	if (IsValidTriangle(a, b, c))
	{
		dS = GetPerimeter(a, b, c)/2;
		dArea = sqrt(dS*(dS-a)*(dS-b)*(dS-c));
	}

	return dArea;
}


// �����νǶ�
double GetAngle(double a, double b, double c)
{
	double		dAngle = 0.0f;

	return dAngle;
}

// �������Ƿ�Ϸ�
bool IsValidTriangle(double a, double b, double c)
{
	if ((a+b-c)<EPLISON || (a+c-b)<EPLISON || (b+c-a)<EPLISON)
		return false;

	return true;
}