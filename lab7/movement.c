/*
 * movement.c
 *
 *  Created on: Jan 31, 2023
 *      Author: Joon Park Osaid Samman
 */


#include "movement.h"
#include "open_interface.h"
#include "Timer.h"

double move_forward (oi_t *sensor_data, double distance_mm) {


    double sum = 0; // distance member in oi_t struct is type double

    oi_setWheels(100,100); //move forward at full speed

        while (sum < distance_mm) {
           oi_update(sensor_data);
           sum += sensor_data -> distance; // use -> notation since pointer
        }
    oi_setWheels(0,0); //stop

    return sum;
}

double turn_left(oi_t *sensor_data, double degrees) {            // counter clockwise

    double deg = sensor_data -> angle;
    oi_setWheels(-100,100); // right moving way faster than the left. Turning to the left
    while(deg > degrees) {
        oi_update(sensor_data);
        deg += sensor_data -> angle; // use -> notation since pointer
    }
    oi_setWheels(0,0); //stop

    return deg;
}

double turn_right(oi_t *sensor_data, double degrees) {            // counter clockwise

    double deg = sensor_data -> angle;
    oi_setWheels(100,-100); // right moving way faster than the right. Turning to the left
    while(deg < degrees) {
        oi_update(sensor_data);
        deg += sensor_data -> angle; // use -> notation since pointer
    }
    oi_setWheels(0,0); //stop

    return deg;
}

double collision_detection_move_forward(oi_t *sensor_data, double distance_mm) {


    double sum = 0; // distance member in oi_tstruct is type double

       int  backward;
       int bL;
       int bR;
           while (sum < distance_mm) {

               oi_setWheels(100,100); //move forward at speed 100

               bL = sensor_data -> bumpLeft;
               bR = sensor_data -> bumpRight;

              if(bL != 0 || bR != 0) {    // obstacle on both left and right
                   oi_setWheels(0,0); //stop
                   int def_distance = backward -150;
                   oi_setWheels(-100,-100); //move backward at speed 100
                   while(backward > def_distance) {
                         oi_update(sensor_data);
                         backward += sensor_data -> distance;  // if distance is negative, then change it to backward > -150
                   }
                   oi_setWheels(0,0); //stop
                   turn_left(sensor_data, -85); // move right -> 90 degrees
                   move_forward(sensor_data, 250); // move 25cm forward
                   turn_right(sensor_data, 85);  // move left ->  -90 degrees
                   sum = sum -150;
               }
               else {
                           sum += sensor_data -> distance; // use -> notation since pointer
               }
              oi_update(sensor_data);

          }



       return sum;
    // 2 BUMP SENSORS
    // 50CM -> 15CM BACK UP -> GO DOWN 25CM -> GO THE REST OF IT UNTIL IT IS STOPPED BY AN OBSTACLE.
}



