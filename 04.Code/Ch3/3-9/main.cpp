/******************************************************************************
 * PPT ��3-9
 *****************************************************************************/

#include <iostream>

using namespace std;

/// �ݹ����
int comm(int n, int k)
{
    /// n���˷�Ϊ2�飬һ��n-1���ˣ���һ��1�ˡ�
    /// ��������1��ѡ��ѡΪ������ѡ����ΪC(n-1,k-1)������ѡ����ΪC(n-1,k)
    /// �ʣ�C(n,k) = C(n-1,k) + C(n-1,k-1)
    if (k > n)
        return 0;
    else if (n == k || k == 0)
        return 1;
    else
        return comm(n - 1, k) + comm(n - 1, k - 1);
}

int main()
{
    int comm(int n, int k);
    int n, k;
    cout << "Please enter two integers n and k: ";
    cin >> n >> k;

    cout << "C(n, k) = " << comm(n, k) << endl;

    return 0;
}
