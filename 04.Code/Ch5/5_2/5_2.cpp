// ��̬������

#include <iostream>
using namespace std;

int		i = 1;	//ȫ�ֱ��������о�̬������

void fun();

void Test()
{
	// ��̬�ֲ�����������ȫ�������ڣ��ֲ��ɼ���ֻ�е�һ�ν��뺯��ʱ����ʼ��
	static int	a = 2;
	static int	b;
	
	int		c = 10;	//�ֲ����������ж�̬�����ڣ�ÿ�ν��뺯��ʱ����ʼ��
	
	a += 2;
	i += 32;
	c += 5;

	cout << "Variable is : " << endl;
	cout << "i: " << i << "\t";
	cout << "a: " << a << "\t";
	cout << "b: " << b << "\t";
	cout << "c: " << c << endl;

	b = a;
}

int main()
{
	static int a;	//��̬�ֲ�������ȫ�������ڣ��ֲ��ɼ�
	int		b = -10;
	int		c = 0;
	
	cout << "---MAIN ---" << endl;
	cout << "i: " << i << "\t";
	cout << "a: " << a << "\t";
	cout << "b: " << b << "\t";
	cout << "c: " << c << endl;

	c += 8;
	Test();	
	cout << "---MAIN ---" << endl;
	cout << "i: " << i << "\t";
	cout << "a: " << a << "\t";
	cout << "b: " << b << "\t";
	cout << "c: " << c << endl;

	i += 10;
	Test();

	return 0;
}