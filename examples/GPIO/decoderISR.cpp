#include <cstdio>
#include <cmath>
#include "GPIOlib.h"

using namespace std;
using namespace GPIO;

int readingLeft=0,readingRight=0;

int main()
{
	init();
	
	controlLeft(FORWARD,30);
	controlRight(BACKWARD,40);
	
	for(int i=0;i<10;i++)
	{
		resetCounter();
		delay(1000);
		getCounter(&readingLeft,&readingRight);
		if(readingLeft==-1||readingRight==-1)
		{
			printf("Error!\n");
			continue;
		}
		//Distance is in mm.
		double distanceLeft=readingLeft*63.4*M_PI/390;
		double distanceRight=readingRight*63.4*M_PI/390;
		printf("Left wheel moved %.2lf cm, right wheel moved %.2lf cm in last second.\n",distanceLeft/10,distanceRight/10);
	}
	stopLeft();
	stopRight();
	return 0;
}
