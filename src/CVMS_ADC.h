/*
 * IncFile1.h
 *
 * Created: 04-06-2023 00:17:52
 *  Author: Amol Jadhav
 */ 


#ifndef CVMS_ADC_H_INCLUDED
#define CVMS_ADC_H_INCLUDED

#include <stdint.h>

#define ADC_SAMPLES 5

uint8_t CVMS_MACid[16];

void configure_adc(void);
void configure_adc_callbacks(void);
void configure_adc_IRQ(void);
void adcReadPrint(void);

void configure_AIN1(void);	//PA04
void configure_AIN2(void);	//PA05
void configure_AIN3(void);	//PA06
void configure_AIN4(void);	//PA08
//void configure_AIN5(void);

void TXLed(bool);
//void analogCircuit(bool);
void analogDelay(uint32_t);
void convertToString(const uint16_t adc_buff[], char* str, const uint8_t strSize);
void framePayload(uint16_t adc_buff[], uint8_t* payload, uint8_t maxpayloadSize);
void CVMS_Task(uint8_t*);
uint8_t CheckDIStatus(void);

//extern static uint16_t adc_result_buffer[ADC_SAMPLES];



#endif /* INCFILE1_H_ */