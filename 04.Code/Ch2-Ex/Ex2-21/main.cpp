#include <iostream>

using namespace std;

int main()
{
    int     n;
    int     i;
    double  fraction = 0.0F;       //����
    float   denominator = 1;    //��ĸ
    float   numerator = 2;      //����
    cout << "Input a integer number: ";
    cin >> n;

    for (i=1; i<=n; ++i)
    {
        fraction += numerator / denominator;

        numerator += denominator;
        denominator = (numerator-denominator);
    }

    cout << "sum = " << fraction << endl;
    return 0;
}
