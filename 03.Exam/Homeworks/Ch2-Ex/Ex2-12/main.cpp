/******************************************************************************
// ����һ��������1��������λ����2����ÿ��λ�ϵ�����3��˳����������
******************************************************************************/

#include <iostream>

using namespace std;

int main()
{
    long     num;
    int      indiv = 0;
    long     t;
    int     pDig[100];
    int     i;

    cout << "Input a Integer: ";
    cin >> num;

    // λ��
    t = num;
    while (t>0)
    {
        pDig[indiv++] = t%10;
        t /= 10;
    }
    cout << num << " is a " << indiv << " number." << endl;

    // ˳���ӡ
    for (i=indiv-1; i>=0; i--)
        cout << pDig[i];
    cout << endl;

    // �����ӡ
    for (i=0; i<indiv; i++)
        cout << pDig[i];
    cout << endl;

    return 0;
}
