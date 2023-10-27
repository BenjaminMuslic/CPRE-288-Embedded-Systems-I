///// Simple 'Hello, world' program
///**
// * This program prints "Hello, world" to the LCD screen
// * @author Chad Nelson
// * @date 06/26/2012
// *
// * updated: phjones 9/3/2019
// * Description: Added timer_init call, and including Timer.h
// */
//
#include <string.h>
#include "Timer.h"
#include "lcd.h"
#include "movement.h"
#include "open_interface.h"
#include "cyBot_Scan.h"
#include "cyBot_uart.h"
//
//void lcd_rotatingBanner(float num);
//
int main(void)
{
//
    cyBot_uart_init();
    oi_t *sensor_data = oi_alloc(); // do this only once at start of main()

    oi_init(sensor_data); // do this only once at start of main()
    lcd_init();
    timer_init();
    cyBOT_init_Scan(0b0111);
    right_calibration_value = 232750;
    left_calibration_value = 1219750;

//    //-----------------------------------------------------------------------------------------------
//    //Calibrate
////    timer_init();
////    lcd_init();
////    cyBOT_init_Scan(0b0111);
////    cyBOT_SERVO_cal();
////
////    return 0;
//    //-----------------------------------------------------------------------------------------------
//
//    /*------------------------------------------------------------------------------------------------
//     * the following is remote control code
//     */
//    //------------------------------------------------------------------------------------------------
//    while (true)
//    {
//        // oi_setWheels(0,0); //move forward at 100 speed
//
//        char x;
//
//        x = cyBot_getByte();
//        cyBot_sendByte(x);
//        lcd_putc(x);
//        if (x == 'w')
//        {
//            oi_setWheels(500, 500);
//            timer_waitMillis(300);
////
////
//           //cyBot_sendByte('got a w!');
//           lcd_rotatingBanner("got a w!");
//           printf("got a w!\n");
//        }
//        else if (x == 'a')
//        {
//            oi_setWheels(500, 0);
//            timer_waitMillis(300);
//            printf("got an a!\n");
//        }
//        else if (x == 's')
//        {
//           oi_setWheels(-500, -500);
//            timer_waitMillis(300);
//            printf("got an s!\n");
//        }
//        else if (x == 'd')
//        {
//            oi_setWheels(0, 500);
//           timer_waitMillis(300);
//            printf("got an d!\n");
//        }
////------------------------------------------------------------------------------------------------
//
///*
// *  The following is the scanning procedure
// */
////------------------------------------------------------------------------------------------------
cyBOT_Scan_t newScan;

oi_setWheels(0,0);
int i;
while(true){
    char y;
    y = cyBot_getByte();
   printf(y + "\n");
    cyBot_sendByte(y);
    lcd_putc(y);

   char data[50];
    int data_index;

    char info[] ="Degrees\t Ping Distance (cm)\n";

    int len = strlen(info);
    int p;

    if (y=='m'){
        cyBot_sendByte('\r');
        cyBot_sendByte('\n');
    }
    for (p = 0; p < len; p++){
        cyBot_sendByte(info[p]);
    }
    cyBot_sendByte('\r');
    cyBot_sendByte('\n');

    char sentence [50];

    for (i = 70; i <= 110; i+=3){
        cyBOT_Scan(i, &newScan);
       sprintf(sentence, "%d\t\t%lf\r\n", i, newScan.sound_dist);
       makestr(sentence);
    }

    for (i = 110; i >= 70; i-=3){
           cyBOT_Scan(i, &newScan);
          sprintf(sentence, "%d\t\t%lf\r\n", i, newScan.sound_dist);
           makestr(sentence);
       }
}
oi_free(sensor_data);
}
////
////}
////
//////    int i;
//////    char y;
//////    y = cyBot_getByte();
//////
//////    while(true){
//////
//////
//////        cyBot_sendByte(y);
//////        lcd_putc(y);
//////
//////        if (y == 'm'){
//////
//////            for (i=0; i <= 20; i+=2) {
//////                cyBOT_Scan(i, &newScan);
//////                data_display(newScan.sound_dist);
//////                printf("%.2lf", newScan.sound_dist);
//////            }
//////
//////            for (i=20; i >= 0; i-=2) {
//////                 cyBOT_Scan(i, &newScan);
//////                 data_display(newScan.sound_dist);
//////                printf("%.2lf", newScan.sound+
//////       }
//////    }
//////    oi_free(sensor_data);  // do this once at end of main()
//////
//////}
////
void makestr(char str[]) {

       int len = strlen(str);
        int i = 0;

        for (i = 0; i < len; i++){
            cyBot_sendByte(str[i]);
        }



        cyBot_uart_init();
        oi_t *sensor_data = oi_alloc(); // do this only once at start of main()
        oi_init(sensor_data); // do this only once at start of main()
        lcd_init();
        timer_init();
        cyBOT_init_Scan(0b0111);
        right_calibration_value = 285250;
        left_calibration_value = 1272250;

        cyBOT_Scan_t newScan;
    //    cyBot_Scan sound_dist;
        oi_setWheels(0,0);
        int i;
        char scanning[] = "Degrees\t PING Distance (cm)\n";
        char objects[] = "Object number\t\t Object angle\t\t Distance to an object (cm)\t\t Radial width \r\n";
        while(true) {

            char y;
            y = cyBot_getByte();
    //        printf(y + "\n");
    //        cyBot_sendByte(y);
    //        lcd_putc(y);
    //        char data[50];
    //        int data_index;

            if(y == 'm') {

                grid_dispay(scanning);

                char sentence [50];

                for(i=70; i <=110; i+=3) {
                    cyBOT_Scan(i, &newScan);
                    sprintf(sentence, "%d\t\t%lf\r\n", i, newScan.sound_dist); //IR_raw_val
                    makestr(sentence);

                }

                for(i=110; i >= 70; i-=3) {
                    cyBOT_Scan(i, &newScan);
                    sprintf(sentence, "%d\t\t%lf\r\n", i, newScan.sound_dist);
                    makestr(sentence);

                }

            }

            if(y== 'n') {

                grid_dispay(objects);

                char sentence [50];
                float init_distance;
                float distance;
                int init_degree;
                bool start = true;
                int object_num =0;

                int degree_increment =0;

                for(i=0; i <=180; i+=1) {

                    cyBOT_Scan(i, &newScan);
                    distance = newScan.sound_dist;

                    if(distance > 60) {
                        // do nothing
                    }

                    else {

                    if(start) {
                        init_distance = distance;
                        start = false;
                    }

                    float range = distance - init_distance;


                     if (range > 3 || range < -3) {                 // out of range +-3

                         init_distance = distance;

                        if(degree_increment > 7) {
                            char sentence [10];
    //                       sprintf(sentence, "\r\n", "Object number: \r\n", "Angle detected: \r\n", "Distance: \r\n", "Radial width: \r\n"); //IR_raw_val
                            sprintf(sentence, "%d\r\n", object_num);
                            makestr(sentence);
                            object_num++;
                            degree_increment =0;
                        }
                     }
                     else {                                                                         // in range +-3

    //                     char sentence [100];
    //                     sprintf(sentence, "%d\r\n", degree_increment);
    //                     makestr(sentence);
                         degree_increment++;
                     }


                    }
                }
                cyBOT_Scan(0, &newScan);
        }
        oi_free(sensor_data);
        }
    }
}
    void makestr(char str []) {

        int len = strlen(str);
        int i;

        for(i =0; i < len; i++) {
            cyBot_sendByte(str[i]);
        }
    }

    void grid_dispay(char information []) {
                   cyBot_sendByte('\r');
                   cyBot_sen n dByte('\n');
                   int p;
                   int len = strlen(information);

                   for(p =0; p < len; p++) {
                       cyBot_sendByte(information[p]);
                   }
                   cyBot_sendByte('\r');
                   cyBot_sendByte('\n');
    }
//
//




