#include <iostream>

using namespace std;

int main()
{
    int     m, n;
    int     tmp;
    int     sum;
    int     r;

    // ����2������
    cout << "Input 2 integer number: ";
    cin >> m >> n;

    // n��������m��С����
    if (n < m)
    {
        tmp = n;
        n = m;
        m = tmp;
    }

    sum = n * m;    //�˻�

    // Լȥ�������Լ��
    // �ٶ�n>m, n=k*t, m=l*t,��Լ��Ϊt. ���ڵ�Ŀ������t���Ҽٶ�n=s*m+r����r=0,��t=m;��r!=0, ��n��m�Ĺ�Լ��t����m��r�Ĺ�Լ����
    while (0 != m)
    {
        r = n % m;
        n = m;
        m = r;
    }

    cout << "HCF = " << n << endl;
    cout << "LCD = " << sum/n << endl;

    return 0;
}
