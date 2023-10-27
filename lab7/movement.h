/*
 * movement.h
 *
 *  Created on: Jan 30, 2023
 *      Author:
 */

#ifndef MOVEMENT_H_
#define MOVEMENT_H_

#include <stdio.h>
#include "movement.h"
#include "open_interface.h"
#include "Timer.h"

double move_forward (oi_t *sensor_data, double distance_mm);
double turn_left(oi_t *sensor_data, double degrees);
double turn_right(oi_t *sensor_data, double degrees);
double collision_detection_move_forward(oi_t *sensor_data, double distance_mm);



#endif /* MOVEMENT_H_ */
