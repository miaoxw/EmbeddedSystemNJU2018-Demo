#ifndef GPIOLIB_H
#define GPIOLIB_H

#define FORWARD 1
#define BACKWARD 0

namespace GPIO
{
	int init();
	
	int controlLeft(int direction,int speed);
	int controlRight(int direction,int speed);
	int stopLeft();
	int stopRight();
	
	int resetCounter();
	void getCounter(int *countLeft,int *countRight);
	
	int turnTo(int angle);
	
	void delay(int milliseconds);
}
#endif
