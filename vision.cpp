/**
 * Author(s): Evan Cleary, Gabriel Bowerson, Nathan Sarrault
 * Date: 6/7/2018
 * Class: CE-442
 * Assignment: Lab 5
 *
 * Computer vision utility utilized to communicate with the
 * raspberry pi. This returns the offset from center with object
 * distance.
 */
#include "vision.h"
#include "arduino.h"

Vision::Vision(){}

VisionOffset* Vision::get_object_offset() {
    Serial.print('\5');
    Serial.print("OFF"); // Request offset
    Serial.print('\6');
    char i = 0;
    char* pch;
    long start = millis();
    // Let serial time out after 1.5 seconds
    while (Serial.available() == 0) {
        if(start-millis() >= 1500)
            return &mOffset;
    }
    char active = 0;
    while(Serial.available() > 0) {
        char c = Serial.read();
        //Check for start character
        if (c == '!' && !active) {
          active = 1;
          continue;
        }
        //check for end character
        if (c == '\n') {
            for(;i<15;i++)
                mBuffer[i]='\0';
            Serial.println(mBuffer);
            sscanf(mBuffer,"%d,%d,%d", &mOffset.x, &mOffset.y, &mOffset.z);
            i=0;
        }
        if(active) {
          //We overflowed for some reason, booo
          if(i >= 15) return &mOffset;
          mBuffer[i++] = c;
        }
    }
    return &mOffset;
}
