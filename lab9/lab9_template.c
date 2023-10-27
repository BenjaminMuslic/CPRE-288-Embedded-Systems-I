/**
 * @file lab9_template.c
 * @author
 * Template file for CprE 288 Lab 9
 */

#include "Timer.h"
#include "lcd.h"
#include "ping_template.h"

// Uncomment or add any include directives that are needed

#warning "Possible unimplemented functions"
#define REPLACEME 0

//volatile unsigned int overflowCount = 0;

int main(void) {
    timer_init(); // Must be called before lcd_init(), which uses timer functions
    lcd_init();
    ping_init();

   int distance;
   int overFlow;
   int pulseWidth;


  while(1)
  {

      ping_trigger();
      distance= ping_read();
      pulseWidth = get_pulseWidth();
      overFlow = overflowCalc();
//        lcd_printf("Dist: %d", dist);
//        lcd_printf("%d", pw);
//        lcd_printf("%d", of);

      lcd_printf("Dist: %d \n PW: %d Overflow: %d",distance,pulseWidth,overFlow);
      timer_waitMillis(200);
  }
//
//    unsigned int dist;
//            int overflow_count = 0;
//
//            while (1) {
//                dist = ping_read();
//
//                lcd_printf("Dist: %d", dist);
//
//                int pulse_width = get_pulseWidth();
//                int pulse_width_millis = get_pulseWidth_millis();
//                lcd_printf("PW: %d, PWM: %d\n", pulse_width, pulse_width_millis);
//
//                overflow_count = overflowCalc();
//                lcd_printf("OF: %d\n", overflow_count);
//
//                timer_waitMillis(200);
//
//    }
}



