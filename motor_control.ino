#define START_BUTTON_PIN 12

#define MOTOR_LEFT_DIR_PIN 2
#define MOTOR_LEFT_DRIVE_PIN 3
#define MOTOR_RIGHT_DIR_PIN 4
#define MOTOR_RIGHT_DRIVE_PIN 5

#define MOTOR_POWER 60
#define MOTOR_ON 2666
#include "motor.h"

char enabled = 0;
char dir = 0;

Motor motorLeft(MOTOR_LEFT_DIR_PIN, MOTOR_LEFT_DRIVE_PIN, 1);
Motor motorRight(MOTOR_RIGHT_DIR_PIN, MOTOR_RIGHT_DRIVE_PIN, 0, 1.0f);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void turnLeft90() {
  motorRight.forward(50);
  motorLeft.backward(50);
  delay(710);
  motorRight.stop();
  motorLeft.stop();
}

void moveForward(int forward_time) {
  motorRight.forward(MOTOR_POWER); 
  motorLeft.forward(MOTOR_POWER);
  delay(forward_time);
  motorRight.stop();
  motorLeft.stop();
}

void runSquare(){
  moveForward(MOTOR_ON);
  turnLeft90();
  moveForward(MOTOR_ON);
  turnLeft90();
  moveForward(MOTOR_ON);
  turnLeft90();
  moveForward(MOTOR_ON);
  turnLeft90();
}

void loop() {
  int pwm;
  // put your main code here, to run repeatedly:
  if(!enabled) {
    enabled = digitalRead(START_BUTTON_PIN);
    return;
  }

  motorLeft.forward(MOTOR_POWER-30);
  motorRight.forward(MOTOR_POWER);
  delay(8525);
  motorLeft.forward(MOTOR_POWER);
  motorRight.forward(MOTOR_POWER-30)
  delay(8525);
  motorLeft.stop();
  motorRight.stop();
  
  
  
  enabled = 0;
//  motorRight.forward(30);
//
//  delay(10000);
//  motorLeft.stop();
//  motorRight.stop();
//  
//  motorLeft.forward(30);
//  motorRight.backward(30);
//
//  delay(10000);
//  motorLeft.stop();
//  motorRight.stop();
}

