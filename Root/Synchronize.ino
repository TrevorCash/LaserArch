
//Copywrite 2015 Trevor Cash, Shaun Gruenig, Linsdey Evans.

//proto-type
inline void RestartTimer(int timerID, unsigned int count);
inline void DisableTimer(int timerID);



const int laserPin = 3;  // the pin with a LED
const int phototransistorPin = 20;

const unsigned int laserOnDutyCycle = 110;
const unsigned int laserOFFDutyCycle = 30;
volatile unsigned char laserState = 1; //1 is on, 0 is off..


struct TimingStats
{
	unsigned int curMotorPeriodTicks = 0;	

};

volatile TimingStats SystemTiming;

IntervalTimer MotorTimer;
IntervalTimer LaserTimer;
IntervalTimer TestTimer;




volatile int timerCausedBadInterrupt = 0;

volatile int stripes;


void setup(void) {
	pinMode(phototransistorPin, INPUT);
	pinMode(laserPin,OUTPUT);
	
	analogWriteFrequency(laserPin, 375000);
	analogWrite(laserPin, laserOnDutyCycle);
	
	attachInterrupt(phototransistorPin, syncPulseInterrupt, FALLING);

	//Setup the Motor Interuppt
	MotorTimer.begin(UnusedInterrupt,200000);
	RestartTimer(0,0xFFFFFFFF);
	
	//setup the laser timer
	LaserTimer.begin(LaserInterrupt,200000);
	DisableTimer(1);
	
	//setup a test Timer.
	TestTimer.begin(UnusedInterrupt,2000);
	RestartTimer(2,0xFFFFFFFF);
	
	
	Serial.begin(115200);
}

void loop()
{
	//Serial.println(SystemTiming.curMotorPeriodTicks);
	delay(1000);
	
	
	Serial.println(PIT_CVAL2);

	RestartTimer(2,0xFFFFFFFF);

}

//PHOTOTRANSISTOR
void syncPulseInterrupt( void )
{
	
	SystemTiming.curMotorPeriodTicks = 0xFFFFFFFF - PIT_CVAL0;
	RestartTimer(0, 0xFFFFFFFF);

	//turn off laser.
	analogWrite(laserPin, laserOFFDutyCycle);
	stripes = 14;
	//Setup the laser timer
	RestartTimer(1, 20000);
	
}

//Interupt for when the laser needs to turn on/or off
void LaserInterrupt( void )
{
	
		stripes--;
	
		if(stripes % 2)
			analogWrite(laserPin,laserOFFDutyCycle);
		else
			analogWrite(laserPin,laserOnDutyCycle);
		
		if(stripes <= 0)
		{
			analogWrite(laserPin,laserOnDutyCycle);
			DisableTimer(1);
		}
}

void UnusedInterrupt( void)
{

}


inline void RestartTimer(int timerID, unsigned int count)
{
	if(timerID == 2)
	{
		PIT_LDVAL2 = count;
		if((PIT_TCTRL2 & 0x1))
		{
			PIT_TCTRL2 ^= 0x1;
			PIT_TCTRL2 ^= 0x1;
		}
		else
		{
			PIT_TCTRL2 ^= 0x1;
		}
	}
	else if(timerID == 1)
	{
		PIT_LDVAL1 = count;
		if((PIT_TCTRL1 & 0x1))
		{
			PIT_TCTRL1 ^= 0x1;
			PIT_TCTRL1 ^= 0x1;
		}
		else
		{
			PIT_TCTRL1 ^= 0x1;
		}
	}
	else if(timerID == 0)
	{
		PIT_LDVAL0 = count;
		if((PIT_TCTRL0 & 0x1))
		{
			PIT_TCTRL0 ^= 0x1;
			PIT_TCTRL0 ^= 0x1;
		}
		else
		{
			PIT_TCTRL0 ^= 0x1;
		}
	}
	else if(timerID == 3)
	{
		PIT_LDVAL3 = count;
		if((PIT_TCTRL3 & 0x1))
		{
			PIT_TCTRL3 ^= 0x1;
			PIT_TCTRL3 ^= 0x1;
		}
		else
		{
			PIT_TCTRL3 ^= 0x1;
		}
	}
}


inline void DisableTimer(int timerID)
{
	if(timerID == 2)
	{
		if((PIT_TCTRL2 & 0x1))
		{
			PIT_TCTRL2 ^= 0x1;
		}
	}
	else if(timerID == 1)
	{
		if((PIT_TCTRL1 & 0x1))
		{
			PIT_TCTRL1 ^= 0x1;
		}
	}
	else if(timerID == 0)
	{
		if((PIT_TCTRL0 & 0x1))
		{
			PIT_TCTRL0 ^= 0x1;
		}
	}
	else if(timerID == 3)
	{
		if((PIT_TCTRL3 & 0x1))
		{
			PIT_TCTRL3 ^= 0x1;
		}
	}
}