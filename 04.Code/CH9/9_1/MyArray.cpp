#include "MyArray.h"
#include "stdlib.h"
#include <iostream>
using namespace std;

// ���캯��
CMyArray::CMyArray(double* ptData, int nSize)
{
	m_nSize = max(nSize, 0);
	m_nCapacity = GetGrowSize();

	m_ptData = new double[m_nCapacity];
	if (m_ptData != NULL && m_nSize>0)
	{
		memcpy(m_ptData, ptData, sizeof(double)*m_nSize);
	}
}

// �������캯��
CMyArray::CMyArray(const CMyArray& ary)
{
	m_nSize = ary.m_nSize;
	m_nCapacity = GetGrowSize();
	m_ptData = new double[m_nCapacity];
	if (m_ptData)
	{
		memcpy(m_ptData, ary.m_ptData, sizeof(double)*m_nSize);
	}
}

// ��������
CMyArray::~CMyArray(void)
{
	if (m_ptData)
	{
		delete[] m_ptData;
		m_ptData = NULL;
	}
	m_nSize = 0;
	m_nCapacity = 0;
}

// ���� = �����
CMyArray CMyArray::operator=(const CMyArray& ary)
{
	if (m_nSize >= ary.m_nSize)
	{	// �洢�ռ��㹻��ֱ�Ӹ���
		m_nSize = ary.m_nSize;
		memcpy(m_ptData, ary.m_ptData, sizeof(double)*m_nSize);
	}
	else	//�洢�ռ䲻��
	{
		// ���ͷ������ڴ棬�ٷ��������ڴ�ռ䣬�����
		if (m_ptData)
		{
			delete[] m_ptData;
			m_ptData = NULL;
		}
		m_nSize = ary.m_nSize;
		m_nCapacity = GetGrowSize();
		m_ptData = new double[m_nCapacity];
		if (m_ptData != NULL)
		{
			memcpy(m_ptData, ary.m_ptData, sizeof(double)*m_nSize);
		}
	}

	return (*this);
}

// ����[i]
double& CMyArray::operator[](int i)
{
	try
	{
		if (i>=0 && i<m_nSize)	//�±���
			return m_ptData[i];
		else
			throw;
	}
	catch(...)
	{
		cerr << "operator [] failed." << endl;
	}
}

// ����[i]
const double& CMyArray::operator[](int i) const
{
	try
	{
		if (i>=0 && i<m_nSize)	//�±���
			return m_ptData[i];
		else
			throw;
	}
	catch(...)
	{
		cerr << "operator [] failed." << endl;
	}
}

// ׷��һ��Ԫ��
void CMyArray::Add(double dVal)
{	
	// ����洢�ռ�����������Ҫ���·����ڴ�
	if (m_nSize == m_nCapacity)
	{
		int		nCapacity = GetGrowSize();	//���·�����ڴ�Ĵ�С
		double*	dptBuff = new double[nCapacity];	//new
		if (dptBuff)
		{
			memcpy(dptBuff, m_ptData, sizeof(double)*m_nSize);	//����ԭ�е�����
		}

		if (m_ptData)	//�ͷ�ԭ������
		{
			delete[] m_ptData;
		}

		//��Ա�������¸�ֵ
		m_ptData = dptBuff;
		m_nCapacity = nCapacity;
	}

	// ׷��һ��Ԫ��
	m_ptData[m_nSize++] = dVal;
}

ostream& operator<<(ostream& os, const CMyArray& ary)
{
	int		i;
	for (i=0; i<ary.m_nSize; i++)
	{
		if (i>0 && i%10==0)
			cout << endl;

		os << ary[i] << " ";
	}
	if (i%10)
		cout << endl;

	return os;
}