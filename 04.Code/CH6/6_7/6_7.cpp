#include <iostream>
using namespace std;

void Fun1(int a[], int num);
void Fun2(int a[], int num);
void Fun3(int a[], int num);

int main()
{
	int		a[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

	Fun1(a, 10);
	cout << endl;

	Fun2(a, 10);
	cout << endl;
	
	Fun3(a, 10);
	cout << endl;
	
	return 0;
}

// ������������Ԫ��
void Fun1(int a[], int num)
{
	int		i;
	for (i=0; i<num; ++i)
	{
		cout << a[i] << "\t";
	}
	cout << endl;
}

// ��������+ָ�����������Ԫ��
void Fun2(int a[], int num)
{
	int		i;
	for (i=0; i<num; ++i)
	{
		cout << *(a+i) << "\t";
	}
	cout << endl;
}

// ��ָ�����Ԫ��
void Fun3(int a[], int num)
{
	int*	ptr = a;
	for (ptr=a; ptr<a+10; ++ptr)
	{
		cout << *ptr << "\t";
	}
	cout << endl;
}