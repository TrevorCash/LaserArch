// ArchMotor.h

#ifndef _ArchMotor_h
#define _ArchMotor_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

#define ARCH_MOTOR_BUFFER_SIZE 100
#define ARCH_MOTOR_HEALTHY_PERIOD_LOW ARCH_PIT_TIMER_FROM_USEC(12500)//80hertz
#define ARCH_MOTOR_HEALTHY_PERIOD_HIGH ARCH_PIT_TIMER_FROM_USEC(5555)//180hertz


class ArchMotor
{
 public:
	
	ArchMotor(unsigned int pwmArduinoPin);
	~ArchMotor();
 
 
 
 
	void TickPeriod(uint32_t currentTimerTime);
	boolean IsHealthy();
	void Start();
	void Stop();
	boolean WaitUntilHealthy(unsigned int millisecs);
	
	
	unsigned int AveragePeriod();
	float AngleFromTicksAve(uint32_t ticks);
	uint32_t TicksFromAngleAve(float angle);
	unsigned int LastPeriod();
	
	void SetMalfunctionState(boolean state);
	boolean GetMalfunctionState();
	
 private:
	uint32_t lastPeriod;
	uint32_t lastTick;
	unsigned int periodBuffer[ARCH_MOTOR_BUFFER_SIZE];
	unsigned int periodBufferIndx;
	unsigned int avgPeriod;
	boolean malfuncState;
	boolean powerState;
	
	unsigned int pwmPin;
 
};

#endif

