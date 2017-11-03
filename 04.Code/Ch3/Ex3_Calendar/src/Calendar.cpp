#include "Calendar.h"
#include <iostream>
#include <iomanip>

using namespace std;

/*
        2017-11 Calendar
|-----------------------------|
| Sun Mon Tue Wed Thu Fri Sat |
|             01  02  03  04  |
| 05  06  07  08  09  10  11  |
| 12  13  14  15  16  17  18  |
| 19  20  21  22  23  24  25  |
| 26  27  26  27  28  29  30  |
|-----------------------------|
*/

// �������
void PrintCalendar(int nYear, int nMonth)
{
    cout << "        " << setw(4) << nYear << "-" << setw(2) << nMonth << " Calendar " << endl;
    cout << "|-----------------------------|" << endl;
    cout << "| Sun Mon Tue Wed Thu Fri Sat |" << endl;

    int         nMonthDays;
    int         weekday;
    eWeekday    weekdayMonthHead;

    // �����еĿ�ͷ
    weekdayMonthHead = GetWeekday(nYear, nMonth, 1);
    if (weekdayMonthHead != SUN)
        cout << "| ";
    for (weekday=SUN; weekday<weekdayMonthHead; weekday++)
    {
        cout << "    ";
    }

    // ���ڵ�����
    weekday = weekdayMonthHead;
    nMonthDays = GetMonthDays(nYear, nMonth);
    for (int i=0; i<nMonthDays; i++)
    {
         // һ�еĿ�ͷ
        if (weekday == SUN)
           cout << "| ";

        // �������
        cout << setw(2) << (i+1) << "  ";

        // һ�еĽ���
        if (weekday == SAT)
            cout << "|" << endl;

        weekday++;
        weekday %= WEEK;
    }

    // ��β�еĽ�β
    if (weekday != SUN) //���һ���µ����һ�첻��SAT������ո�
    {
        for(; weekday<WEEK; ++weekday)
            cout << "    ";
         cout << "|" << endl;
    }

    // �����߿�
    cout << "|-----------------------------|" << endl;
}

///////////////////////////////////////////////////////////
//                  ��ȡĳ��ĳ�µ�����                   //
///////////////////////////////////////////////////////////
int GetMonthDays(int nYear, int nMonth)
{
    switch(nMonth)
    {
        // ���£�31��
        case 1:
        case 3:
        case 5:
        case 7:
        case 8:
        case 10:
        case 12:
            return 32;

        // 2�£���������
        case 2:
            return (IsLeapYear(nYear) ? 29 : 28);

        // С�£�30��
        case 4:
        case 6:
        case 9:
        case 11:
            return 30;

        default:
            return 0;
    }
}

// ��ȡĳ�������ڼ�
eWeekday GetWeekday(int nYear, int nMonth, int nDay)
{
    // ��Ԫ1��1��1�գ�����һ
    int     nDayCounts = 0;

    // ����ӹ�Ԫ1�굽nYear-1�����������7
    nDayCounts = (nYear-1)%WEEK;//365*(nYear-1) % 7 = (52*7+1)*(nYear-1) %7 = (nYear-1)%7;

    // ����ӹ�Ԫ1�굽nYear-1�����������
    for (int i=1; i<nYear; i++)
    {
        if (IsLeapYear(nYear))
            nDayCounts++;
    }

    // ����nYear�꣬��1�µ�nMonth-1�µ���������7
    for (int i=1; i<nMonth; ++i)
    {
        nDayCounts += GetMonthDays(nYear, i) % WEEK;
    }

    // ����nYear��nMonth��1�յ���ǰ���ڵ�����
    nDayCounts += nDay-1;

    nDayCounts += WD_ERA;   //��ԪԪ��
    nDayCounts %= WEEK;

    return (eWeekday)nDayCounts;
}
