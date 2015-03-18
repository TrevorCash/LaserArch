
//Copywrite 2015 Trevor Cash, Shaun Gruenig, Linsdey Evans.

//Includes
#include <i2c_t3/i2c_t3.h>
#include "PrimaryDefines.h"
#include "ArchMotor.h"
#include "ArchTeensyPins.h"
#include "ArchAutoCalibrator.h"
#include "ArchMotor.h"
#include "ArchMath.h"
#include "ArchLCD.h"

//Proto-types
////////////////////////////
void MainLoop();
void SystemTestLoop(); //seperate main loop for system test mode.
void MainSetup();
void SystemTestSetup();//seperate setup for system test mode.

void OnSyncInterupt();
void OnNoteInterupt();
void OnSyncTimerInterupt();
void OnCalibrationTimerInterupt();


//Make a motor manager to manage motor control and diagnostics
ArchMotor MainMotor(MOTOR_PWM_TEENSY_PIN);


//Make a note calibrator to manage the auto-calibration
ArchAutoCalibrator NoteSensorCalibrator(NOTE_PHOTOTRANSISTOR_ADC_TEENSY_PIN,
										NOTE_PHOTOTRANSISTOR_DAC_TEENSY_PIN,
										&MainMotor);



//make a note region manager to manage the dynamic note regions.

//Make an ArchLCD For Testing.
ArchLCD OrbitalLCD;


//timers
IntervalTimer SyncTimer;
IntervalTimer CalibrationTimer;


//misc
volatile uint32_t syncTimerVal = 0;



void setup(void) {
	Serial.begin(115200);
	delay(1000);
	//Attach Interupts for the whole program
	pinMode(SYNC_PHOTOTRANSISTOR_TEENSY_PIN,INPUT);
	pinMode(NOTE_PHOTOTRANSISTOR_TEENSY_PIN,INPUT);
	pinMode(NOTE_PHOTOTRANSISTOR_ADC_TEENSY_PIN, INPUT);
	attachInterrupt(SYNC_PHOTOTRANSISTOR_TEENSY_PIN, OnSyncInterupt, FALLING);
	attachInterrupt(NOTE_PHOTOTRANSISTOR_TEENSY_PIN, OnNoteInterupt, CHANGE);
	
	//set global analog write resolution
	analogWriteResolution(12);
	analogReadResolution(16);
	
	//prepare timers.
	SyncTimer.begin(OnSyncTimerInterupt,1);//dummy statement just to get things setup
	PIT_TCTRL0 = 0x0003;
	PIT_LDVAL0 = 0xFFFFFFFF;
	
	CalibrationTimer.begin(OnCalibrationTimerInterupt,1);
	PIT_TCTRL1 = 0x00000003;
	PIT_LDVAL1 = 0xFFFFFFFF;
	
	
	//Laser Pins
	pinMode(BLUE_LASER_PWM_TEENSY_PIN,OUTPUT);
	pinMode(GREEN_LASER_PWM_TEENSY_PIN,OUTPUT);
	analogWriteFrequency(BLUE_LASER_PWM_TEENSY_PIN,250000);
	analogWriteFrequency(GREEN_LASER_PWM_TEENSY_PIN,250000);
	analogWrite(BLUE_LASER_PWM_TEENSY_PIN,0);
	analogWrite(GREEN_LASER_PWM_TEENSY_PIN,0);
	
	//Dac output configure
	pinMode(NOTE_PHOTOTRANSISTOR_DAC_TEENSY_PIN,OUTPUT);
	
	
	
	//LCD init
	//OrbitalLCD.Initialize();
	//OrbitalLCD.ClearScreen();
	
	
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
	
	Serial.println("ARCH IN TEST MODE:");
	//OrbitalLCD.SendText("Arch In Test Mode!");

	
}

void SystemTestLoop()
{
		////Simple LCD Test Ruitine
		//char key = OrbitalLCD.ReadKey();
		//while(key)
		//{
			//if(key == 'A')
				//OrbitalLCD.ClearScreen();
			////if(key == 'B')
			////	OrbitalLCD.UpdateLabel(1,"duhhhh");
				//
			//OrbitalLCD.SendChar(key);
			//
			//key = OrbitalLCD.ReadKey();
		//}
	//
	//
	//ArchInterfaceManager.Update();
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
			else if(cmd.startsWith("dac"))
			{
				String dacValStr = cmd.substring(3);
				int val = dacValStr.toInt();
				Serial.print("Setting Dac Val to: ");
				Serial.println(val);
				analogWrite(NOTE_PHOTOTRANSISTOR_DAC_TEENSY_PIN, val);
			}
			else if(cmd == "calib")
			{
				NoteSensorCalibrator.SetIsCalibrating(true);
			}
			else if(cmd == "printcalib")
			{
				NoteSensorCalibrator.PrintCharacteristicBuff();	
			}
		}
		//Serial.println(MainMotor.AveragePeriod());

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
	syncTimerVal = 0xFFFFFFFF - uint32_t(PIT_CVAL0);

	NoteSensorCalibrator.OnSyncInterupt(syncTimerVal);
	MainMotor.TickPeriod(syncTimerVal);
	
	

	//delay(2);


	//reset timer back to "ZERO" 
	PIT_TCTRL0 = 0x0;
	PIT_LDVAL0 = 0xFFFFFFFF;
	PIT_TCTRL0 = 0x00000003;
}
void OnNoteInterupt()
{
	NoteSensorCalibrator.OnNoteInterupt();
}





//TIMER INTERUPTS
void OnSyncTimerInterupt()
{
	//should never get called if motor is running AND lasers are on.
	//Serial.println("GACK!");
}


void OnCalibrationTimerInterupt()
{
	NoteSensorCalibrator.OnCalibrationTimerInterupt();	
}