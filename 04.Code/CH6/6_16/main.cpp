#include <iostream>
#include "Point.h"

using namespace std;

int main()
{
	{
		int		n;
		cin >> n;

		VectorPoint		vecPnt(n);
		vecPnt.GetPoint(0).GetX();
		vecPnt[0].GetX();

		Point*	pPnts = new Point[n];
		
		if (pPnts != 0)
		{
			pPnts[0].GetX();
			
			delete[] pPnts;
			pPnts = 0;
		}
	}

	{
		int		count;
		cout << "Input count: " << endl;
		cin >> count;

		int		i;
		int		*pheight = new int[count];
		if (pheight != 0L)
		{
			for (i=0; i<count; ++i)
			{
				cout << "Input No. " << (i+1) << "  Height: ";
				cin >> pheight[i];
			}
			
			delete[] pheight;
			pheight = 0L;
		}


		return 0;
	}

	{
	Point*	ptPnt = NULL;	// Step 1. ����ָ��
	ptPnt = new Point;		// Step 2. ��ֵ������ռ�
	
	if (ptPnt)	{
		delete ptPnt;			// Step 3. ɾ���ռ�
		ptPnt = NULL;
	}
	
	// 
	ptPnt = new Point(1,2);	// ����ʼ���б�
	if (ptPnt){
		delete ptPnt;
		ptPnt = NULL;
	}
	ptPnt = new Point();
	if (ptPnt) { 
		delete ptPnt;
		ptPnt = NULL;
	}

	// ָ������ָ��
	ptPnt = new Point[10];	
	if (ptPnt){
		delete ptPnt;
		ptPnt = NULL;
	}

	// ��û�д��󣿣���
	ptPnt = new Point[0];
	
	// ����Ԫ��
	ptPnt[0].GetX();
	(*(ptPnt+0)).GetX();
	(ptPnt+0)->GetX();
	}

	/////////////////////////////////////////////////////////////
	// 1. ָ����� and const�÷�
	{
		int		a = 5;
		int		b = 10;
		int	*	pa = &a;
		*pa = 10;	// <==> a=10;
		cout << pa << "\t" << *pa << endl;
		
		// 2. ���� & const
		int& ra = a;
		ra = 10;	//<==> a=10;
		ra = b;
		
		// 3.ָ�������
		int*	&rpa = pa;	// 	int&	*pra = pa;
		
		//???ָ�������õ����𣿣���
	}

	/////////////////////////////////////////////////////////////
	// 2.ָ�������ָ��
	/////////////////////////////////////////////////////////////
	{
		// һά����
		int		a[10];
		int		*pa;

		pa = a;
		pa = &a[0];
		cout << pa[1] << "\t";
		cout << *(pa+1) << "\t";
		cout << *pa+1 << "\t";
		
		// ����ָ�� VS. ָ������
		int		b[10][10];
		int		*pb[10];	//ָ������
	//	pb = b;	//????
		int		(*pb2)[10];
		pb2 = b;

		// ���ͨ��ָ����ʶ�ά���飿��
		// ����1. ��ά����ȼ�Ϊһά����
		int		*pm;	//pm = b;
		pm = &b[0][0];
		// *(pm+i*col+j);
		// pm[i*col+j];
		
		// ����2. ��ָ������ģ���ά����
		int		**ppm;
		int		irow = 10;
		int		icol = 5;
		int		i;
		ppm = new int* [irow];
		for (i=0; i<irow; ++i)
		{
			ppm[i] = new int[icol];
		}

		//delete
		for (i=0; i<irow; ++i)
		{
			if (ppm[i]) delete[] ppm[i];
		}
		delete[] ppm;
		
		/////////////////////////////////////////////////////////////////////////////////
		/// ����ָ��
		//////////////////////////////////////////////////////////////////////////////////
		{
			int		(*pfn)(int, int);
			//pfn = ;
			int		(Point::*pfn2)() = Point::GetX;

			//��̬��������

		}
		
		
	}
	
	return 0;
}

/**ָ����÷�

*/
