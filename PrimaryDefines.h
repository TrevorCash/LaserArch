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
#define MAX_BLOBS 30

//maximum number of finger to track!
#define MAX_FINGERS 15

#define MAX_FINGER_VALIDITY 2
#define MIN_FINGER_VALIDITY 0

//finger-region hysteresis
#define FINGER_REGION_HYSTERESIS_MAX_DEG 0.5
#define FINGER_REGION_HYSTERESIS_MIN_RATIO_OF_SPAN 0.25

//width modulation limits
#define FINGER_EXPECTED_WIDTH_IN_PLAYABLE_REGION_DEG 4.0 //this should be tweeked to the average finger playing where humans like to play (used as reference);
#define FINGER_WIDTH_MODULATION_MAX_CHANGE_DEG 6.0 //modulation should max out when width varies from original to +- this define.
#define FINGER_WIDTH_MODULATION_MIN_DEG (FINGER_EXPECTED_WIDTH_IN_PLAYABLE_REGION_DEG/2.0)


//maximum regions avalable.
#define  MAX_REGIONS 100

//minimum region size.
#define MIN_REGION_SIZE_DEG 0.2


//angle offset of sync phototransistor (use this to counter time constant or physical offset of the sync photo-transistor
#define SYNC_PHYSICAL_OFFSET_DEGREES 0

//min max cutoff angles (any note edges are immediatly discarded if out of this range (used to get rid of strange edge behaviors)
#define REJECTION_ANGLE_MIN_DEGREES 70
#define REJECTION_ANGLE_MAX_DEGREES 290

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


//Led Strip
//literal start and end angles of led strip
#define LED_STRIP_START_DEG 71
#define LED_STRIP_END_DEG 250


//LCD Types and Modes

//Label Types
#define LABEL_MENU_PTR		1
#define LABEL_PLAIN_TEXT	2
#define LABEL_VALUE_NUMBER	3
#define LABEL_VALUE_NOTE	4
#define LABEL_VALUE_COLOR	5
#define LABEL_VALUE_SCALE	6

//Label Modes
#define LABEL_CLEAR			0
#define LABEL_HOVER			1
#define LABEL_SELECTED		2

//LCD Button Values//
#define LCD_BACK			65
#define LCD_HOME			71
#define LCD_ENTER			69
#define LCD_UP				66
#define LCD_DOWN			72
#define LCD_RIGHT			67
#define LCD_LEFT			68

//Menu Indicators//
#define MENU_NONE			0
#define MENU_CHROMATIC		1
#define MENU_CUSTOM			2
#define MENU_CUSTOM_REGION	3
#define MENU_PITCHBENDING	4
#define MENU_SCALE			5

//Colors//
#define COLOR_RED			0
#define COLOR_BLUE			1
#define COLOR_GREEN			2
#define COLOR_CYAN			3

//Scale//
#define SCALE_NONE			0
#define SCALE_MAJOR			1
#define SCALE_MINOR			2


#endif /* PRIMARYDEFINES_H_ */