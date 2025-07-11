/*
 * CFile1.c
 *
 * Created: 04-06-2023 00:15:39
 *  Author: Amol Jadhav
 */ 
//#include "CVMS_ADC.h"
#include "CVMS_ADC.h"
#include "port.h"
#include "CVMS_Defines.h"
#include "ASF\sam0\drivers\adc\adc.h"
#include "ASF\sam0\drivers\adc\adc_callback.h"

/***** ADC Config *********/
struct adc_module adc_instance;
struct adc_config config_adc;

static uint16_t adc_result_buffer[ADC_SAMPLES];

volatile bool adc_read_done = false;


extern uint8_t CVMS_MACid[16];
uint8_t RFDD_ID[] = "0005";

uint8_t CheckDIStatus(void)
{
	uint8_t DigitalInputs = 0x00;
	if(port_pin_get_input_level(DI1_PIN))
	{
		DigitalInputs &= 0xff;
		DigitalInputs |= 0x01;
	}
	else
	DigitalInputs &= 0xfe;
	
	if(port_pin_get_input_level(DI2_PIN))
	{
		DigitalInputs &= 0xff;
		DigitalInputs |= 0x02;
	}
	else
	DigitalInputs &= 0xfd;
	
	if(port_pin_get_input_level(DI3_PIN))
	{
		DigitalInputs &= 0xff;
		DigitalInputs |= 0x04;
	}
	else
	DigitalInputs &= 0xfb;
	
	if(port_pin_get_input_level(DI4_PIN))
	{
		DigitalInputs &= 0xff;
		DigitalInputs |= 0x08;
	}
	else
	DigitalInputs &= 0xf7;
	
	return DigitalInputs;
}

// Callback function when 128 samples are completed.
void adc_complete_callback(struct adc_module *const module)
{
	adc_read_done = true;
}


//Configure the ADC
void configure_adc(void)
{

	struct system_voltage_references_config vtg_ref;
	
	adc_get_config_defaults(&config_adc);
	config_adc.reference       = ADC_REFERENCE_INTREF;
	config_adc.clock_prescaler = ADC_CLOCK_PRESCALER_DIV32;
	config_adc.resolution      = ADC_RESOLUTION_12BIT;
	config_adc.accumulate_samples = ADC_ACCUMULATE_SAMPLES_16;
	config_adc.divide_result      = ADC_ACCUMULATE_SAMPLES_16;

/*	#if (SAMC21)
	config_adc.positive_input  = ADC_POSITIVE_INPUT_PIN5;
	#else
	config_adc.positive_input  = ADC_POSITIVE_INPUT_PIN6;
	#endif 
*/
	config_adc.sample_length	= 50; 
	
//	config_adc.accumulate_samples = ADC_ACCUMULATE_SAMPLES_4;


	// Vref Configuration for Internal Voltage 2.5v
	vtg_ref.sel = SYSTEM_VOLTAGE_REFERENCE_2V5;
	vtg_ref.on_demand = 1;		// Should be 1 to run the Vref only when requested.
	vtg_ref.run_in_standby = 0;  // Should be 1 to keep Vref on sleepmode
	system_voltage_reference_set_config(&vtg_ref);

//	config_adc.positive_input_sequence_mask_enable =/* ADC_POSITIVE_INPUT_PIN6 | ADC_POSITIVE_INPUT_PIN7 |*/ ADC_POSITIVE_INPUT_PIN10 | ADC_POSITIVE_INPUT_PIN11 | ADC_POSITIVE_INPUT_PIN16;
//	adc_enable_positive_input_sequence(&adc_instance, config_adc.positive_input_sequence_mask_enable);

}


//Configure the AIN
void configure_AIN1(void)
{
	config_adc.positive_input  = ADC_POSITIVE_INPUT_PIN6;
	adc_init(&adc_instance, ADC, &config_adc);
	adc_enable(&adc_instance);
}
void configure_AIN2(void)
{
	config_adc.positive_input  = ADC_POSITIVE_INPUT_PIN4;
	adc_init(&adc_instance, ADC, &config_adc); 
	adc_enable(&adc_instance);
}
void configure_AIN3(void)
{
	config_adc.positive_input  = ADC_POSITIVE_INPUT_PIN5;
	adc_init(&adc_instance, ADC, &config_adc);
	adc_enable(&adc_instance);
}
void configure_AIN4(void)
{
	config_adc.positive_input  = ADC_POSITIVE_INPUT_PIN16;
	adc_init(&adc_instance, ADC, &config_adc);
	adc_enable(&adc_instance);
}
/*void configure_AIN5(void)
{
	config_adc.positive_input  = ADC_POSITIVE_INPUT_PIN11;
	adc_init(&adc_instance, ADC, &config_adc);
	adc_enable(&adc_instance);
}*/

	
// Register a call back for ADC
void configure_adc_callbacks(void)
{
	adc_register_callback(&adc_instance, adc_complete_callback, ADC_CALLBACK_READ_BUFFER);
	adc_enable_callback(&adc_instance, ADC_CALLBACK_READ_BUFFER);
}

