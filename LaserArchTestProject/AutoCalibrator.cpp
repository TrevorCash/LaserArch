/*
 * AutoCalibrator.cpp
 *
 * Created: 2/16/2015 4:38:45 PM
 *  Author: 7002815
 */ 

#include "AutoCalibrator.h"

//public methods:
AutoCalibrator::AutoCalibrator(int ADC_ARDUINO_PIN, int DAC_ARDUINO_PIN)
{
	
	adcPin = ADC_ARDUINO_PIN;
	dacPin = DAC_ARDUINO_PIN;
	
	currentThreshold = 2048; // half of 2^12 which is dac resolution.
	currentMin = 0;
	currentMax = 4096;
}


AutoCalibrator::~AutoCalibrator()
{
	
}


//Called From Main Loop Periodically
//to instantly take single ADC reading and update the appropriate DAC value.
void AutoCalibrator::Update()
{
	//obtain a sample from the ADC 
	unsigned int sampleVal = analogRead(adcPin);
	
	//keep the value as either a max or min.
	if( sampleVal > currentThreshold)
	{
		currentMax = sampleVal;
	}
	else
	{
		currentMin = sampleVal;
	}
	
	//update threshold as simple average of max and min.
	currentThreshold = (currentMax + currentMin) >> 1;
	
	//output the threshold
	analogWrite(dacPin, currentThreshold);
}



//private methods