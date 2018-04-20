#include <iostream>
#include <cmath>
#include <algorithm>
#include <vector>
#include <list>
#include <string>

// 2-N֮������������

using namespace std;

// �ж�N�Ƿ�Ϊ����
bool IsPrime(unsigned long N)
{
    long     i;
    long     nEnd = sqrt(N)+1;

    for (i=2; i<nEnd; i++)
        if (N%i==0) return false;

    return true;
}

template<typename T>
void PrintPrime(T t1, T t2)
{
    T   iter;
    for (iter=t1; iter!=t2; iter++)
    {
        cout << (*iter) << "\t";
    }
    cout << endl;

    return;
}

/*
    ����һ��������N�������2-N����������
*/
int main()
{
    unsigned long     N;
    cout << "Input Number: ";
    cin >> N;

    cout <<  "Prime Number(1-" << N << "): ";
    unsigned long      i;
    for (i=2; i<=N; i++)
    {
        if (IsPrime(i))
        {
            cout << i << "\t";
        }
    }
    cout << endl;

    // Container
    vector<unsigned long>   vecPrime;
    list<unsigned long> lstPrime;
    for (i=2; i<=N; i++)
    {
        if (IsPrime(i))
        {
            vecPrime.push_back(i);
            lstPrime.insert(lstPrime.end(),i);
        }
    }

    cout << "vector Prime: ";
    PrintPrime(vecPrime.begin(), vecPrime.end());
    cout << endl;

    cout << "list prime: ";
    PrintPrime(lstPrime.begin(), lstPrime.end());
    cout << endl;

    list< vector<int> > lv;

    string  str;

    return 0;
}