// Register IRQ for ADC
void configure_adc_IRQ(void)
{
	    adc_enable_interrupt(&adc_instance, ADC_INTERRUPT_RESULT_READY);
//	    adc_configure_trigger(ADC, ADC_TRIG_SW, 0);
}


void adcReadPrint(void)
{
			
	configure_AIN1();
	configure_adc_callbacks();
	adc_read_buffer_job(&adc_instance, &adc_result_buffer[1], 1);
	while (adc_read_done == false)
	{
	}
	adc_read_done = false;
	adc_disable(&adc_instance);

	configure_AIN2();
	configure_adc_callbacks();
	adc_read_buffer_job(&adc_instance, &adc_result_buffer[2], 1);
	while (adc_read_done == false)
	{
	}
	adc_read_done = false;
	adc_disable(&adc_instance);
			
	configure_AIN3();
	configure_adc_callbacks();
	adc_read_buffer_job(&adc_instance, &adc_result_buffer[3], 1);
	while (adc_read_done == false)
	{
	}
	adc_read_done = false;
	adc_disable(&adc_instance);
	
	configure_AIN4();
	configure_adc_callbacks();
	adc_read_buffer_job(&adc_instance, &adc_result_buffer[4], 1);
	while (adc_read_done == false)
	{
	}
	adc_read_done = false;
	adc_disable(&adc_instance);
	
	adc_result_buffer[0] = CheckDIStatus();

	/*configure_AIN5();
	configure_adc_callbacks();
	adc_read_buffer_job(&adc_instance, &adc_result_buffer[0], 1);
	while (adc_read_done == false)
	{
	}
	adc_read_done = false;
	adc_disable(&adc_instance);*/

    #if defined (ENABLE_CONSOLE)
    printf("AIN1:%d, AIN2:%d, AIN3:%d, AIN4:%d, DI:%d",adc_result_buffer[0],adc_result_buffer[1],adc_result_buffer[2],adc_result_buffer[3], adc_result_buffer[4]);
    #endif
	
}

void convertToString(const uint16_t adc_buff[], char* str, const uint8_t strSize)
{
	// Calculate the number of characters needed for the string
	size_t strLength = ADC_SAMPLES * 5; // Assuming each value requires 5 characters (including comma and space)

	// Check if the string size is sufficient
	if (strSize < strLength)
	{
		// Handle insufficient string size error
		return;
	}

	// Convert each uint16_t value to a string
	for (size_t i = 0; i < ADC_SAMPLES; i++)
	{
		// Use sprintf to convert each value to a string and append to the main string
		sprintf(&str[i * 5], "%02x, ", adc_buff[i]); // Assuming each value is a decimal unsigned integer
	}

	// Replace the last space with a null terminator
	str[strLength - 1] = '\0';
}
	
void framePayload(uint16_t adc_buff[], uint8_t* payload, uint8_t maxpayloadSize)
{
	// Calculate the number of bytes needed for the payload
	size_t payloadBytes = ADC_SAMPLES * sizeof(uint16_t);

	// Check if the payload size is sufficient
	if (maxpayloadSize < payloadBytes)
	{
		// Handle insufficient payload size error
		return;
	}

	payload[0] = CVMS_MACid[0];
	payload[1] = CVMS_MACid[1];
	payload[2] = CVMS_MACid[2];
	payload[3] = CVMS_MACid[3];
	payload[4] = 0x2c;
	payload[5] = 0x20;
	
	convertToString(adc_buff, &payload[6], 26);
/*
	// Convert each uint16_t value to two uint8_t bytes
	for (size_t i = 0; i < ADC_SAMPLES; i++)
	{
		// Extract the least significant byte (LSB)
		payload[i * 3] = adc_buff[i] & 0xFF;

		// Extract the most significant byte (MSB)
		payload[i * 3 + 1] = (adc_buff[i] >> 8) & 0xFF;
		
		payload[i * 3 + 2] = 0x20;
	}
	*/
}
void CVMS_Task(uint8_t* data)
{
	//analogCircuit(true);
	analogDelay(100);
	adcReadPrint();
	//analogCircuit(false);
	framePayload(adc_result_buffer, data, 36);
}