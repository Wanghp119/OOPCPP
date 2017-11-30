#include <iostream>
#include "Circle.h"

using namespace std;

const float FencePrice = 35;		//Χ������
const float ConcretePrice = 20;		//��������

// ������
int main()
{
	float		radius;			//�뾶
	float		FenceCost;	//Χ�����
	float		ConcreteCost;	//�������
	
	// ����Ӿ�ذ뾶
	cout << "Input pool radius : " << endl;
	cin >> radius;
	
	Circle		oPool(radius);		//��Ӿ�ض���
	Circle		oPoolRim(radius+3.0);	//Ӿ����Χ����
	
	FenceCost = FencePrice * oPool.Perimeter();	//�ܳ�*����
	cout << "Fence Cost is : ��" << FenceCost << endl;

	// ��� * ����
	ConcreteCost = ConcretePrice * (oPoolRim.Area() - oPool.Area());
	cout << "Concrete Cost is : ��" << ConcreteCost << endl;

	return 0;
}