#include <iostream>

using namespace std;

int main()
{
    int i=0,j=0,n;

    cout<<"��������������(����0�����)��";
    cin>>n;
    while( n!=0 )
    {
        if(n>0) i++;
        if(n<0) j++;
        cin>>n    ;
    }

    cout <<"������������" <<i << "\t";
    cout <<"������������" <<j <<endl;

    return 0;
}
