// ����������
#include <iostream>
using namespace std;

int		i;		//�ļ�������

namespace Ns
{
	int		j;		//���ֿռ�������
}

// ������
int main()
{
	i = 5;	//global
	Ns::j = 6;	//

	{
		using namespace Ns;
		 int		i = 7;	//�ֲ�������

		 cout << "i = " << i << endl;	//local
		 cout << "Ns::j = " << j << endl;
	}

	cout << "i = " << i << endl;	//global
	
	return 0;
} 