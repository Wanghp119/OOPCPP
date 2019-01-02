#include <iostream>
#include "Circle.h"
#include "Pool.h"

using namespace std;

const float FencePrice = 35;		//Χ������
const float ConcretePrice = 20;		//��������

// ������
int main()
{
    Circle  c(2.0f);
    Circle  c2(c);

    c2 = c;

    cout << c.Perimeter() << "\t" << c.Area() << endl;
    cout << c2.Perimeter() << "\t" << c2.Area() << endl;
    return 0;

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
