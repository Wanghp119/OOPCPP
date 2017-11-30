/************************************************************************/
/* class CMyArray                                                       */
/* �Զ���������࣬��̬�����ڴ�											*/
/* Wang hongping 2017.3.7												*/
/************************************************************************/

#pragma once

#ifndef NULL
#define NULL 0
#endif	//NULL

#include <iostream>
using namespace std;

//
class CMyArray
{
public:
	// ���캯������������
	CMyArray(double* ptData=NULL, int nSize=0);	//
	CMyArray(const CMyArray& ary);	//�������캯��
	~CMyArray(void);

	friend ostream& operator<<(ostream& os, const CMyArray& ary);

	// ���Բ���
	inline int	GetSize() {return m_nSize;}	//Ԫ�ظ���
	CMyArray operator=(const CMyArray& ary);//����=
	double& operator[](int i);				//����[i]
	const double& operator[](int i) const;	//����[i]
	operator double*() {return m_ptData;}
	
	// ���ݲ���
	void Add(double dVal);					//׷��һ��Ԫ��

protected:
	int	GetGrowSize() { return m_nSize + 10;}	//�ڴ�ռ�������Ĵ�С

private:
	double*	m_ptData;	//����ָ��
	int		m_nSize;	//Ԫ�ظ���
	int		m_nCapacity;//�洢�ռ䣨Ϊ�˱�֤׷�����ݵ�Ч�ʣ��洢�ռ��Դ���Ԫ�ظ�����
};

ostream& operator<<(ostream& os, const CMyArray& ary);
