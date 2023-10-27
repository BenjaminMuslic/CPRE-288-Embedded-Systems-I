/*
 * lab6_main.c
 *
 *  Created on: Mar 3, 2023
 *      Author: no one
 */


#include "Timer.h"
#include "lcd.h"
#include "cyBot_Scan.h"  // For scan sensors
#include "uart.h"

// Uncomment or add any include directives that are needed
// #include "open_interface.h"
// #include "movement.h"
// #include "button.h"


#warning "Possible unimplemented functions"
#define REPLACEME 0


//int main(void) {
//    timer_init(); // Must be called before lcd_init(), which uses timer functions
//    lcd_init();
//    uart_interrupt_init();
//  // cyBOT_init_Scan();
//
//    // YOUR CODE HERE
//
//    while(1)
//    {
//
//        uart_sendStr("\rHello!\n\r");
//        uart_sendStr("PuTTy is sending messages.\n\r");
//        uart_sendStr("So yeah.\n\r\n");
//        char c;
//            char temp = '\n';
//            c = uart_receive();
//
//            if (c > '0') {
//                lcd_clear();
//                if (c != temp) {
//                    uart_sendChar(c);
//                    lcd_putc(c);
//                }
//                temp = c;
//            }
//
//    }
//
//}
