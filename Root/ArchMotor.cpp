// 
// 
// 

#include "ArchMotor.h"
#include "ArchMath.h"


ArchMotor::ArchMotor(unsigned int pwmArduinoPin)
{
	periodBufferIndx = 0;
	malfuncState = false;
	avgPeriod = 0;
	lastPeriod = 0;
	lastTick = 0;
	powerState = false;//motors off by default
	
	pwmPin = pwmArduinoPin;
}
ArchMotor::~ArchMotor()
{
	
}


//Called Directly from the sync interrupt.
inline void ArchMotor::TickPeriod(unsigned int currentTimerTime)
{
	if(currentTimerTime < lastTick)
		SetMalfunctionState(true);
	
	lastPeriod = currentTimerTime - lastTick;
	periodBuffer[periodBufferIndx] = lastPeriod;
	periodBufferIndx++;
	periodBufferIndx = periodBufferIndx % ARCH_MOTOR_BUFFER_SIZE;
}

boolean ArchMotor::IsHealthy()
{
	if(powerState == false)//if the motor is purposfully off, we dont know if its healthy or not. so assume it is!
	{
		return true;
	}
	
	if((avgPeriod >= ARCH_MOTOR_HEALTHY_PERIOD_LOW) && (avgPeriod <= ARCH_MOTOR_HEALTHY_PERIOD_HIGH) && (!malfuncState) && powerState)
		return true;
	else
		return false;
}

void ArchMotor::Start()
{
	powerState = true;
	analogWrite(pwmPin,255);
}
void ArchMotor::Stop()
{
	powerState = false;
	analogWrite(pwmPin,0);
}

//Block until motor is healthy - DOES NOT STOP GLOBAL INTERRUPTS
//returns false if timeout.
boolean ArchMotor::WaitUntilHealthy(unsigned int millisecs)
{
	unsigned int i = 0;
	while(!IsHealthy() and i < millisecs)
	{
		delay(1);
		i++;
	}
	if(i >= millisecs)
		return false;
	
	return true;
}

inline unsigned int ArchMotor::AveragePeriod()
{
	return avgPeriod;
}

inline unsigned int ArchMotor::LastPeriod()
{
	return lastPeriod;
}


inline void ArchMotor::SetMalfunctionState(boolean state)
{
	malfuncState = state;
}

inline boolean ArchMotor::GetMalfunctionState()
{
	return malfuncState;
}