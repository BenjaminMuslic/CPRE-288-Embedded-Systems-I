/// Simple 'Hello, world' program
/**
 * This program prints "Hello, world" to the LCD screen
 * @author Chad Nelson
 * @date 06/26/2012
 *
 * updated: phjones 9/3/2019
 * Description: Added timer_init call, and including Timer.h
 */

#include "Timer.h"
#include "lcd.h"


int main (void) {

	timer_init(); // Initialize Timer, needed before any LCD screen functions can be called 
	              // and enables time functions (e.g. timer_waitMillis)

	lcd_init();   // Initialize the LCD screen.  This also clears the screen. 



	lcd_rotatingBanner("                    Microcontrollers are fun!                    ");

	// Print "Hello, world" on the LCD
	//lcd_printf("Hello, world");



//	lcd_puts("Hello, world"); // Replace lcd_printf with lcd_puts
        // step through in debug mode and explain to TA how it works
    
	// NOTE: It is recommended that you use only lcd_init(), lcd_printf(), lcd_putc, and lcd_puts from lcd.h.
       // NOTE: For time functions, see Timer.h

	return 0;
}
void lcd_rotatingBanner(char sentence[]) {


    while(true) { //while the function is true

    char subString[20];  //allocate memory for 20 empty characters
    int start;           //allocate variable for start

    for (start = 0; start <= 45; start++){   //there are 65 characters in the whole string of sentence[] 65 - 20 = 45. Iterate through that

        int i; //allocate a variable for i

        for (i = 0; i < 20; i++){                                   //iterate through the empty empty sub string
              subString[i] = sentence[start + i];                   //set the index of each iteration of the empty substring to the index of the sentence[start plus the i]
          }
            lcd_printf(subString);                                  //print the substring
            timer_waitMillis(300);                                  //wait 300 miliseconds


    }

    //lcd_printf("I JUST WAITED");
    }
}
