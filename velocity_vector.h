#ifndef _H_VEL_VECTOR
#define _H_VEL_VECTOR
#include "vision.h"
struct vel_vect {
    float x,y;
    float omega;
    float vl,vr;
};

typedef struct vel_vect Velocity;

void offset_to_vel(VisionOffset* off, Velocity* vel);

#endif
