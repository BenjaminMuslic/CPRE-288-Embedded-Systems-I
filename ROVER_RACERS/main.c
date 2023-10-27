/**
 *@file main.c
 *@author Benjamin Muslic, Manjul Balayar, Kalem Shrock, Dino & Adin Huric
 */
#include <functions.h>
#include "lcd.h"
#include "Timer.h"
#include "open_interface.h"
#include "uart-interrupt.h"
#include "ping_template.h"
#include <time.h>
#include <stdbool.h>
#include "driverlib/interrupt.h"
#include "button.h"
#include "servo.h"
#include "adc.h"
#include "calibration.h"
#include <time.h>
#include "bno055.h"

//ROVER RACERS
const int car_honk_num_notes = 2;
unsigned char car_honk_notes[] = { 72, 76 };

unsigned char car_honk_duration[] = { 8, 8 };

void load_car_honk(void)
{
    oi_loadSong(2, car_honk_num_notes, car_honk_notes, car_honk_duration);
}


int main(void)
{
    //calibrate();

    // Initialize components.
    timer_init();   // Must be called before lcd_init(), which uses timer functions.
    lcd_init();
    uart_interrupt_init();
    ping_init();
    servo_init();
    adc_init();

    //  Allocate memory for the sensor data.
    oi_t *sensor_data = oi_alloc();

    oi_init(sensor_data);   // Do this only once at start of main().

    // Set robot's wheels to stop.
    oi_setWheels(0, 0);

    load_car_honk();

    // Loop indefinitely.
    while (1)
    {
        // w = forward
        if (command_flag == 2)
        {
            command_flag = move_forward(sensor_data);
        }

        // s = reverse
        if (command_flag == 3)
        {
            move_reverse(sensor_data);
            command_flag = 0;
        }

        // a = left
        if (command_flag == 4)
        {
            turn_left(sensor_data);
            command_flag = 0;
        }

        // d = right
        if (command_flag == 5)
        {
            turn_right(sensor_data);
            command_flag = 0;
        }

        // r = EMERGENCY BRAKE
        if (command_flag == 7)
        {
            emergency_brake(sensor_data);
            command_flag = 0;
        }

        // 1 = perform 180 scan with PING sensor and Timer.
        if (command_flag == 8)
        {
            command_flag = 0;
            ping(sensor_data);
        }

        // 2 = perform 180 scan with IR sensor and ADC.
        if (command_flag == 10)
        {
            command_flag = 0;
            ir(sensor_data);
        }

        // 3 = perform 180 scan with PING and IR.
        if (command_flag == 11)
        {
            command_flag = 0;
            double_scan();
        }

        // b = BOOOOOST (use at own risk)
        if (command_flag == 9)
        {
            oi_setLeds(0, 0, 255, 255);
            command_flag = boost(sensor_data);
            oi_setLeds(0, 0, 0, 0);
        }

        //p = honk
        if (command_flag == 12)
        {
            oi_play_song(2);
            command_flag = 0;
        }

        timer_waitMillis(50);
    }

    oi_free(sensor_data);
}

