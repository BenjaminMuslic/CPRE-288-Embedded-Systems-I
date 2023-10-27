/*
 * movement.c
 *
 *  Created on: Jan 30, 2023
 *      Author: muslicb
 */
#include "movement.h"
#include "open_interface.h"
#include "Timer.h"

double move_forward (oi_t *sensor_data) {


    double distanceX = 0; // distance member in oi_t struct is type double
    oi_setWheels(100,100); //move forward at 100 speed

        while (distanceX <= 2000) {
           oi_update(sensor_data);
           distanceX += sensor_data -> distance; // use -> notation since pointer
        }
    oi_setWheels(0,0); //stop
    distanceX = 0;
}

double turn_right(oi_t *sensor_data) {            // counter clockwise
    double angleRight = 0;

    oi_setWheels(0,250); // right moving way faster than the left. Turning to the left

    while (angleRight >= -90) {
       oi_update(sensor_data);

       angleRight += sensor_data -> angle; // use -> notation since pointer
      }
           oi_setWheels(0,0); //stop
           angleRight = 0;
    }

double turn_left(oi_t *sensor_data) {            // counter clockwise
    double angleLeft = 0;

    oi_setWheels(100,0); // right moving way faster than the left. Turning to the left

    while (angleLeft <= 85) {
       oi_update(sensor_data);
   //    printf("%f \n",sensor_data -> angle);
       angleLeft += sensor_data -> angle; // use -> notation since pointer
      }
           oi_setWheels(0,0); //stop
           angleLeft = 0;
    }

double obstacle(oi_t *sensor_data){

    double distanceX = 0;

    oi_setWheels(100,100); //move forward at 100 speed

    while (distanceX <= 2000) {
             oi_update(sensor_data);
             distanceX += sensor_data -> distance; // use -> notation since pointer

    if (sensor_data -> bumpLeft == 1 || sensor_data -> bumpRight == 1 ){

           distanceX = 0;
           oi_setWheels(-100,-100); //move backward at 100 speed

           while(distanceX > -300) {
                       oi_update(sensor_data);
                       distanceX += sensor_data -> distance; // use -> notation since pointer
           }
           double angleRight = 85;

               oi_setWheels(-100,100); // right moving way faster than the left. Turning to the left

               while(angleRight >= 0) { //because angle starts from 85
                  oi_update(sensor_data);
              //    printf("%f \n",sensor_data -> angle);
                  angleRight += sensor_data -> angle; // use -> notation since pointer
                 }
               distanceX = 250;
               oi_setWheels(100,100);
               while(distanceX >= 0){
                   oi_update(sensor_data);
                   distanceX -= sensor_data -> distance; // use -> notation since pointer
                   }
               double angleLeft = -85;

               while(angleLeft <= 0) { //because angle starts from 85
                oi_update(sensor_data);
                oi_setWheels(100,-100);
              //   printf("%f \n",sensor_data -> angle);
               angleLeft += sensor_data -> angle; // use -> notation since pointer
              }
               distanceX = 1000;
               oi_setWheels(100,100);
               while(distanceX >= 0){
                  oi_update(sensor_data);
                  distanceX -= sensor_data -> distance; // use -> notation since pointer
                  }
               }


    }
}



//           timer_waitMillis(300);
//           double angleRight = 0;
//
//              oi_setWheels(0,250); // right moving way faster than the left. Turning to the left
//
//              while (angleRight >= -90) {
//                 oi_update(sensor_data);
//
//                 angleRight += sensor_data -> angle; // use -> notation since pointer
//                }
//                     oi_setWheels(0,0); //stop
//                     angleRight = 0;
//              }
//
//      oi_setWheels(0,0); //stop
//      distanceX = 0;
//    }
//}





