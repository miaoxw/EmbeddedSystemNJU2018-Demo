#include <wiringPi.h>

const int SERVO_CONTROL=1;

inline long map(long x,long in_min,long in_max,long out_min,long out_max)
{
	return (x-in_min)*(out_max-out_min)/(in_max-in_min)+out_min;
}

//Angle range is -90deg to +90deg. Minus sign is left, and vice versa.
//However, it is unnecessary to turn an angle beyond the rande of[-45deg, 45deg].
//Rude operation may cause FATAL DAMAGE to the servo!
void turnTo(int angle)
{
	if(angle<-90)
		angle=-90;
	if(angle>90)
		angle=90;

	int pwmValue=map(angle,-90,90,24,120);
	pwmWrite(SERVO_CONTROL,pwmValue);
}

int main()
{
	wiringPiSetup();

	//Some parameter settings when using PWM output.
	pinMode(SERVO_CONTROL,PWM_OUTPUT);
	pwmSetMode(PWM_MODE_MS);
	pwmSetClock(400);
	pwmSetRange(1024);

	//THIS IS THE SAFE RANGE!
	for(int i=-45;i<=45;i+=15)
	{
		turnTo(i);
		delay(2000);
	}

	turnTo(0);
	return 0;
}

