/*
 * PrimaryDefines.h
 *
 * Created: 2/17/2015 9:28:18 AM
 *  Author: 7002815
 */ 


#ifndef PRIMARYDEFINES_H_
#define PRIMARYDEFINES_H_

//Define if you want readable midi messages to the uart at a more standard baud rate
#define MIDI_DEBUG_MODE

//Define if you want to enable the core system test mode - usefull for calibrating?
#define CORE_SYSTEM_TEST_MODE

//PWM Frequencies
#define ARCH_TIMER_0_PWM_FREQ 250000

//Laser Pwm Values
#define GREEN_LASER_PWM_DUTY_CYCLE_ON 1000
#define GREEN_LASER_PWM_DUTY_CYCLE_OFF 500
#define BLUE_LASER_PWM_DUTY_CYCLE_ON 1606
#define BLUE_LASER_PWM_DUTY_CYCLE_OFF 0

//Matrix Orbital 7bit I2C Slave Address.
#define ORBITAL_I2C_ADDRESS 0x28






#endif /* PRIMARYDEFINES_H_ */