/*
 * servo.c
 *
 *  Created on: Apr 11, 2023
 *
 */
#include "servo.h"
#include "Timer.h"

//  20ms = 20 x 1000000 ns. (20000000/62.5)ns = 320000 in hex
volatile unsigned long conversion = 0x4E200;
volatile unsigned long DegreeToServoVal =0;


void servo_init(void) {

    // intialization of pwm
//    SYSCTL_RCGCPWM_R |= 0x01; // enable pwm module

    // intialization of port b
    SYSCTL_RCGCGPIO_R |= 0x00000002; // enable port b gpio

    while(! SYSCTL_RCGCGPIO_R & 0x00000002) {}

    GPIO_PORTB_AFSEL_R |= 0x20;
    GPIO_PORTB_DEN_R |= 0x20;
    GPIO_PORTB_DIR_R |= 0x20;
    GPIO_PORTB_PCTL_R |= 0x00700000;

    // Timer init
//    timer_init();
        timer_init2();

        TIMER1_TBMR_R |= 0x0A;
        TIMER1_TBMR_R &= ~0x01;

        TIMER1_TBPR_R = conversion >> 16;
        TIMER1_TBILR_R = conversion & 0xFFFF;
        TIMER1_CTL_R |= 0x100;
}

void servo_move(uint16_t degrees) {

//       GPIO_PORTB_DATA_R |= 0x20;

       DegreeToServoVal = 320000 - ((320000 - 278000)/180) * degrees;

       TIMER1_TBPMR_R = DegreeToServoVal >> 16; // upper 8 bits on prescaler
       TIMER1_TBMATCHR_R = DegreeToServoVal & 0xFFFF; // lower 16 bits on timer

       // Stay high until current counter equals match value
//       GPIO_PORTB_DATA_R &= ~0x20; // Set PWM signal low

}
