// main
#include <iostream>
#include "Clock.h"
using namespace std;

Clock	gClock;	//ȫ�ֶ��󣬾��о�̬�����ڣ������ռ�������

int main()
{
	gClock.showTime();

	gClock.setTime(8, 30, 30);
	
	Clock	myClock(gClock);
	myClock.showTime();

	return 0;
}