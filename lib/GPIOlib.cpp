#include <wiringPi.h>
#include <softPwm.h>

#include "GPIOlib.h"

const int IN1=22;
const int IN2=23;
const int ENA=24;
const int IN3=27;
const int IN4=28;
const int ENB=29;

const int LEFT_ISR=2;
const int RIGHT_ISR=3;

const int SERVO_CONTROL=1;

const int SPEED_LIMIT=80;
const int ANGLE_UPPER_BOUND=45;
const int ANGLE_LOWER_BOUND=-45;

bool initialized=false;
volatile int innerCountLeft=0;
volatile int innerCountRight=0;

void leftISR()
{
	++innerCountLeft;
}

void rightISR()
{
	++innerCountRight;
}


int GPIO::init()
{
	wiringPiSetup();
	softPwmCreate(ENA,0,100);
	softPwmCreate(ENB,0,100);
	pinMode(IN1,OUTPUT);
	pinMode(IN2,OUTPUT);
	pinMode(IN3,OUTPUT);
	pinMode(IN4,OUTPUT);
	
	pinMode(LEFT_ISR,INPUT);
	pinMode(RIGHT_ISR,INPUT);
	
	pinMode(SERVO_CONTROL,PWM_OUTPUT);
	pwmSetMode(PWM_MODE_MS);
	pwmSetClock(400);
	pwmSetRange(1024);
	
	initialized=true;
	
	GPIO::stopLeft();
	GPIO::stopRight();
	GPIO::turnTo(0);
	wiringPiISR(LEFT_ISR,INT_EDGE_FALLING,leftISR);
	wiringPiISR(RIGHT_ISR,INT_EDGE_FALLING,rightISR);
	return 0;
}

int GPIO::controlLeft(int direction,int speed)
{
	if(!initialized)
		return -1;
	
	if(speed<0)
		speed=0;
	if(speed>SPEED_LIMIT)
		speed=SPEED_LIMIT;
	
	if(direction==FORWARD)
	{
		digitalWrite(IN1,HIGH);
		digitalWrite(IN2,LOW);
		softPwmWrite(ENA,speed);
		return 0;
	}
	else if(direction==BACKWARD)
	{
		digitalWrite(IN1,LOW);
		digitalWrite(IN2,HIGH);
		softPwmWrite(ENA,speed);
		return 0;
	}
	else
		return -1;
}

int GPIO::controlRight(int direction,int speed)
{
	if(!initialized)
		return -1;
	
	if(speed<0)
		speed=0;
	if(speed>SPEED_LIMIT)
		speed=SPEED_LIMIT;
	
	if(direction==FORWARD)
	{
		digitalWrite(IN3,HIGH);
		digitalWrite(IN4,LOW);
		softPwmWrite(ENB,speed);
		return 0;
	}
	else if(direction==BACKWARD)
	{
		digitalWrite(IN3,LOW);
		digitalWrite(IN4,HIGH);
		softPwmWrite(ENB,speed);
		return 0;
	}
	else
		return -1;
}

int GPIO::stopLeft()
{
	if(!initialized)
		return -1;
	
	digitalWrite(IN1,HIGH);
	digitalWrite(IN2,LOW);
	softPwmWrite(ENA,0);
	return 0;
}

int GPIO::stopRight()
{
	if(!initialized)
		return -1;
	
	digitalWrite(IN3,HIGH);
	digitalWrite(IN4,LOW);
	softPwmWrite(ENB,0);
	return 0;
}

int GPIO::resetCounter()
{
	if(!initialized)
		return -1;
	
	innerCountLeft=innerCountRight=0;
	return 0;
}

//Counter is also reset to zero when this function is called.
void GPIO::getCounter(int *countLeft,int *countRight)
{
	if(!initialized)
	{
		*countLeft=*countRight=-1;
		return;
	}
	
	*countLeft=innerCountLeft;
	*countRight=innerCountRight;
	innerCountLeft=innerCountRight=0;
}

inline long map(long x,long in_min,long in_max,long out_min,long out_max)
{
	return (x-in_min)*(out_max-out_min)/(in_max-in_min)+out_min;
}

int GPIO::turnTo(int angle)
{
	if(!initialized)
		return -1;
	
	if(angle>ANGLE_UPPER_BOUND)
		angle=ANGLE_UPPER_BOUND;
	if(angle<ANGLE_LOWER_BOUND)
		angle=ANGLE_LOWER_BOUND;
	
	int pwmValue=map(angle,-90,90,24,120);
	pwmWrite(SERVO_CONTROL,pwmValue);
	return 0;
}

void GPIO::delay(int milliseconds)
{
	::delay(milliseconds);
}