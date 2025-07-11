/*
 * CVMS_Defines.h
 *
 * Created: 04-06-2023 00:46:31
 *  Author: Amol Jadhav
 */ 


#ifndef CVMS_Defines_H
#define CVMS_Defines_H


/***************** String Definations *****************/
#define STRING_EOL    "\r"
/*#define STRING_HEADER "-- Getting Started Example --\r\n" \
"-- "BOARD_NAME" --\r\n" \
"-- Compiled: "__DATE__" "__TIME__" --\r\n" \
"-- Pressing and release button SW0 should make LED0 on and off --"STRING_EOL*/
#define STRING_HEADER "-- Compiled: "__DATE__" "__TIME__" --"STRING_EOL
#define STRING_SEPERATOR(); sio2host_tx((uint8_t *)", ",2);

/***************** Timer Counter Sleep Definations *****************/
#define TC_COUNT_VALUE 34441

#define SLEEP_TIME 6 // Seconds
#define ANALOG_SETTLE_mS 50	//Time required for Analog circuit to settle

/***************** Define Pin Digital Inputs *****************/
#define DI1_PIN                  PIN_PA14
#define DI2_PIN					 PIN_PA15
#define DI3_PIN					 PIN_PA16
#define DI4_PIN					 PIN_PA17
//#define ANA_ACTIVE               false
//#define ANA_INACTIVE             !ANA_ACTIVE

/***************** Define Pin for Transmission LED *****************/
#define LEDTx_PIN                  PIN_PA19
#define LEDTx_ACTIVE               true
#define LEDTx_INACTIVE             !LEDTx_ACTIVE

/***************** Define Pin for Sleep Interval configuration *****************/
//#define INTERVAL_PIN1                  PIN_PA15
//#define INTERVAL_PIN2                  PIN_PA27
//#define CONTINUOUS_TX_PIN              PIN_PA28

enum sleep_interval_enum{
	sleep_15m = 60*15,		// Pin1 = 0, Pin2 = 0
	sleep_1m = 60*1,		// Pin1 = 0, Pin2 = 1
	sleep_2m = 60*2,		// Pin1 = 1, Pin2 = 0
	sleep_5m = 60*5,		// Pin1 = 1, Pin2 = 1
	};

void CVMS_HandleMessage(void);
void ReadInterval(void);

/***************** Timer *****************/


/***************** Timer *****************/





#endif /* INCFILE1_H_ */