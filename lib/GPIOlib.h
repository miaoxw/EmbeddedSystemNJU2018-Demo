#ifndef GPIOLIB_H
#define GPIOLIB_H

#define FORWARD 1
#define BACKWARD 0

namespace GPIO
{
	int init();
	
	//direction is either FORWARD or BACKWARD. speed can be an integer ranging from 0 to 100.
	int controlLeft(int direction,int speed);
	int controlRight(int direction,int speed);
	int stopLeft();
	int stopRight();
	
	int resetCounter();
	void getCounter(int *countLeft,int *countRight);
	//angle is available in the range of -90 to 90.
	int turnTo(int angle);
	
	void delay(int milliseconds);
}
#endif
