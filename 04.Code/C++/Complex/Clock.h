#pragma once

class CClock	//ʱ��������
{
public:	//�ⲿ�ӿ�
	CClock(int NewH=0, int NewM=0, int NewS=0);
	~CClock(void);

	void ShowTime( );

	CClock&  operator ++( );  //ǰ�õ�Ŀ���������
	CClock operator ++(int);  //���õ�Ŀ���������

private:	//˽�����ݳ�Ա
	int m_nHour;
	int	m_nMin;
	int	m_nSec;
};

int _TestClock();