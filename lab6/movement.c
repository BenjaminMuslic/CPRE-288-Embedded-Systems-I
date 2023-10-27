
#include "open_interface.h"
#include "Timer.h"
#include "lcd.h"
#include "movement.h"

double move_forward(oi_t *sensor_data, double distance_mm){
    double sum = 0;

    oi_setWheels(100, 100);

        while(sum < distance_mm){
            oi_update(sensor_data);
            sum += sensor_data -> distance;
            lcd_clear();
            lcd_printf("Distance (in mm): %lf", sum);


        }

    oi_setWheels(0, 0);

    return sum;
}

double move_backward(oi_t *sensor_data, double distance_mm){
    double sum = 0;

    oi_setWheels(-100, -100);

        while(sum > distance_mm){
            oi_update(sensor_data);
            sum += sensor_data -> distance;
            lcd_clear();
            lcd_printf("Distance (in mm): %lf", sum);
        }

    oi_setWheels(0, 0);

    return sum;
}

double turn_left(oi_t *sensor_data, double degrees){
    double sum = 0;

            oi_setWheels(50, -50);

                while(sum < degrees){
                    oi_update(sensor_data);
                    sum += sensor_data -> angle;
                    lcd_clear();
                    lcd_printf("angle (in degrees): %lf", sum);
                }

            oi_setWheels(0, 0);

            return sum;
}

double turn_right(oi_t *sensor_data, double degrees){
    double sum = 0;

        oi_setWheels(-50, 50);

            while(sum > degrees){
                oi_update(sensor_data);
                sum += sensor_data -> angle;
                lcd_clear();
                lcd_printf("angle (in degrees): %lf", sum);
            }

        oi_setWheels(0, 0);

        return sum;
}

double collision_detect(oi_t *sensor_data, double distance_mm, double degLeft, double degRight, double back, double lat){
    double sum = 0;
    double temp = 0;
    double lateral = 0;
    int checkLeft = 0;
    int checkRight = 0;

        oi_setWheels(100, 100);

            while(sum < distance_mm){
                oi_update(sensor_data);
                sum += sensor_data -> distance;
                temp = sum;
                lcd_clear();
                lcd_printf("Distance (in mm): %lf", sum);

//                if(sensor_data -> bumpLeft == 1 && sensor_data -> bumpRight == 1){
//
//                    oi_setWheels(-100, -100);
//
//                    while(sum > temp-150){
//                        sum -= sensor_data -> distance;
//                        lcd_clear();
//                        lcd_printf("Distance (in mm): %f", sum);
//                    }
//
//                    oi_setWheels(0, 0);
//
//                    double turn_right(oi_t *sensor_data, double degrees);
//
//                    oi_setWheels(100, 100);
//
//                    while(lateral < 250){
//                        oi_update(sensor_data);
//                        lateral += sensor_data -> distance;
//                    }
//
//                    oi_setWheels(0, 0);
//
//                    double turn_left(oi_t *sensor_data, double degrees);
//
//                    oi_setWheels(100, 100);
//                }else
                    if(sensor_data -> bumpLeft == 1){
                        checkLeft = 1;
                    }

                    if(sensor_data -> bumpRight == 1){
                        checkRight = 1;
                    }

                    if(checkLeft == 1){
                    oi_setWheels(0, 0);

//                    while(sum > temp-150){
//                        oi_setWheels(-100, -100);
//                        sum += sensor_data -> distance;
//                        lcd_clear();
//                        lcd_printf("Distance (in mm): %lf", sum);
//                    }

                    timer_waitMillis(300);

                    move_backward(sensor_data, back);

                    sum -= 150;

                    oi_setWheels(0, 0);

                    timer_waitMillis(300);

                    turn_right(sensor_data, degRight);

//                    oi_setWheels(100, 100);
//
//                    while(lateral < 250){
//                        oi_update(sensor_data);
//                        lateral += sensor_data -> distance;
//                    }

                    timer_waitMillis(300);

                    move_forward(sensor_data, lat);

                    oi_setWheels(0, 0);

                    timer_waitMillis(300);

                    turn_left(sensor_data, degLeft);

                    timer_waitMillis(300);

                    oi_setWheels(100, 100);

                    checkLeft = 0;
                }else if(checkRight == 1){
//                    oi_setWheels(-100, -100);
//
//                    while(sum > temp-150){
//                        sum -= sensor_data -> distance;
//                        lcd_clear();
//                        lcd_printf("Distance (in mm): %lf", sum);
//
//                    }
//
//                    oi_setWheels(0, 0);
//
//                    double turn_right(oi_t *sensor_data, double degrees);
//
//                    oi_setWheels(100, 100);
//
//                    while(lateral < 250){
//                        oi_update(sensor_data);
//                        lateral += sensor_data -> distance;
//                    }
//
//                    oi_setWheels(0, 0);
//
//                    double turn_left(oi_t *sensor_data, double degrees);
//
//                    oi_setWheels(100, 100);

                    oi_setWheels(0, 0);

                    //                    while(sum > temp-150){
                    //                        oi_setWheels(-100, -100);
                    //                        sum += sensor_data -> distance;
                    //                        lcd_clear();
                    //                        lcd_printf("Distance (in mm): %lf", sum);
                    //                    }

                    timer_waitMillis(300);

                    move_backward(sensor_data, back);

                    sum -= 150;

                    oi_setWheels(0, 0);

                    timer_waitMillis(300);

                    turn_left(sensor_data, degLeft);

                    //                    oi_setWheels(100, 100);
                    //
                    //                    while(lateral < 250){
                    //                        oi_update(sensor_data);
                    //                        lateral += sensor_data -> distance;
                    //                    }

                    timer_waitMillis(300);

                    move_forward(sensor_data, lat);

                    oi_setWheels(0, 0);

                    timer_waitMillis(300);

                    turn_right(sensor_data, degRight);

                    timer_waitMillis(300);

                    oi_setWheels(100, 100);

                    checkRight = 0;
                }

            }

        oi_setWheels(0, 0);

        return sum;

}




