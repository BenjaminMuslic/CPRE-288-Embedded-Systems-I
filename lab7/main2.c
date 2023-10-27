
//Lab
#include "Timer.h"
#include "lcd.h"
#include "movement.h"
#include "open_interface.h"
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <inc/tm4c123gh6pm.h>
#include "cyBot_Scan.h"
#include "cyBot_uart.h"

//----------------------calibration----------------------------------------------//


//    timer_init();
//    lcd_init();
//    cyBOT_init_Scan(0b0111);
//    cyBOT_SERVO_cal();
//
//    return 0;
//}
//-------------------------------------------------------------------------------//

void makestr(char str []);
void make_move(oi_t *sensor_data, int prev_obj_Angle, float dist_to_obj);

// This function initializes various components and sets some calibration values.
int main (void) {

    // Initialize UART communication with the robot.
    cyBot_uart_init();

    // Allocate memory for the sensor data.
    oi_t *sensor_data = oi_alloc(); // do this only once at start of main()

    // Initialize the robot's Open Interface and various components.
    oi_init(sensor_data); // do this only once at start of main()
    lcd_init();
    timer_init();
    cyBOT_init_Scan(0b0111);
    right_calibration_value = 264250;
    left_calibration_value = 1235500;

    // Declare a variable for storing the latest scan data.
    cyBOT_Scan_t newScan;

    // Set the robot's wheels to stop.
    oi_setWheels(0,0);

    // Declare some strings for displaying text on the LCD screen.
    int i;
    char scanning[] = "Degrees\t PING Distance (cm)\n";
    char objects[] = "Object number\t\t Object angle\t\t Distance to an object (cm)\t\t Radial width\t\t Object Width\r\n";

    // Loop infinitely.
    while(true) {

        // Read a character from the UART input.
        char y;
        y = cyBot_getByte();

        char sentence [50];
                    float init_distance;
                    float distance;
                    int init_degree;
                    bool start = true;
                    int object_num =0;
                    float obj_Angle;
                    float dist_to_obj;
                    float maxRange = 65.0;
                    int degree_increment =0;
                    float small_obj_dist = 0;
                    float  prev_obj_Angle=0;
                    float prev_obj_inc=0;

        // If the character is 'm', perform a 60-120 degree scan and display the results on the LCD.
        if(y == 'm') {

            // Display a header for the scan results.
            grid_dispay(scanning);

            // Iterate through angles from 60 to 120 degrees in increments of 3.
            float calculation;
            char sentence [100];
            for(i=60; i <=120; i+=3) {

                // Perform a scan at the current angle and store the results in newScan.
                cyBOT_Scan(i, &newScan);

                // Calculate the distance to an object using the IR sensor and display it on the LCD.
                //sprintf(sentence, "%d\t\t%lf\r\n", i, (22.47/(newScan.IR_raw_val/1000.0) - 0.17)); //IR_raw_val

                // Display the distance to an object using the sound sensor on the LCD.
//                sprintf(sentence, "%d\t\t%lf\r\n", i, newScan.sound_dist); // sound_dist
                sprintf(sentence, "%d\t\t%lf\r\n", i, (22.47/(newScan.IR_raw_val/1000.0) - 0.17));
                // Display the formatted string on the LCD.
                makestr(sentence);
            }

            // Turn the robot 80 degrees to the right.
//            turn_right(sensor_data, 80);

            // Move the robot forward and detect collisions.
//            collision_detection_move_forward(sensor_data, 200);
        }

        // If the character is 'n' start the scanning process
        if(y== 'n') {
            oi_setWheels(0,0); //stop
            grid_dispay(objects); //initialize the display for the detected objects



            for(i=0; i <=180; i+=2) { //loop through the range of degrees for scanning

                cyBOT_Scan(i, &newScan); //perform a scan for the current degree
//                distance = newScan.sound_dist; //get the distance of the object using the sound sensor
              distance = (22.47/(newScan.IR_raw_val/1000.0) - 0.17); //get the distance of the object using the IR sensor




                if(distance < maxRange) { //if an object is detected within the maximum range

                    if(start) {
                        init_distance = distance; //initialize the initial distance of the object
                        start = false;
                    }

                    float range = distance - init_distance;

                    if (range > 3 || range < -3) { //if the object is out of range

                        init_distance = distance; //update the initial distance of the object

                        if(degree_increment > 18.0) { //if the object is within range for at least 3 times continuously

                            char sentence [10];

                            object_num++; //increment the object number

                            obj_Angle = (obj_Angle/degree_increment); //get the average angle of the object

                            dist_to_obj = (dist_to_obj/degree_increment/2); //get the average distance to the object

                            double object_width = obj_Angle/360 *2*3.1415926535 * dist_to_obj; //calculate the width of the object

                            sprintf(sentence, "%d\t\t\t%.2f\t\t\t%.2f\t\t\t\t\t%d\t\t\t\t%lf\r\n", object_num, obj_Angle, dist_to_obj, degree_increment, object_width); //store the object information in the sentence variable

                            makestr(sentence); //display the object information

                            if (prev_obj_inc < degree_increment) { // if this object is smaller than the prev object
                                prev_obj_inc = degree_increment;
                                prev_obj_Angle = obj_Angle; //store the angle of the object with the most number of scans
                                small_obj_dist = dist_to_obj;
                            }

                        }
                        degree_increment =0;
                        obj_Angle=0;
                        dist_to_obj=0;
                    }
                    else if (range < 3 && range > -3) { //if the object is within range

                        dist_to_obj += distance; //add the distance of the object to the total distance
                        obj_Angle += i; //add the angle of the object to the total angle
                        degree_increment +=2; //increment the degree increment by 2

                    }

                }
            }

            // Check if the previous object angle is not zero
            if(prev_obj_Angle > 0) {
                // If not zero, scan for new objects in that angle and get the new scan data
                cyBOT_Scan(prev_obj_Angle, &newScan);
                // Make a move based on the sensor data and the previous object angle and distance
                turn_right(sensor_data,90-prev_obj_inc);
                timer_waitMillis(1000);
                collision_detection_move_forward(sensor_data, small_obj_dist);



            }

            // Check if the 'y' key has been pressed
            if(y == 'p') {
                // If pressed, make a move based on the sensor data and the previous object angle and distance
                turn_left(sensor_data, 90);
                // Move forward by the specified distance while checking for any potential collisions.
            //    collision_detection_move_forward(sensor_data, dist);
                timer_waitMillis(1500);
                turn_right(sensor_data, 90);
            }


            // Free the sensor data
//            oi_free(sensor_data);

    }
        if (y=='k'){
            oi_free(sensor_data);
            break;
        }
}
}

