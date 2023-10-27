/**
 * @file ping_template.h
 * @author Benjamin Muslic, Manjul Balayar, Kalem Shrock, Dino & Adin Huric
 */
#ifndef PING_H_
#define PING_H_

#include <stdint.h>
#include <stdbool.h>
#include <inc/tm4c123gh6pm.h>
#include "driverlib/interrupt.h"

/**
 * Initialize ping sensor. Uses PB3 and Timer 3B
 */
void ping_init (void);

/**
 * @brief Trigger the ping sensor
 */
void ping_trigger (void);

/**
 * @brief Timer3B ping ISR
 */
void TIMER3B_Handler(void);

/**
 * @brief Calculate the distance in cm
 *
 * @return Distance in cm
 */
unsigned long ping_getDistance (void);

int get_pulseWidth(void);

double get_pulseWidth_millis(void);

double ping_scan(int angle);

#endif /* PING_H_ */