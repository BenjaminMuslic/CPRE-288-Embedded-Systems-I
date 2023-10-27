

/**
 * main.c
 */

#include "Timer.h"
#include "lcd.h"
#include "ping_template.h"
#include "servo.h"

int main(void)
{

    //----------------------calibration-------------------------------------------//


    //    timer_init();
    //    lcd_init();
    //    cyBOT_init_Scan(0b0111);
    //    cyBOT_SERVO_cal();
    //
    //    return 0;
    //}
    //-------------------------------------------------------------------------------//

    servo_init();
    lcd_init();
    ping_init();
    servo_move(45);
}


//servo init && servo move
