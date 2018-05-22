#include "velocity_vector.h"
#include "arduino.h"

void offset_to_vel(VisionOffset* off, Velocity* vel) {
    int flip = (off->x < 0 ? -1 : 1);
    double curve = (6*sqrt(off->x*off->x + off->z*off->z))/(23*PI);
    vel->omega = ((vel->y*(curve+flip))/(curve-flip) - vel->y);
}
