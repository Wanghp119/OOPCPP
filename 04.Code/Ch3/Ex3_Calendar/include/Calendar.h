#ifndef CALENDAR_H
#define CALENDAR_H

/////////////////////////////////////////////////////////
// ��������
enum eWeekday
{
    SUN, MON, TUE, WED, THU, FRI, SAT, WEEK
};

const int   MAX_MONTH = 12;     //����·�
const eWeekday WD_ERA = SAT;    //��ԪԪ������һ


/*          �������
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
void PrintCalendar(int nYear, int nMonth);


// ��ȡĳ��ĳ�µ�����
int GetMonthDays(int nYear, int nMonth);

// �ж�ĳ���Ƿ�Ϊ����
inline bool IsLeapYear(int nYear)
{
    return ((nYear%400==0) || (nYear%4==0 && nYear%100!=0));
}

// ��ȡĳ�������ڼ�
eWeekday GetWeekday(int nYear, int nMonth, int nDay=1);


//

#endif // CALENDAR_H
