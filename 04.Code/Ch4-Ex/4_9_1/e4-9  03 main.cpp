// e4-9  03.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include"e4-9  03.h"	//�ļ�·����ò�Ҫ���ո񡣡���
#include<iostream>
using namespace std;

//extern int i;	//extern int i��˵��i��һ��ȫ�ֱ�������i���𣿣���

int main()
{


	point r(20, 10);
	point l(50, 10);

	r.print(20,10);
	l.print(50,10);

	rectangle area(r, l);

	cout << "s=" << area.getarea()<<"   ";
//	cout << point::i;	//i����ô�����𣿣�Ӧ����Point::i,��i��private�����������static��������
    return 0;
}

