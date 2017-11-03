/****************************************************************************
 *              ��������ʾ����                                             *
 * ���ܣ����������գ���ӡ��ǰ�µ��������������ں�������                  *
 ****************************************************************************/
#include <iostream>
#include "Calendar.h"

using namespace std;

void Usage()
{
    //
    cout << "Usage: Input a date with yyyy-mm, print the calender of month." << endl;
    cout << "       Validate Parameter : yyyy (1-2020), mm (1-12)" << endl;
    cout << "       Exit - input year<=0 && mm<=0" << endl;
}

int main()
{
    Usage();

    int     nYear, nMonth;
    do
    {
        // ��ʼֵ
        nYear = nMonth = 0;

        // �����ꡢ�¡���
        cout << "Input a date yyyy mm��";
        cin >> nYear >> nMonth;

        // �Ϸ������ӡ������
        if (nYear>0 && nMonth>0 && nMonth<=MAX_MONTH)
        {
            PrintCalendar(nYear, nMonth);
        }
        else
        {   // ���벻�Ϸ�����ӡҪ��
            Usage();
        }
    }while(nYear>0 || nMonth>0);   //���ºϷ���������

    return 0;
}
