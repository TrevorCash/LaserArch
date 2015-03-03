//Copywrite 2015 Trevor Cash, Shaun Gruenig, Linsdey Evans.

//Includes
#include "PrimaryDefines.h"
#include "ArchMotor.h"
#include "ArchTeensyPins.h"
#include "ArchAutoCalibrator.h"
#include "ArchMotor.h"
#include "ArchMath.h"

//Proto-types
////////////////////////////
void MainLoop();
void SystemTestLoop(); //seperate main loop for system test mode.
void MainSetup();
void SystemTestSetup();//seperate setup for system test mode.
//Interupt Functions
void OnSyncInterupt();
void OnNoteInterupt();

//Make a note calibrator to manage the auto-calibration
ArchAutoCalibrator NoteSensorCalibrator(NOTE_PHOTOTRANSISTOR_ADC_TEENSY_PIN,
										NOTE_PHOTOTRANSISTOR_DAC_TEENSY_PIN);

//Make a motor manager to manage motor control and diagnostics
ArchMotor MainMotor(MOTOR_PWM_TEENSY_PIN);

//make a note region manager to manage the dynamic note regions.



void setup(void) {
	Serial.begin(115200);
	
	//Attach Interupts for the whole program
	attachInterrupt(SYNC_PHOTOTRANSISTOR_TEENSY_PIN, OnSyncInterupt, RISING);
	attachInterrupt(NOTE_PHOTOTRANSISTOR_TEENSY_PIN, OnNoteInterupt, CHANGE);
	
	//Laser Pins
	pinMode(BLUE_LASER_PWM_TEENSY_PIN,OUTPUT);
	pinMode(GREEN_LASER_PWM_TEENSY_PIN,OUTPUT);
	analogWriteFrequency(BLUE_LASER_PWM_TEENSY_PIN,500000);
	analogWriteFrequency(GREEN_LASER_PWM_TEENSY_PIN,500000);
	analogWrite(BLUE_LASER_PWM_TEENSY_PIN,BLUE_LASER_PWM_DUTY_CYCLE_ON);
	analogWrite(GREEN_LASER_PWM_TEENSY_PIN,GREEN_LASER_PWM_DUTY_CYCLE_ON);
	
	#ifdef CORE_SYSTEM_TEST_MODE
		SystemTestSetup();
	#else
		MainSetup();
	#endif
}

void loop()
{
	#ifdef CORE_SYSTEM_TEST_MODE
		SystemTestLoop();
	#else
		MainLoop();
	#endif
}



void SystemTestSetup()
{
	delay(1000);
	Serial.println("ARCH IN TEST MODE:");
	
	MainMotor.Start();
}

void SystemTestLoop()
{
		//GetInputFromTerminal
		while(Serial.available())
		{
			String cmd = Serial.readStringUntil('\n');
			if(cmd == "motoroff")
			{
				MainMotor.Stop();
			}
			else if(cmd == "motoron")
			{
				MainMotor.Start();
			}
			else if(cmd == "greenon")
			{
				analogWrite(GREEN_LASER_PWM_TEENSY_PIN,GREEN_LASER_PWM_DUTY_CYCLE_ON);
			}
			else if(cmd == "greenoff")
			{
				analogWrite(GREEN_LASER_PWM_TEENSY_PIN,GREEN_LASER_PWM_DUTY_CYCLE_OFF);
			}
			else if(cmd == "blueon")
			{
				analogWrite(BLUE_LASER_PWM_TEENSY_PIN,BLUE_LASER_PWM_DUTY_CYCLE_ON);
			}
			else if(cmd == "blueoff")
			{
				analogWrite(BLUE_LASER_PWM_TEENSY_PIN,BLUE_LASER_PWM_DUTY_CYCLE_OFF);

			}
			else if(cmd == "lasersoff")
			{
				analogWrite(BLUE_LASER_PWM_TEENSY_PIN,BLUE_LASER_PWM_DUTY_CYCLE_OFF);
				analogWrite(GREEN_LASER_PWM_TEENSY_PIN,GREEN_LASER_PWM_DUTY_CYCLE_OFF);
			}
			else if(cmd == "laserson")
			{
				analogWrite(BLUE_LASER_PWM_TEENSY_PIN,BLUE_LASER_PWM_DUTY_CYCLE_ON);
				analogWrite(GREEN_LASER_PWM_TEENSY_PIN,GREEN_LASER_PWM_DUTY_CYCLE_ON);
			}
			else if(cmd == "alloff")
			{
				analogWrite(BLUE_LASER_PWM_TEENSY_PIN,0);
				analogWrite(GREEN_LASER_PWM_TEENSY_PIN,0);
				MainMotor.Stop();
			}
			else if(cmd == "allon")
			{
				analogWrite(BLUE_LASER_PWM_TEENSY_PIN,BLUE_LASER_PWM_DUTY_CYCLE_ON);
				analogWrite(GREEN_LASER_PWM_TEENSY_PIN,GREEN_LASER_PWM_DUTY_CYCLE_ON);
				MainMotor.Start();
			}
		}
		
	
		Serial.print("Motor Healthy: ");
		Serial.println(MainMotor.IsHealthy());
		delay(100);
}


void MainSetup()
{
	
}


void MainLoop()
{
}





/////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////
void OnSyncInterupt()
{
	
}
void OnNoteInterupt()
{
	
}