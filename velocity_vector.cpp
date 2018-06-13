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

void read_velocity(Velocity* vel) {
  char mBuffer[24];
  char active = 0, i = 0;
  char * strtokIndx;
  while(Serial.available() > 0) {
        char c = Serial.read();
        //Check for start character
        if (c == '!' && !active) {
          active = 1;
          continue;
        }
        //check for end character
        if (c == '\n') {
            for(;i<24;i++)
                mBuffer[i]='\0';
            strtokIndx = strtok(mBuffer,",");
            vel->y = atof(strtokIndx);
            strtokIndx = strtok(NULL,",");
            vel->vr = atof(strtokIndx);
            strtokIndx = strtok(NULL,",");
            vel->vl = atof(strtokIndx);
            i=0;
            active = 0;
            continue;
        }
        if(active) {
          //We overflowed for some reason, booo
          if(i >= 24) break;
          mBuffer[i++] = c;
        }
    }
}
