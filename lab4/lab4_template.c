/**
 * lab4_template.c
 *
 * Template file for CprE 288 lab 4
 *
 * @author Zhao Zhang, Chad Nelson, Zachary Glanz
 * @date 08/14/2016
 */

#include "button.h"
#include "Timer.h"
#include "lcd.h"
#include "cyBot_uart.h"  // Functions for communicating between CyBot and Putty (via UART)
                         // PuTTy: Baud=115200, 8 data bits, No Flow Control, No Parity, COM1

#warning "Possible unimplemented functions"
#define REPLACEME 0



int main(void) {
	button_init();
	timer_init(); // Must be called before lcd_init(), which uses timer functions
	lcd_init();
	            // Don't forget to initialize the cyBot UART before trying to use it
	int x;
    cyBot_uart_init();
   // oi_t *sensor_data = oi_alloc(); // do this only once at start of main()

	// YOUR CODE HERE

	
	while(1)
	{
	    x = button_getButton();

	    if (x == 4){

	        lcd_printf("1");
	        cyBot_sendByte('4');

	    }
	    else if (x == 3){

	                lcd_printf("2");
	        cyBot_sendByte('3');

	            }
	    else if (x == 2){

	                        lcd_printf("3");
	        cyBot_sendByte('2');

	          }
	    else if (x == 1){

	                        lcd_printf("4");
	        cyBot_sendByte('1');

	                    }
  //    lcd_printf(x);




	}

}
