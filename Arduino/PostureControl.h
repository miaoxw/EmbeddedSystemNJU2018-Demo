#ifndef _POSTURECONTROL_h
#define _POSTURECONTROL_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif
namespace PostureControl
{
	void turnLeftALittle();
	void turnRightALittle();
}
#endif
