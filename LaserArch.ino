
//Copyright 2015 Trevor Cash, Shaun Gruenig, Linsdey Evans.

//Includes
#include <i2c_t3/i2c_t3.h>
#include <MIDI/MIDI.h>
#include "OctoWS2811Trevor.h"
#include "PrimaryDefines.h"
#include "ArchMotor.h"
#include "ArchTeensyPins.h"
#include "ArchAutoCalibrator.h"
#include "ArchMotor.h"
#include "ArchMath.h"
#include "ArchLCD.h"
#include "ArchBlobManager.h"
#include "ArchRawBlob.h"
#include "ArchFingerManager.h"
#include "ArchLedManager.h"
#include "ArchNoteManager.h"
#include "LCDMenuSetup.h"
#include "LCDMenu.h"
#include "LCDLabels.h"

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
ArchBlobManager BlobManager(&MainMotor);

//ArchRegionManager
ArchRegionManager RegionManager(REJECTION_ANGLE_MIN_DEGREES,REJECTION_ANGLE_MAX_DEGREES, &MainMotor);


//make the note manager.
ArchNoteManager NoteManager(&RegionManager);



//make a fingers manager - manage finger tracking.
ArchFingerManager FingerManager(&BlobManager, &NoteManager);



//Make an ArchLCD For Testing.
ArchLCD OrbitalLCD;





//Led Strip object
const int ledsPerStrip = 144;
DMAMEM int displayMemory[ledsPerStrip*6];
int drawingMemory[ledsPerStrip*6];
const int config = WS2811_GRB | WS2811_800kHz;
OctoWS2811 LedStrip(ledsPerStrip, displayMemory, drawingMemory, config);


ArchLedManager LedManager(&LedStrip, &RegionManager, &FingerManager);



//timers
IntervalTimer SyncTimer;
IntervalTimer CalibrationTimer;


//misc, temp
volatile uint32_t syncTimerVal = 0;
volatile uint32_t numNoteEdges = 0;
volatile uint32_t numNoteEdgesCounter = 0;
ArchRegion* debugRegion = NULL;



