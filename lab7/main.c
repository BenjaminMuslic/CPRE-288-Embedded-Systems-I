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
//#include "Timer.h"
//#include "lcd.h"
//#include "movement.h"
//#include "open_interface.h"
//#include <stdio.h>
//#include <stdint.h>
//#include <string.h>
//#include <stdlib.h>
//#include <inc/tm4c123gh6pm.h>
//#include "cyBot_Scan.h"
//#include "cyBot_uart.h"
//
////----------------------calibration-------------------------------------------//
//
//
////    timer_init();
////    lcd_init();
////    cyBOT_init_Scan(0b0111);
////    cyBOT_SERVO_cal();
////
////    return 0;
////}
////-------------------------------------------------------------------------------//
//
//void makestr(char str []);
//void make_move(oi_t *sensor_data, int prev_obj_Angle, float dist_to_obj);
//
//int main (void) {
//
//    cyBot_uart_init();
//    oi_t *sensor_data = oi_alloc(); // do this only once at start of main()
//    oi_init(sensor_data); // do this only once at start of main()
//    lcd_init();
//    timer_init();
//    cyBOT_init_Scan(0b0111);
//    right_calibration_value = 285250;
//    left_calibration_value = 1240750;
//
//    cyBOT_Scan_t newScan;
////    cyBot_Scan sound_dist;
//    oi_setWheels(0,0);
//    int i;
//    char scanning[] = "Degrees\t PING Distance (cm)\n";
//    char objects[] = "Object number\t\t Object angle\t\t Distance to an object (cm)\t\t Radial width\t\t Object Width\r\n";
//
//   while(true) {
//
//        char y;
//        y = cyBot_getByte();
////        printf(y + "\n");
////        cyBot_sendByte(y);
////        lcd_putc(y);
////        char data[50];
////        int data_index;
//
//        if(y == 'm') {
//
//            grid_dispay(scanning);
//            float calculation;
//            char sentence [100];
//
//            for(i=60; i <=120; i+=3) {
//                cyBOT_Scan(i, &newScan);
//
////                sprintf(sentence, "%d\t\t%lf\r\n", i, (22.47/(newScan.IR_raw_val/1000.0) - 0.17)); //IR_raw_val
//
//                sprintf(sentence, "%d\t\t%lf\r\n", i, newScan.sound_dist); // sound_dist
//
//                makestr(sentence);
////                makestr(sentence);
//            }
//            turn_right(sensor_data, 80);
//            collision_detection_move_forward(sensor_data, 200);
//        }
//
//
//        if(y== 'n') {
//            oi_setWheels(0,0); //stop
//            grid_dispay(objects);
//
//            char sentence [50];
//            float init_distance;
//            float distance;
//            int init_degree;
//            bool start = true;
//            int object_num =0;
//            float obj_Angle;
//            float dist_to_obj;
//            float maxRange = 65.0;
//            int degree_increment =0;
//
//            float  prev_obj_Angle=0;
//            float prev_obj_inc=0;
//
//            for(i=0; i <=180; i+=2) {
//
//                cyBOT_Scan(i, &newScan);
//                distance = newScan.sound_dist;
////                distance = (22.47/(newScan.IR_raw_val/1000.0) - 0.17);
//
//            if(distance < maxRange) {
//
//                if(start) {
//                    init_distance = distance;
//                    start = false;
//                }
//
//                float range = distance - init_distance;
//
//                 if (range > 5 || range < -5) {                 // out of range +-3
//
//                     init_distance = distance;
//
//                    // in range of +-5cm for at least 7 times continuously to be called as an object.
//                    if(degree_increment > 10) {
//                        char sentence [10];
//                        object_num++;
//                        obj_Angle = (obj_Angle/degree_increment);
//                        dist_to_obj = (dist_to_obj/degree_increment);
//
//                        double object_width = obj_Angle/360 *2*3.1415926535 * dist_to_obj;
//
//                        sprintf(sentence, "%d\t\t\t%.2f\t\t\t%.2f\t\t\t\t\t%d\t\t\t\t%lf\r\n", object_num, obj_Angle, dist_to_obj, degree_increment, object_width);
//                        makestr(sentence);
//
//                        if (prev_obj_inc < degree_increment) {
//                            prev_obj_inc = degree_increment;
//                            prev_obj_Angle = obj_Angle;
//                        }
//
//                    }
//                    degree_increment =0;
//                    obj_Angle=0;
//                    dist_to_obj=0;
//                 }
//                 else if (range < 5 && range > -5) {                                                                         // in range +-3
//
//                     dist_to_obj += distance;
//                     obj_Angle += i;
//                     degree_increment +=2;
//
//                 }
//
//                }
//            }
//
//            if(prev_obj_Angle != 0) {
//                cyBOT_Scan(prev_obj_Angle, &newScan);
//                make_move(sensor_data,prev_obj_Angle, dist_to_obj);
//
//         }
//
//        if(y== 'p') {
//            make_move(sensor_data,prev_obj_Angle, dist_to_obj);
//        }
//    oi_free(sensor_data);
//    }
//}
//}
//
//// This function makes a move based on the input angle and distance while avoiding collisions.
//
//void make_move(oi_t *sensor_data, int angle, float dist) {
//
//    // If the angle is greater than 90 degrees, turn right.
//    if(angle > 90) {
//        turn_right(sensor_data, angle);
//    }
//    // Otherwise, turn left.
//    else {
//        turn_left(sensor_data, angle);
//    }
//
//    // Move forward by the specified distance while checking for any potential collisions.
//    collision_detection_move_forward(sensor_data, dist);
//}
//
//
//void makestr(char str []) {
//
//    int len = strlen(str);
//    int i;
//
//    for(i =0; i < len; i++) {
//        cyBot_sendByte(str[i]);
//    }
//}
//
//void grid_dispay(char information []) {
//               cyBot_sendByte('\r');
//               cyBot_sendByte('\n');
//               int p;
//               int len = strlen(information);
//
//               for(p =0; p < len; p++) {
//                   cyBot_sendByte(information[p]);
//               }
//               cyBot_sendByte('\r');
//               cyBot_sendByte('\n');
//}

