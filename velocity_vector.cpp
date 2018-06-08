/**
 * Author(s): Evan Cleary, Gabriel Bowerson, Nathan Sarrault
 * Date: 6/7/2018
 * Class: CE-442
 * Assignment: Lab 5
 *
 * Utility to convert offsets to relative linear velocities.
 * This assumes a target target radius with the offset being the
 * chord of a circle stretch across 30Degrees of the circle.
 */
#include "velocity_vector.h"
#include "arduino.h"

void offset_to_vel(VisionOffset* off, Velocity* vel) {
  double curve = sqrt(off->x*off->x + off->z*off->z)/(1.3*23.0);
  double velocity = (12-(24*curve))/(2*curve+1);
  if(off->x < 0){
    vel->vr = 12+velocity;
    vel->vl = vel->y;
    vel->omega = 1;
  } else if(off->x > 0){
    vel->vl = 12+velocity;
    vel->vr = vel->y;
    vel->omega = 1;
  } else {
    vel->vl = vel->y;
    vel->vr = vel->y;
    vel->omega = 0;
  }

    
}