void setup(void) {
	Serial.begin(115200);
	
	//MIDI.begin();
	
	
	delay(1000);
	
	//Attach Interupts for the whole program
	pinMode(SYNC_PHOTOTRANSISTOR_TEENSY_PIN,INPUT);
	pinMode(NOTE_PHOTOTRANSISTOR_TEENSY_PIN,INPUT);
	pinMode(NOTE_PHOTOTRANSISTOR_ADC_TEENSY_PIN, INPUT);
	attachInterrupt(SYNC_PHOTOTRANSISTOR_TEENSY_PIN, OnSyncInterupt, FALLING);
	attachInterrupt(NOTE_PHOTOTRANSISTOR_TEENSY_PIN, OnNoteInterupt, CHANGE);
	
	//set global analog write resolution
	analogWriteResolution(ANALOG_WRITE_RES);
	analogReadResolution(16);
	
	//prepare timers.
	SyncTimer.begin(OnSyncTimerInterupt,1);//dummy statement just to get things setup
	PIT_TCTRL0 = 0x0003;
	PIT_LDVAL0 = 0xFFFFFFFF;
	
	CalibrationTimer.begin(OnCalibrationTimerInterupt,1);
	PIT_TCTRL1 = 0x00000003;
	PIT_LDVAL1 = 0xFFFFFFFF;
	
	
	//Laser Pins
	pinMode(GREEN_LASER_PWM_TEENSY_PIN,OUTPUT);
	analogWriteFrequency(GREEN_LASER_PWM_TEENSY_PIN,ARCH_TIMER_0_PWM_FREQ);
	analogWriteFrequency(MOTOR_PWM_TEENSY_PIN,ARCH_TIMER_0_PWM_FREQ);
	analogWrite(GREEN_LASER_PWM_TEENSY_PIN,0);
	
	//Dac output configure
	pinMode(NOTE_PHOTOTRANSISTOR_DAC_TEENSY_PIN,OUTPUT);
	analogWrite(NOTE_PHOTOTRANSISTOR_DAC_TEENSY_PIN, 1200);
	
	
	RegionManager.Initialize(24);
	
	
	//LCD init
	OrbitalLCD.Initialize();
	OrbitalLCD.ClearScreen();
	
	
	//LED Strip Init
	LedStrip.begin();
	LedStrip.show();
	
	
	
	
	
	
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
	
	
	
	
	FingerManager.Update();
	LedManager.Update();
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
			else if(cmd == "alloff")
			{
				analogWrite(GREEN_LASER_PWM_TEENSY_PIN,0);
				MainMotor.Stop();
			}
			else if(cmd == "allon")
			{
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
			else if(cmd == "blobinfo")
			{
				
			}
			else if (cmd == "clearscreen")
			{
				OrbitalLCD.ClearScreen();
			}
			else if (cmd == "testlabel")
			{	//Top Left Y = 0->63 X = 0->191
				LCDLabels testlabel(0, 0, 0, LABEL_CLEAR, "Hello World");
				testlabel.InitializeLabel();

				//testlabel.UpdateLabel();
				testlabel.setMode(LABEL_SELECTED);
			}
			else if (cmd == "TestMenu")
			{
				OrbitalLCD.MenuHome = DefineMenu_OperationMode();
				OrbitalLCD.Menu = OrbitalLCD.MenuHome;
				OrbitalLCD.Cursor = OrbitalLCD.MenuHome->getCursorHome();
				OrbitalLCD.Cursor->setMode(LABEL_HOVER);
				OrbitalLCD.Menu->DrawMe();
			}
			else if (cmd.startsWith("ButtonPress"))
			{
				if (cmd == "ButtonPressUp")
				{
					if (OrbitalLCD.Cursor->getMode() == LABEL_HOVER && OrbitalLCD.Cursor->getUp() != NULL)
					{
						OrbitalLCD.Cursor->setMode(LABEL_CLEAR);
						OrbitalLCD.Cursor = OrbitalLCD.Cursor->getUp();
						OrbitalLCD.Cursor->setMode(LABEL_HOVER);					
					}
					else if (OrbitalLCD.Cursor->getMode() == LABEL_SELECTED)
					{
						OrbitalLCD.Cursor->UpCommand();
					}
				}
				else if(cmd == "ButtonPressDown")
				{
					if (OrbitalLCD.Cursor->getMode() == LABEL_HOVER && OrbitalLCD.Cursor->getDown() != NULL)
					{
						OrbitalLCD.Cursor->setMode(LABEL_CLEAR);
						OrbitalLCD.Cursor = OrbitalLCD.Cursor->getDown();
						OrbitalLCD.Cursor->setMode(LABEL_HOVER);
					}
					else if (OrbitalLCD.Cursor->getMode() == LABEL_SELECTED)
					{
						OrbitalLCD.Cursor->DownCommand();
					}
				}
				else if(cmd == "ButtonPressLeft")
				{
					if (OrbitalLCD.Cursor->getMode() == LABEL_HOVER && OrbitalLCD.Cursor->getLeft() != NULL)
					{
						OrbitalLCD.Cursor->setMode(LABEL_CLEAR);
						OrbitalLCD.Cursor = OrbitalLCD.Cursor->getLeft();
						OrbitalLCD.Cursor->setMode(LABEL_HOVER);
					}
					else if (OrbitalLCD.Cursor->getMode() == LABEL_SELECTED)
					{
						OrbitalLCD.Cursor->LeftCommand();
					}
				}
				else if(cmd == "ButtonPressRight")
				{
					if (OrbitalLCD.Cursor->getMode() == LABEL_HOVER && OrbitalLCD.Cursor->getRight() != NULL)
					{
						OrbitalLCD.Cursor->setMode(LABEL_CLEAR);
						OrbitalLCD.Cursor = OrbitalLCD.Cursor->getRight();
						OrbitalLCD.Cursor->setMode(LABEL_HOVER);
					}
					else if (OrbitalLCD.Cursor->getMode() == LABEL_SELECTED)
					{
						OrbitalLCD.Cursor->RightCommand();
					}
				}
				else if(cmd == "ButtonPressEnter")
				{
					
				}
			}
			else if(cmd.startsWith("lcd:"))
			{
				
				OrbitalLCD.SendText((char*)cmd.substring(4).c_str());
			}
			else if (cmd == "getversion")
			{
				char vcmd = 0x36;
				OrbitalLCD.SendCommand(&vcmd,1);
				char d = OrbitalLCD.ReadKey();
				while(!d){}
				while(d)
				{
					Serial.println("asdasdasdasd");
					Serial.print(d);
					d = OrbitalLCD.ReadKey();
				}
			}
			else if(cmd == "regioninfo")
			{
				RegionManager.PrintRegionInfo();
			}
			else if(cmd.startsWith("getregion:"))
			{
				float ang = cmd.substring(10).toFloat();
				if(debugRegion)
					debugRegion->UpdateColors(32,32,64);
				debugRegion = RegionManager.FindRegionAtAngle(ang);
				if(debugRegion)
				{
					Serial.print("Region at Address: ");
					Serial.print((int)debugRegion);
					Serial.println(" Currently Selected.");
					debugRegion->PrintInfo();
					debugRegion->UpdateColors(64,0,0);
				}
				else
				{
					Serial.println("Unable To Find region! Non Selected!");
				}
			}
			else if(cmd.startsWith("regionstretch:"))
			{
				Serial.println("modifying...");
				float start = cmd.substring(14,17).toFloat();
				float end = cmd.substring(18,21).toFloat();
				Serial.println(start);
				Serial.println(end);
				boolean success = RegionManager.ModifyRegionSpan(debugRegion, start, end, ArchRegionManager::RegionLinearStretch);
				if(!success)
				Serial.println("failed to modify");
			}
			else if(cmd == "regionremove")
			{
				if(debugRegion)
				{
					RegionManager.RemoveRegion(debugRegion);
					Serial.println("Deleted Region!");
				}
					
				debugRegion = NULL;
				
			}
		}
		//BlobManager.LockLastBlobArray();
		//if(BlobManager.blobsArrayLastCycleSize != 1)
		//Serial.println(BlobManager.blobsArrayLastCycleSize );
		//
		//BlobManager.UnLockLastBlobArray();
		//if(BlobManager.blobsArrayLastCycleSize)
		//{	Serial.println("Blob Info:");
			//int i;
			//for(i = 0; i < BlobManager.blobsArrayLastCycleSize; i++)
			//{
				//Serial.print("Blob: ");
				//Serial.println(i);
				//Serial.print("Mid Time: ");
				//Serial.println(BlobManager.lastBlobsArray[i].midTime);
			//}
		//}
		//Serial.println(MainMotor.AveragePeriod());
		//Serial.print(uint32_t(numNoteEdges),10);
		//Serial.println("");
		//if(BlobManager.blobsArrayCurSize)
		//Serial.println(MainMotor.AngleFromTicksAve(BlobManager.blobsArray[0].midTime));
		//Serial.println(MainMotor.TicksFromAngleAve(120));
		
		//Serial.println(MainMotor.AngleFromTicksAve(BlobManager.lastBlobsArray[0].midTime));
		
		
		
		//delay(100);
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
	uint32_t currSyncTimerVal = 0xFFFFFFFF - uint32_t(PIT_CVAL0);

	NoteSensorCalibrator.OnSyncInterupt(currSyncTimerVal);
	MainMotor.TickPeriod(currSyncTimerVal);
	BlobManager.OnSyncInterupt(currSyncTimerVal);
	

	//reset timer back to "ZERO" 
	PIT_TCTRL0 = 0x0;
	PIT_LDVAL0 = 0xFFFFFFFF;
	PIT_TCTRL0 = 0x00000003;
	
	numNoteEdges = numNoteEdgesCounter;
	numNoteEdgesCounter = 0;
}
void OnNoteInterupt()
{
	uint32_t currSyncTimerVal = 0xFFFFFFFF - uint32_t(PIT_CVAL0);

	
	BlobManager.OnNoteInterupt(currSyncTimerVal, boolean(digitalReadFast(NOTE_PHOTOTRANSISTOR_TEENSY_PIN)));
	
	NoteSensorCalibrator.OnNoteInterupt(currSyncTimerVal);
	
	numNoteEdgesCounter++;
}





//TIMER INTERUPTS
void OnSyncTimerInterupt()
{
	//should never get called if motor is running AND laser is on.  
	//but if there is either a motor malfunction or laser malfunction this will trigger eventually.
	//Serial.println("GACK!");
}


void OnCalibrationTimerInterupt()
{
	NoteSensorCalibrator.OnCalibrationTimerInterupt();	
}