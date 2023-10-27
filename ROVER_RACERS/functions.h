/**
 * @author Benjamin Muslic, Manjul Balayar, Kalem Shrock, Dino & Adin Huric
 */

#ifndef FUNCTIONS_H__
#define FUNCTIONS_H_H_

#include "open_interface.h"

int move_forward(oi_t *sensor_data);
int boost(oi_t *sensor_data);
void move_reverse();
void turn_left();
void turn_right();
void emergency_brake();
int check_bump(oi_t *sensor_data);
int check_boundary(oi_t *sensor_data);
int check_cliff(oi_t *sensor_data);
void ir(oi_t *sensor_data);
void ping(oi_t *sensor_data);
void double_scan(void);
void reposition();


extern int reposition_done;
extern float heading;

#endif /FUNCTIONS_H__H_ */
