
#ifndef PINGH
#define PINGH

#include <inc/tm4c123gh6pm.h>

void TIMER3B_HANDLER(void);

void ping_init();

void send_pulse();

unsigned int ping_read();

unsigned long calcDist();

int get_pulseWidth();

int overflowCalc();

int get_pulseWidth_millis();



#endif /* PINGH */
