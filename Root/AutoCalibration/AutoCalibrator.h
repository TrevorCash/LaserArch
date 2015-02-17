/*
 * AutoCalibrator.h
 *
 * Created: 2/16/2015 4:39:02 PM
 *  Author: 7002815
 *
 * Desc:  Used To manage auto calibration of the note-photo transistor to set DAC value for appropriate threshold values.
 *
 *
 */ 
#ifndef AUTOCALIBRATOR_H_
#define AUTOCALIBRATOR_H_

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

class AutoCalibrator
{
	public:
		AutoCalibrator(int ADC_ARDUINO_PIN, int DAC_ARDUINO_PIN);
		~AutoCalibrator();
		
		
		void Update();
		
	private:	
		unsigned int adcPin;
		unsigned int dacPin;
		
		unsigned int currentMax;
		unsigned int currentMin;
		unsigned int currentThreshold;
};



#endif /* AUTOCALIBRATOR_H_ */