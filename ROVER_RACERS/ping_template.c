/*
 * @file ping_template.c
 * @author Benjamin Muslic, Manjul Balayar, Kalem Shrock, Dino & Adin Huric
 */

#include "ping_template.h"
#include "Timer.h"
#include "servo.h"

volatile unsigned long START_TIME = 0;
volatile unsigned long END_TIME = 0;
volatile unsigned long CURRENT_TIME = 0;
volatile enum{LOW, HIGH, DONE} STATE = LOW; // State of ping echo pulse

// Initialize the timer
void ping_init (void){

    // Step 1: Port B Initialization
    // Enable Port B
    SYSCTL_RCGCGPIO_R |= 0x2;
    SYSCTL_RCGCTIMER_R |= 0x8;
    while ((SYSCTL_RCGCTIMER_R & 0x8) == 0) {};
    while ((SYSCTL_RCGCGPIO_R & 0x2) == 0) {};

    // Enable alternate function
    GPIO_PORTB_AFSEL_R |= 0x8; // bit 3 = 1
    // Set PB3 to alternate function
    GPIO_PORTB_PCTL_R |= 0x7000;
    // Clear out 4th bit
    GPIO_PORTB_PCTL_R &= ~0x8000;

    // Step 2: Configure and Enable Timer
    // Enable clock to Timer 3 and check that it's ready
    SYSCTL_RCGCTIMER_R |= 0x8;
    while ((SYSCTL_RCGCTIMER_R & 0x8) == 0) {};
    
    // Disable timer before messing with stuff
    TIMER3_CTL_R &= ~0x100;

    // Enable is bit 8 = 1
    // Rising and falling edge capture is bit 11:10 = 11
    TIMER3_CTL_R |= 0xC00;

    // Set to 16 bit mode
    TIMER3_CFG_R |= 0x04;

    // Capture mode is bit 1:0 = 11
    // Edge-time mode is bit 2 = 1
    // Enable capture mode is bit 3 = 0
    // Count direction is bit 4 = 0
    // = 00111
    TIMER3_TBMR_R |= 0x07;
    TIMER3_TBMR_R &= ~0b10000;

    // Use prescaler
    TIMER3_TBPR_R |= 0xFF;

    // Loads counter for Timer B
    TIMER3_TBILR_R |= 0xFFFF;



    // Step 3: Configure Interrupts for Handler

    // First clear interrupt flag (clear by writing 1 to ICR)
    TIMER3_ICR_R |= 0x400; // bit 10 = 1
    // Enable TB capture interrupt
    TIMER3_IMR_R |= 0x400; // bit 10 = 1
    // Set priority of Timer3 interrupt to 1 in bits 7-5, set bits 7:5 to 0b001 = 0X11100000
    NVIC_PRI9_R |= 0xE0;
    // Enable interrupt for Timer 3B, set bit 4 = 1
    NVIC_EN1_R |= 0x10;
    //tell CPU to use ISR handler for TIMER3
    IntRegister(INT_TIMER3B, TIMER3B_Handler);

    // Re-enable Timer 3B after setting it up?
    TIMER3_CTL_R |= 0x100;

    //globally allow CPU to service interrupts (see interrupt.h file)
    IntMasterEnable();
}


///////////////// Part 1: Activate Sensor ///////////////////
void ping_trigger (void) {
    // 1) Initialize PB3 as digital output (disable alternate function) with GPIOAFSEL
    // 2) Make pin low-high-low by writing 0-1-0 to GPIODATA register bit
    // 3) Implement duration of trigger pulse

    // Disable timer and disable timer interrupt
    TIMER3_CTL_R &= 0b1111111011111111; // bit 8 = 0
    TIMER3_IMR_R &= ~0x400; // bit 10 = 0

    // Enable Port B
    SYSCTL_RCGCGPIO_R |= 0x2;
    // Disable alternate function (disconnect timer from port pin)
    GPIO_PORTB_AFSEL_R &= ~0x8; // bit 3 = 0
    // Enable direction in Port B
    GPIO_PORTB_DEN_R |= 0x8;
    // Enable as output in Port B
    GPIO_PORTB_DIR_R |= 0x8;

    // Write 0-1-0 to GPIODATA register bit
     GPIO_PORTB_DATA_R &= ~0x8; // bit 3 = 0
     STATE = LOW;
     GPIO_PORTB_DATA_R |= 0x8; // bit 3 = 1
     STATE = HIGH;
     timer_waitMicros(5); // delay five microseconds
     GPIO_PORTB_DATA_R &= ~0x8; // bit 3 = 0
     STATE = LOW;

    // Clear an interrupt that may have been erroneously triggered
    TIMER3_ICR_R |= 0xF00; // write 1 to bit 11, 10, 9, 8

    // Re-enable alternate function, timer interrupt, and timer
    GPIO_PORTB_AFSEL_R |= 0x8; // bit 3 = 1
    TIMER3_IMR_R |= 0x400; // bit 10 = 1
    TIMER3_CTL_R |= 0x100; // bit 8 = 1
}


// Implement the interrupt handler
void TIMER3B_Handler(void){

    // YOUR CODE HERE
    // As needed, go back to review your interrupt handler code for the UART lab.
    // What are the first lines of code in the ISR? Regardless of the device, interrupt handling
    // includes checking the source of the interrupt and clearing the interrupt status bit.
    // Checking the source: test the MIS bit in the MIS register (is the ISR executing
    // because the input capture event happened and interrupts were enabled for that event?
    // Clearing the interrupt: set the ICR bit (so that same event doesn't trigger another interrupt)
    // The rest of the code in the ISR depends on actions needed when the event happens.

      //check if handler called
      if (TIMER3_MIS_R & 0x400); // if bit 10 = 1
      {
          //clear the interrupt status bit (clear by writing 1 to ICR)
          TIMER3_ICR_R |= 0x400; // clear bit 10 = 1

          if (STATE == LOW) { // record rising time if state is low
              START_TIME = TIMER3_TBR_R;
              STATE = HIGH;
          } else if (STATE == HIGH) { // record falling time if state is high
              END_TIME = TIMER3_TBR_R;
              STATE = DONE;
          }
      }
}

/**
 *
 * Calculate distance from time observed using PING sensor.
 *
 */
unsigned long ping_getDistance (void){
    CURRENT_TIME = get_pulseWidth();
    return ((CURRENT_TIME/16000000.0) * (34300.0)) / 2.0;
}

int get_pulseWidth(void) {
	return START_TIME - END_TIME;
}

double get_pulseWidth_millis(void) {
    return (CURRENT_TIME / 16000000.0) * 1000;
}

/**
 *
 * Scan using PING sensor without cyBOT_scan library.
 *
 */
double ping_scan(int angle) {
    servo_move(angle);
    timer_waitMillis(80);
    int i = 0;
    int sum = 0;
    double distance;

    for (i = 0; i < 2; i++) {
        ping_trigger();
        sum += ping_getDistance();
        timer_waitMillis(100);
    }

    distance = sum / 2.0;

    return distance;
}
