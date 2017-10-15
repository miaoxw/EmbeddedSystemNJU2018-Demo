#include "GPIOlib.h"

using namespace GPIO;

int main()
{
	init();

	//THIS IS THE SAFE RANGE!
	for(int i=-45;i<=45;i+=15)
	{
		turnTo(i);
		delay(1000);
	}

	turnTo(0);
	return 0;
}
