#include "vision.h"
#include "arduino.h"

Vision::Vision(){}

VisionOffset* Vision::get_object_offset() {
    Serial.print('\5');
    Serial.print("OFF");
    Serial.print('\6');
    char i = 0;
    char* pch;
    long start = millis();
    while (Serial.available() == 0) {
        if(start-millis() >= 1500)
            return &mOffset;
    }
    char active = 0;
    while(Serial.available() > 0) {
        char c = Serial.read();
        if (c == '!' && !active) {
          active = 1;
          continue;
        }
        if (c == '\n') {
            for(;i<15;i++)
                mBuffer[i]='\0';
//            pch = strtok(mBuffer,",");
//            mOffset.x = atoi(pch);
//            pch = strtok(NULL, ",");
//            mOffset.y = atoi(pch);
//            pch = strtok(NULL, ",");
//            mOffset.z = atoi(pch);
            Serial.println(mBuffer);
            sscanf(mBuffer,"%d,%d,%d", &mOffset.x, &mOffset.y, &mOffset.z);
            i=0;
        }
        if(active) {
          if(i >= 15) return &mOffset;
          mBuffer[i++] = c;
        }
    }
    return &mOffset;
}
