#include "MotorDriver.h"
#include "PostureControl.h"

using MotorDriver::forward;
using MotorDriver::stop;
using PostureControl::turnLeftALittle;
using PostureControl::turnRightALittle;

void setup()
{
	MotorDriver::init();
	Serial.begin(115200);
}

void loop()
{
	if (Serial.available()>0)
	{
		char ch = Serial.read();
		switch (ch)
		{
			case 'F':
				MotorDriver::forward(MOTOR_LEFT_FRONT);
				MotorDriver::forward(MOTOR_LEFT_BACK);
				MotorDriver::forward(MOTOR_RIGHT_FRONT);
				MotorDriver::forward(MOTOR_RIGHT_BACK);
				break;
			case 'S':
				MotorDriver::stop(MOTOR_LEFT_FRONT);
				MotorDriver::stop(MOTOR_LEFT_BACK);
				MotorDriver::stop(MOTOR_RIGHT_FRONT);
				MotorDriver::stop(MOTOR_RIGHT_BACK);
				break;
			case 'L':
				PostureControl::turnLeftALittle();
				break;
			case 'R':
				PostureControl::turnRightALittle();
				break;
			default:
				delay(1);
		}
	}
	else
		delay(2);
}
