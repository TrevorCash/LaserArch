/*
 * ArchTeensyPins.h
 *
 * Created: 2/17/2015 9:31:52 AM
 *  Author: 7002815
 */ 

//Here we define common names for pins on the teensy board (ARDUINO PINS, not internal uc pins!)

#ifndef ARCHTEENSYPINS_H_
#define ARCHTEENSYPINS_H_

#include "pins_arduino.h"

#define NOTE_PHOTOTRANSISTOR_ADC_TEENSY_PIN		22
#define NOTE_PHOTOTRANSISTOR_DAC_TEENSY_PIN		A14
#define NOTE_PHOTOTRANSISTOR_TEENSY_PIN			21

#define SYNC_PHOTOTRANSISTOR_TEENSY_PIN			23

#define GREEN_LASER_PWM_TEENSY_PIN				3
#define BLUE_LASER_PWM_TEENSY_PIN				25

#define MOTOR_PWM_TEENSY_PIN					6



#endif /* ARCHTEENSYPINS_H_ */