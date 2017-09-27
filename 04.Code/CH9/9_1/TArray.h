/************************************************************************/
/* class CTArray                                                        */
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
template<typename T>
class CTArray
{
public:
	// ���캯������������
	CTArray(T* ptData=NULL, int nSize=0)//
	{
		m_nSize = max(nSize, 0);
		m_nCapacity = GetGrowSize();

		m_ptData = new T[m_nCapacity];
		if (m_ptData != NULL && m_nSize>0)
		{
			memcpy(m_ptData, ptData, sizeof(T)*m_nSize);
		}
	}

	CTArray(const CTArray& ary)	//�������캯��
	{
		m_nSize = ary.m_nSize;
		m_nCapacity = GetGrowSize();
		m_ptData = new T[m_nCapacity];
		if (m_ptData)
		{
			memcpy(m_ptData, ary.m_ptData, sizeof(T)*m_nSize);
		}
	}

	operator T*()
	{
		return m_ptData;
	}

	~CTArray(void)
	{
		if (m_ptData)
		{
			delete[] m_ptData;
			m_ptData = NULL;
		}
		m_nSize = 0;
		m_nCapacity = 0;
	}

	friend ostream& operator<<(ostream& os, const CTArray<T>& ary)
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

	// ���Բ���
	inline int	GetSize() {return m_nSize;}	//Ԫ�ظ���

	CTArray operator=(const CTArray& ary)//����=
	{
		if (m_nSize >= ary.m_nSize)
		{	// �洢�ռ��㹻��ֱ�Ӹ���
			m_nSize = ary.m_nSize;
			memcpy(m_ptData, ary.m_ptData, sizeof(T)*m_nSize);
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
			m_ptData = new T[m_nCapacity];
			if (m_ptData != NULL)
			{
				memcpy(m_ptData, ary.m_ptData, sizeof(T)*m_nSize);
			}
		}

		return (*this);
	}

	T& operator[](int i)				//����[i]
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

	const T& operator[](int i) const	//����[i]
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

	// ���ݲ���
	void Add(T Val)					//׷��һ��Ԫ��
	{
		// ����洢�ռ�����������Ҫ���·����ڴ�
		if (m_nSize == m_nCapacity)
		{
			int		nCapacity = GetGrowSize();	//���·�����ڴ�Ĵ�С
			T*	dptBuff = new T[nCapacity];	//new
			if (dptBuff)
			{
				memcpy(dptBuff, m_ptData, sizeof(T)*m_nSize);	//����ԭ�е�����
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
		m_ptData[m_nSize++] = Val;
	}

protected:
	int	GetGrowSize() { return m_nSize + 10;}	//�ڴ�ռ�������Ĵ�С

private:
	T*		m_ptData;	//����ָ��
	int		m_nSize;	//Ԫ�ظ���
	int		m_nCapacity;//�洢�ռ䣨Ϊ�˱�֤׷�����ݵ�Ч�ʣ��洢�ռ��Դ���Ԫ�ظ�����
};