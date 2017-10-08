#include <iostream>

using namespace std;

bool IsNarcissusNum(int);   //����ˮ�ɻ����жϺ���

int main()
{
    int     i;
    for (i=100; i<1000; ++i)
    {
        if (IsNarcissusNum(i))
        {
            cout << i << "\t";
        }
    }   //for

    return 0;
}

//-------------------------------------------//
// ˮ�ɻ����жϺ���
//------------------------------------------//
bool IsNarcissusNum(int num)
{
    int     digital;
    int     sum = 0;
    int     org = num;
    while(org > 0)
    {
        digital = org % 10; //��ĩβ����

        sum += digital * digital * digital; //����3�η�
        org /= 10;  //����ĩβ����
    }

    //�ж�sum�Ƿ����������
    return (sum == num);
}