// This function makes a move based on the input angle and distance while avoiding collisions.

void make_move(oi_t *sensor_data, int angle, float dist) {

    // If the angle is greater than 90 degrees, turn right.
//    if(angle > 90) {
//        turn_right(sensor_data, angle);
//    }
//    // Otherwise, turn left.
//    else {
//        turn_left(sensor_data, angle);
//    }
//    turn_left(sensor_data, 90-angle);

    // Move forward by the specified distance while checking for any potential collisions.
//    collision_detection_move_forward(sensor_data, dist);
//    timer_waitMillis(3000);


}


// This function takes a character array (string) as input
void makestr(char str []) {

    // Get the length of the input string
    int len = strlen(str);

    int i;

    // Loop through each character in the input string
    for(i =0; i < len; i++) {

        // Send each character over the serial connection
        cyBot_sendByte(str[i]);
    }
}

// This function takes a character array (string) as input
void grid_dispay(char information []) {

    // Send a new line character and carriage return to start a new line
    cyBot_sendByte('\r');
    cyBot_sendByte('\n');

    int p;
    // Get the length of the input string
    int len = strlen(information);

    // Loop through each character in the input string
    for(p =0; p < len; p++) {

        // Send each character over the serial connection
        cyBot_sendByte(information[p]);
    }

    // Send a new line character and carriage return to end the line
    cyBot_sendByte('\r');
    cyBot_sendByte('\n');
}


