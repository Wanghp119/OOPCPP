#include<iostream>
using namespace std;

int main()
{
	int*	ptr_i;		//����int��ָ��i_pointer
	int		i;			//����int����i

	// const int* ptr_i
	// int* const ptr_i

	ptr_i = &i;	//ȡi�ĵ�ַ����i_pointer

	i = 10;		// int��������ֵ
	*ptr_i = 10;	//������ֵ

	cout<< "Output int i=" << i <<endl;		//���int������ֵ
	cout<< "Output int pointer i=" << *ptr_i <<endl;	//���int��ָ����ָ��ַ������

	return 0;
}