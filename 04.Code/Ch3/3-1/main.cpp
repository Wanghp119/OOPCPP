#include <iostream>

using namespace std;

double power(double, int);  //����

int main()
{
    cout << " 5 to the power 2 is " << power(5, 2) << endl;
    return 0;
}

// ����x��n�η�
double power(double x, int n)
{
	double val = 1.0;
	while(n>0)
	{
		val *= x;
		n--;
	}

	return val;
}

double power2(double x, int n)
{
    if (n==0)
     return 1.0;

    return x*power2(x, n-1);
}
