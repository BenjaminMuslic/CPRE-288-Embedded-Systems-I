/*
 * @file adc.c
 * @author Benjamin Muslic, Manjul Balayar, Kalem Shrock, Dino & Adin Huric
 */

#include <inc/tm4c123gh6pm.h>
#include <stdint.h>
#include <string.h>
#include "uart.h"
#include "adc.h"
#include <math.h>

void adc_init(void) {
    // Enable ADC clock bit 0 in this register for ADC0
    SYSCTL_RCGCADC_R |= 0x01;

    // Enable port B clock for the pin that we will use for ADC input
    SYSCTL_RCGCGPIO_R |= 0x02;

    // Wait for these two clocks to stabilize, use PRGPIO and PRADC
    while ((SYSCTL_PRGPIO_R & 0x02) == 0) {};

    // To make pin an input, write a zero to the DIR register
    GPIO_PORTB_DIR_R &= ~0x10; // make PB4

    // Enable the alternative function on that pin by writing one to the AFSEL register
    GPIO_PORTB_AFSEL_R |= 0x10; // enable alternate function on PB4

    // Disable the digital function on that pin by writing zero to the DEN register
    GPIO_PORTB_DEN_R &= ~0x10; // disable digital I/O on PB4

    // Enable the analog function on that pin by writing one to the AMSEL register
    GPIO_PORTB_AMSEL_R |= 0x10; // enable analog functionality on PB4

    while ((SYSCTL_PRADC_R & 0x0001) == 0) {};

    // Before configuring the sequencer, disable it. To disable sequencer 3, write a 0 to bit 3 (AFSEN3) in the ADC0_ACTSS_R
    ADC0_ACTSS_R &= ~0x0008;

    // Configure trigger event for sample sequencer in the ADC0_EMUX_R register. Write a 0000 to bits 15-12 (EM3) specifying software start mode for sequencer 3
    ADC0_EMUX_R &= ~0xF000;

    // Configure corresponding input source in the ADC0_SSMUX3 register. Write channel number to bits 3-0 in the ADC0_SSMUX3_R register
    ADC0_SSMUX3_R &= ~0x000F;

    // We sample channel 10, which is PB4
    ADC0_SSMUX3_R += 10;

    // Configure sample bits in the ADC0_SSCTL3 register. Sequencer 3 has only one sample, so write 0110 to the ADC0_SSCTL3_R register
    // Clear TS0 (bit 3) because we aren't measuring temperature
    // Set IEO (bit 2) because we want RIS bit to be set when sample is complete
    // Set END0 (bit 1) because this is the last and only sample in the sequence
    // Clear D0 (bit 0) because we don't want differential mode
    ADC0_SSCTL3_R = 0x0006;

    // Enable sample sequencer logic by writing 1 to bit 3 (ASEN3) in the ADC0_ACTSS_R register
    ADC0_ACTSS_R |= 0x0008;
}

// use AIN10 on PB4
// use ADC module 0, ADC0 - has 12 analog input channels (AIN), converts voltage and stores 12-bit digital value in this ADC register
// use Sequencer 3, SS3 - has its own set of registers to initialize and control a conversion
//      Sequencer 3 has 1 sample, 1 depth of FIFO
uint16_t adc_read(void) {
	
	uint16_t result;
	
	// Four steps to perform a software start conversion
	
	// Step 1: the ADC is started using the software trigger
	ADC0_PSSI_R = 0x0008; // PSSI: processor sample sequence initiate register, bit 3 begins sequence for SS3
	
	// Step 2: the function waits for the ADC to complete by polling the RIS register bit 3
	while ((ADC0_RIS_R & 0x08) == 0) {};
	
	// Step 3: the 12-bit digital sample is read out of sequencer 3
	result = ADC0_SSFIFO3_R & 0xFFF; // SSFIFO3: sample sequence result, store conversion results of samples
	
	// Step 4:
	ADC0_ISC_R = 0x0008;

	// return sample
	return result;
}

/**
 *
 * Calculate distance from ADC using IR sensor.
 *
 */
double ir_getDistance(void) {
    int adc_val = 0; // Raw ADC digital value scanned in by bot.
    int adc_sum = 0;
    int adc_sample = 0;

    double estimated_dist_val = 0;
    double estimated_dist_sum = 0;
    double estimated_dist = 0;

    int i = 0;
    int avg_count = 0;

    for (i = 0; i < 16; i++) {
        adc_val = adc_read(); // Get raw ADC value.
        // FIXME: Equation may be specific to bot.
        estimated_dist_val = 3570082.11707347 / pow((double)adc_val, 1.60513643); // Estimate distance in cm given raw ADC value.

        adc_sum += adc_val;
        estimated_dist_sum += estimated_dist_val;

        avg_count++;
    }

    adc_sample = adc_sum / avg_count; // Average ADC values.
    estimated_dist = estimated_dist_sum / avg_count; // Average distance values.

    timer_waitMillis(200); // Wait.

    // Reset variables.
    adc_sample = 0;
    adc_sum = 0;
    estimated_dist_sum = 0;
    avg_count = 0;

    return estimated_dist;
}

/**
 *
 * Scan using IR sensor without cyBOT_scan library.
 *
 */
double ir_scan(int angle) {
    servo_move(angle);
    timer_waitMillis(5);
    double distance;

    distance = ir_getDistance();

    return distance;
}
