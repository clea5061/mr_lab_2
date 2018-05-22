#include "vision.h"
#include "arduino.h"

Vision::Vision(){}

VisionOffset* Vision::get_object_offset() {
    Serial.print('\5');
    Serial.print("OFF");
    Serial.print('\6');
    char i = 0;
    while(Serial.available() > 0) {
        char c = Serial.read();
        if (c == '\n') {
            for(;i<15;i++)
                mBuffer[i]='\0';
            sscanf(mBuffer, "%d,%d,%d", mOffset.x, mOffset.y, mOffset.z);
            i=0;
        }
        mBuffer[i++] = c;
    }
    return &mOffset;
}