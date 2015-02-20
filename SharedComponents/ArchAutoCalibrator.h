// AutoCalibrator.h

#ifndef _AUTOCALIBRATOR_h
#define _AUTOCALIBRATOR_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

class ArchAutoCalibrator
{
 public:
	 ArchAutoCalibrator(int ADC_ARDUINO_PIN, int DAC_ARDUINO_PIN);
	 ~ArchAutoCalibrator();
 
 
 void Update();
 
 private:
	 unsigned int adcPin;
	 unsigned int dacPin;
 
	 unsigned int currentMax;
	 unsigned int currentMin;
	 unsigned int currentThreshold;
};


#endif

