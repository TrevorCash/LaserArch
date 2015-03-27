// AutoCalibrator.h

#ifndef _AUTOCALIBRATOR_h
#define _AUTOCALIBRATOR_h

#include "ArchMotor.h"

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

#define ARCH_CALIBRATOR_NUM_SAMPLES 200
#define ARCH_CALIBRATOR_NUM_AVERAGES 32



class ArchAutoCalibrator
{
 public:
	 ArchAutoCalibrator(int ADC_ARDUINO_PIN, int DAC_ARDUINO_PIN, ArchMotor* Motor);
	 ~ArchAutoCalibrator();
 
 
 void Update();//Update From Main Loop
 void OnSyncInterupt(uint32_t currentTime);//call in the Sync Interuppt
 void OnNoteInterupt(uint32_t currentTimerTime);//call in the note interuppt.
 void OnCalibrationTimerInterupt();//call in the calib timer interupt.
 
 
 
 void SetIsCalibrating(boolean c)
 {
	 isCalibrating = c;
	 characteristicBuffAvgIteration = 0;

	 //clear buffer
	 int i;
	 for(i = 0; i < ARCH_CALIBRATOR_NUM_SAMPLES; i++)
		characteristicBuff[i] = 0;
		
	 characteristicBuffMax = -50000;
	 characteristicBuffMin = 50000;
		
	 Serial.println("Calibrating...");
}
 boolean IsCalibrating(){return isCalibrating;}
	
void PrintCharacteristicBuff()
{
	int i;
	Serial.println("BUFFER START:");
	for(i = 0; i < ARCH_CALIBRATOR_NUM_SAMPLES; i++)
		Serial.println(characteristicBuff[i]);	
}
	 

 
 private:
	 unsigned int adcPin;
	 unsigned int dacPin;
 
	 unsigned int currentMax;
	 unsigned int currentMin;
	 unsigned int currentThreshold;
	 
	 
	 boolean isCalibrating;
	 
	 int32_t characteristicBuff[ARCH_CALIBRATOR_NUM_SAMPLES];
	 int32_t characteristicBuffMax;
	 int32_t characteristicBuffMin;
	 uint16_t characteristicBuffIndx;
	 uint16_t characteristicBuffAvgIteration;
	 
	 int32_t notePhotoLevelAmbient;
	 
	 ArchMotor* Motor;

};


#endif

