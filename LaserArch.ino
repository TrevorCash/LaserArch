#include "ArchMotor.h"
//Copywrite 2015 Trevor Cash, Shaun Gruenig, Linsdey Evans.

#include "ArchTeensyPins.h"
#include "ArchAutoCalibrator.h"
#include "ArchMotor.h"
#include "ArchMath.h"

//Make a note calibrator to manage the auto-calibration
ArchAutoCalibrator NoteSensorCalibrator(NOTE_PHOTOTRANSISTOR_ADC_TEENSY_PIN,
										NOTE_PHOTOTRANSISTOR_DAC_TEENSY_PIN);

//Make a motor manager to manage motor control and diagnostics
ArchMotor MainMotor(MOTOR_PWM_TEENSY_PIN);

//make a note region manager to manage the dynamic note regions.



void setup(void) {
	Serial.begin(115200);
	
	
	MainMotor.Start();
	MainMotor.WaitUntilHealthy(1000);
}

void loop()
{
	Serial.println(ARCH_MOTOR_HEALTHY_PERIOD_LOW);
	
	delay(1000);
	//update Note Sensor Calibrator.
	//NoteSensorCalibrator.Update();
}
