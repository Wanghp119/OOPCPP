#include <iostream>
#include "Complex.h"

using namespace std;

/// ������Ĳ���
int main()
{
    complex     c(1,3);     /// 1+3i
    complex     d(2,4);     /// 2+4i

    cout << (c+d) << endl;  /// ����+
    cout << (c-d) << endl;  /// ����-

    /// ���� /
    complex     e = c/d;
    cout << e << endl;  ///�������

    cout << d*e << endl;    ///����*

    return 0;
}
