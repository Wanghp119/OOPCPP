////////////////////////////////////////////////////////////////////////////
// �ļ����ܣ�
// ���ڣ�
// ���ߣ�
//////////////////////////////////////////////////////////////////////////

#ifndef _CANLEDAR_H_
#define _CANLEDAR_H_

//////////////////////////////////////////////////////////////////////////
// ���ܣ���ӡ����
// ���������int nYear - ��
//			 int nMonth - ��
// ����ֵ��void - ��
//////////////////////////////////////////////////////////////////////////
void PrintCalendar(int nYear, int nMonth);

// ��������ö�ٱ���
enum eWeekday
{
	SUN, MON, TUE, WED, THR, FRI, SAT
};

eWeekday GetWeekday(int nYear, int nMonth, int nDay);

int GetMonthDays(int nYear, int nMonth);

// �ж�����
inline bool IsLeapYear(int nYear)
{
	return ((nYear%4==0 && nYear%100!=0) || nYear%400==0);
}

#endif//#ifndef _CANLEDAR_H_
