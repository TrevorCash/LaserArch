/*
 * AutoCalibrator.cpp
 *
 * Created: 2/16/2015 4:38:45 PM
 *  Author: 7002815
 */ 

#include "ArchAutoCalibrator.h"
#include "PrimaryDefines.h"
#include "ArchTeensyPins.h"
#include "ArchMath.h"
#include "ArchMotor.h"


//public methods:
ArchAutoCalibrator::ArchAutoCalibrator(int ADC_ARDUINO_PIN, int DAC_ARDUINO_PIN, ArchMotor* Motor)
{
	
	adcPin = ADC_ARDUINO_PIN;
	dacPin = DAC_ARDUINO_PIN;
	this->Motor = Motor;
	
	currentThreshold = 2048; // half of 2^12 which is dac resolution.
	currentMin = 0;
	currentMax = 4096;
	
	isCalibrating = false;
	characteristicBuffIndx = 0;
	characteristicBuffAvgIteration = 0;
	notePhotoLevelAmbient = 0;
	characteristicBuffMax = -50000;
	characteristicBuffMin = 50000;
}


ArchAutoCalibrator::~ArchAutoCalibrator()
{
	
}


//Called From Main Loop Periodically
//to instantly take single ADC reading and update the appropriate DAC value.
void ArchAutoCalibrator::Update()
{
}

void ArchAutoCalibrator::OnSyncInterupt(uint32_t currentTime)//call in the Sync Interuppt
{
	//Serial.println("AUto cal sync triggered!");
	notePhotoLevelAmbient = analogRead(NOTE_PHOTOTRANSISTOR_ADC_TEENSY_PIN);
	//analogWrite(NOTE_PHOTOTRANSISTOR_DAC_TEENSY_PIN, notePhotoLevelAmbient*4 + 125);

	characteristicBuffIndx = 0;
	
	
	
	uint32_t sampleTime;
	if(Motor->AveragePeriod() < ARCH_MOTOR_HEALTHY_PERIOD_LOW)
		sampleTime = currentTime;
	else
		sampleTime =  Motor->AveragePeriod()/ARCH_CALIBRATOR_NUM_SAMPLES;	
		
	//setup/restart sampling timer (PIT1)
	PIT_TCTRL1 = 0x0;
	PIT_LDVAL1 = sampleTime;
	PIT_TCTRL1 = 0x3;

}
void ArchAutoCalibrator::OnNoteInterupt(uint32_t currentTimerTime)//call in the note interuppt.
{
	//Serial.println("AUto cal note triggered!");
	
}

void ArchAutoCalibrator::OnCalibrationTimerInterupt()//call in the calib timer interupt.
{
	if(isCalibrating)
	{
		//take a sample and add to characteristicBuffer
		characteristicBuff[characteristicBuffIndx] += (analogRead(NOTE_PHOTOTRANSISTOR_ADC_TEENSY_PIN) - notePhotoLevelAmbient)/ARCH_CALIBRATOR_NUM_AVERAGES;	
	}
	else
	{
		//write to dac based off characteristicBuffer.
		int32_t characteristicVal = characteristicBuff[characteristicBuffIndx];
		int32_t passingThreshold = (characteristicBuffMax - characteristicBuffMin)*0.5 - 3000;
		int32_t dacThreshold;
		
		
		if(characteristicVal > passingThreshold)
			dacThreshold = characteristicVal - 9000;
		else
			dacThreshold = characteristicVal;
			////dacThreshold = (characteristicBuffMax - characteristicBuffMin)*0.4;
		
		//dacThreshold = (characteristicBuffMax + characteristicBuffMin)*0.5;
		//dacThreshold = passingThreshold;
		//if(dacThreshold < 0)
			//dacThreshold = 0;	
			
	//analogWrite(NOTE_PHOTOTRANSISTOR_DAC_TEENSY_PIN, (dacThreshold + notePhotoLevelAmbient) >> 4);
		
	}
	
	characteristicBuffIndx++;
	if(characteristicBuffIndx >= ARCH_CALIBRATOR_NUM_SAMPLES)
	{
		characteristicBuffIndx = 0;
		
		if(isCalibrating)
		{
			characteristicBuffAvgIteration++;
			if(characteristicBuffAvgIteration >= ARCH_CALIBRATOR_NUM_AVERAGES)
			{
				isCalibrating = false;
				
				int i;
				for(i = 0; i < ARCH_CALIBRATOR_NUM_SAMPLES; i++)
				{
					if(characteristicBuff[i] > characteristicBuffMax)
					characteristicBuffMax = characteristicBuff[i];
					else if(characteristicBuff[i] < characteristicBuffMin)
					characteristicBuffMin = characteristicBuff[i];
				}
				
				
				Serial.println("Calibration Finished");
			}
		}
	}
}

//private methods