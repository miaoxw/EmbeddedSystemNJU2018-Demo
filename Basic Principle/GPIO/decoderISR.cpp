#include <cstdio>
#include <wiringPi.h>
#include <softPwm.h>

using namespace std;

//Pins in control of the motor on the left
const int IN1=22;
const int IN2=23;
const int ENA=24;
//Pins in control of the motor on the right
const int IN3=27;
const int IN4=28;
const int ENB=29;
//Pins of EINT resources
const int LEFT_ISR=2;
const int RIGHT_ISR=3;

volatile int countLeft=0;
volatile int countRight=0;

void leftISR()
{
	++countLeft;
}

void rightISR()
{
	++countRight;
}

int main()
{
	wiringPiSetup();
	softPwmCreate(ENA,0,100);
	softPwmCreate(ENB,0,100);
	pinMode(IN1,OUTPUT);
	pinMode(IN2,OUTPUT);
	pinMode(IN3,OUTPUT);
	pinMode(IN4,OUTPUT);
	
	//Pins for EINT should be set to INPUT
	pinMode(LEFT_ISR,INPUT);
	pinMode(RIGHT_ISR,INPUT); 

	softPwmWrite(ENA,10);
	softPwmWrite(ENB,20);
	digitalWrite(IN1,HIGH);
	digitalWrite(IN2,LOW);
	digitalWrite(IN3,HIGH);
	digitalWrite(IN4,LOW);

	//Timing for trigger can be chosen from INT_EDGE_FALLING, INT_EDGE_RISING, INT_EDGE_BOTH and INT_EDGE_SETUP.
	//For more details, please refer to the website of WiringPi.
	wiringPiISR(LEFT_ISR,INT_EDGE_FALLING,leftISR);
	wiringPiISR(RIGHT_ISR,INT_EDGE_RISING,rightISR);

	delay(10000);
	softPwmWrite(ENA,0);
	digitalWrite(IN1,LOW);
	digitalWrite(IN2,LOW);
	softPwmWrite(ENB,0);
	digitalWrite(IN3,LOW);
	digitalWrite(IN4,LOW);

	printf("leftISR is called %d times.\nrightISR is called %d times.\n",countLeft,countRight);
	return 0;
}
