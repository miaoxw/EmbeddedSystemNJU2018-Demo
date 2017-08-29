#ifndef _MOTORDRIVER_h
#define _MOTORDRIVER_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#define MOTOR_LEFT_FRONT 0
#define MOTOR_RIGHT_FRONT 1
#define MOTOR_LEFT_BACK 2
#define MOTOR_RIGHT_BACK 3

namespace MotorDriver
{
	const unsigned char DEFAULT_SPEED=90;

	void init();
	void forward(char motorID,uint8_t speed=DEFAULT_SPEED);
	void backward(char motorID,uint8_t speed=DEFAULT_SPEED);
	void stop(char motorID);
}
#endif

