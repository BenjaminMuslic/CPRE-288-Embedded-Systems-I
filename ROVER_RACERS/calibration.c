/*
 * @file calibration.c
 * @author Benjamin Muslic, Manjul Balayar, Kalem Shrock, Dino & Adin Huric
 */

#include <functions.h>

#include "open_interface.h"
#include "Timer.h"
#include "lcd.h"
#include "servo.h"
#include "button.h"

/**
 * Use to calibrate servo.
 *
 */
void calibrate(void) {
   button_init();
   timer_init();
   lcd_init();
   servo_init();
   servo_calibrate();
}
