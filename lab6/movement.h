

#ifndef MOVEMENT_H_
#define MOVEMENT_H_

//double move_forward(oi_t *sensor_data, double distance_mm){};
double move_forward(oi_t *sensor_data, double distance_mm);
double move_backward(oi_t *sensor_data, double distance_mm);
double turn_left(oi_t *sensor_data, double degrees);
double turn_right(oi_t *sensor_data, double degrees);
double collision_detect(oi_t *sensor_data, double distance_mm, double degLeft, double degRight, double back, double lat);



#endif /* MOVEMENT_H_ */
