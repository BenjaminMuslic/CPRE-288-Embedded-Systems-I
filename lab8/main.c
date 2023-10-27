

/**
 * main.c
 */

#include "lcd.h"
#include "Timer.h"
#include "movement.h"
#include "open_interface.h"
#include "cyBot_uart.h"
#include "cyBot_Scan.h"
#include "uart-interrupt.h"
#include <time.h>
#include "adc.h"

////////////////////////

// calibration //

//int main (void) {
//
//   timer_init();
//   lcd_init();
//   cyBOT_init_Scan(0b0111);
//   cyBOT_SERVO_cal();
//   return 0;
//}

////////////////////////


int main (void) {
	
	lcd_init(); // initialize lcd
	timer_init(); // initialize timer
	oi_t *sensor_data = oi_alloc(); // sensor data struct
	oi_init(sensor_data); // initialize sensor data struct
	uart_interrupt_init(); // initialize uart interrupt
	adc_init();
	cyBOT_init_Scan(0b0111); // initialize scan
	cyBOT_Scan_t getScan; // scan struct


	// calibration values
//	right_calibration_value = 238000;
//	left_calibration_value = 1214500;
	

	int adc_val = 0; // raw adc digital value scanned in by bot
	int adc_sum = 0;
	int adc_sample = 0;

	double estimated_dist_val = 0;
	double estimated_dist_sum = 0;
	double estimated_dist = 0;

	int i = 0;
	int avg_count = 0;
	char data[200];
	
	
	///////////////// Part 1: Initialize ADC ///////////////////

	// Take multiple samples and display raw digital adc values	
	
//	while (1) {
//
//		adc_val = adc_read(); // get ADC value
//
//		// print raw digital adc values
//		// sprintf(actual_data, "ADC values: %d\n\r", adc_val);
//		lcd_printf("ADC values: %d", adc_val);
//
//		timer_waitMillis(800); // add delay
//
//	}
	
	
	
//	///////////////// Part 2a: Samples ///////////////////
//
//	// Collect and average 16-20 samples at different distances
//	// Distance will be between 9 - 50 cm away
//
	while (1) {

		for(i = 0; i < 16; i++){
			adc_val = adc_read(); // get ADC value
			estimated_dist_val = 1464820.29939687 / pow((double)adc_val, 1.5128593);

			adc_sum += adc_val;
			estimated_dist_sum += estimated_dist_val;

			avg_count++;
		}

		adc_sample = adc_sum / avg_count; // get averaged adc value
		estimated_dist = estimated_dist_sum / avg_count; // get averaged dist value

		// print distance and adc values
        sprintf(data, "Averaged raw ADC value: %d\t\t Averaged estimated distance: %0.2f\n\r", adc_sample, estimated_dist);

        uart_sendStr(data);

        timer_waitMillis(1000); // add delay

        // reset values
        adc_sample = 0;
        adc_sum = 0;
        estimated_dist = 0;
        estimated_dist_sum = 0;
        avg_count = 0;

	}

	// Once all samples are taken, graph in excel and find best fit/line equation


//
//
//
//
//
//	///////////////// Part 2b: Calculating Distance ///////////////////
//
//	// Given the raw digital values from the ADC, pass them through your
//	// best fit equation and get an estimated distance value in cm
//
//
//	/////////////////////////////////////////////////////////////////

	oi_free(sensor_data);
	
	return 0;
}
