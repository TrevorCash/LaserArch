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

//maximum number of blobss to track!
#define  MAX_BLOBS 30

//maximum number of finger to track!
#define MAX_FINGERS 15

//angle offset of sync phototransistor (use this to counter time constant or physical offset of the sync photo-transistor
#define SYNC_PHYSICAL_OFFSET_DEGREES 0

//min max cutoff angles (any note edges are immediatly discarded if out of this range (used to get rid of strange edge behaviors)
#define REJECTION_ANGLE_MIN_DEGREES 100
#define REJECTION_ANGLE_MAX_DEGREES 260

//global analog write resolution
#define ANALOG_WRITE_RES 12
#define ANALOG_WRITE_MAXVAL ((1 << ANALOG_WRITE_RES) - 1)





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