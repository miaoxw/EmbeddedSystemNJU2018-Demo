#include "MotorDriver.h"

namespace MotorDriver
{
	const char DIRECTION_PINS[]={4,12,8,7};
	const char SPEED_PINS[]={3,11,5,6};
}

void MotorDriver::init()
{
	for(int i=0;i<4;i++)
	{
		pinMode(DIRECTION_PINS[i],OUTPUT);
		pinMode(SPEED_PINS[i],OUTPUT);
	}
}

void MotorDriver::forward(char motorID,uint8_t speed)
{
	digitalWrite(DIRECTION_PINS[motorID],HIGH);
	analogWrite(SPEED_PINS[motorID],speed);
}

void MotorDriver::backward(char motorID,uint8_t speed)
{
	digitalWrite(DIRECTION_PINS[motorID],LOW);
	analogWrite(SPEED_PINS[motorID],speed);
}

void MotorDriver::stop(char motorID)
{
	digitalWrite(DIRECTION_PINS[motorID],HIGH);
	analogWrite(SPEED_PINS[motorID],0);
}
