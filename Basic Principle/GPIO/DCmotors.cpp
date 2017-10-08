#include <wiringPi.h>
#include <softPwm.h>

//Pins in control of the motor on the left
const int IN1=22;
const int IN2=23;
const int ENA=24;
//Pins in control of the motor on the right
const int IN3=27;
const int IN4=28;
const int ENB=29;

int main()
{
	//Call this function at the start of any program related GPIO on RPi.
	wiringPiSetup();
	//The only PWM output is used by servo, so we need soft PWM to control rotation speed of motors.
	softPwmCreate(ENA,0,100);
	softPwmCreate(ENB,0,100);

	pinMode(IN1,OUTPUT);
	pinMode(IN2,OUTPUT);
	pinMode(IN3,OUTPUT);
	pinMode(IN4,OUTPUT);

	//Move forward
	digitalWrite(IN1,HIGH);
	digitalWrite(IN2,LOW);
	softPwmWrite(ENA,100);

	digitalWrite(IN3,HIGH);
	digitalWrite(IN4,LOW);
	softPwmWrite(ENB,100);
	delay(1000);

	//Stop
	softPwmWrite(ENA,0);
	digitalWrite(IN1,LOW);
	digitalWrite(IN2,LOW);

	softPwmWrite(ENB,0);
	digitalWrite(IN3,LOW);
	digitalWrite(IN4,LOW);
	delay(1000);

	//Move backward
	digitalWrite(IN1,LOW);
	digitalWrite(IN2,HIGH);
	softPwmWrite(ENA,100);

	digitalWrite(IN3,LOW);
	digitalWrite(IN4,HIGH);
	softPwmWrite(ENB,100);
	delay(1000);

	//Stop
	softPwmWrite(ENA,0);
	digitalWrite(IN1,LOW);
	digitalWrite(IN2,LOW);

	softPwmWrite(ENB,0);
	digitalWrite(IN3,LOW);
	digitalWrite(IN4,LOW);
	delay(1000);

	//2 motors can work at different speeds.
	digitalWrite(IN1,HIGH);
	digitalWrite(IN2,LOW);
	softPwmWrite(ENA,80);

	digitalWrite(IN3,HIGH);
	digitalWrite(IN4,LOW);
	softPwmWrite(ENB,10);
	delay(1000);

	//Stop
	softPwmWrite(ENA,0);
	digitalWrite(IN1,LOW);
	digitalWrite(IN2,LOW);

	softPwmWrite(ENB,0);
	digitalWrite(IN3,LOW);
	digitalWrite(IN4,LOW);
	delay(1000);

	//Even directions can differ from each other.
	digitalWrite(IN1,LOW);
	digitalWrite(IN2,HIGH);
	softPwmWrite(ENA,80);

	digitalWrite(IN3,HIGH);
	digitalWrite(IN4,LOW);
	softPwmWrite(ENB,10);
	delay(1000);

	//Don't forget to stop all motors before exiting.
	softPwmWrite(ENA,0);
	digitalWrite(IN1,LOW);
	digitalWrite(IN2,LOW);

	softPwmWrite(ENB,0);
	digitalWrite(IN3,LOW);
	digitalWrite(IN4,LOW);
	return 0;
}
