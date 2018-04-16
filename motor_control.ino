/**
 * Author(s): Evan Cleary, Gabriel Bowerson, Nathan Sarrault
 * Date: 4/17/2018
 * Class: CE-442
 * Assignment: Lab 2
 *
 * Basic controls of a differential drive robot.
 * Has functions that support moving forward, turning left,
 * going in a square, and navigating a figure 8.
 *
 */
#define START_BUTTON_PIN 12

#define MOTOR_LEFT_DIR_PIN 2
#define MOTOR_LEFT_DRIVE_PIN 3
#define MOTOR_RIGHT_DIR_PIN 4
#define MOTOR_RIGHT_DRIVE_PIN 5

#define MOTOR_POWER 50
#define MOTOR_POWER_FIGURE 60
#define MOTOR_ON_SQUARE_50 2950
#define MOTOR_ON_SQUARE_80 1650
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
  delay(670);
  motorRight.stop();
  motorLeft.stop();
}

void moveForward(int forward_time, int power) {
  motorRight.forward(power); 
  motorLeft.forward(power);
  delay(forward_time);
  motorRight.stop();
  motorLeft.stop();
}

void runSquare(){
  moveForward(MOTOR_ON_SQUARE_50, MOTOR_POWER);
  turnLeft90();
  moveForward(MOTOR_ON_SQUARE_50, MOTOR_POWER);
  turnLeft90();
  moveForward(MOTOR_ON_SQUARE_50, MOTOR_POWER);
  turnLeft90();
  moveForward(MOTOR_ON_SQUARE_50, MOTOR_POWER);
  turnLeft90();
}

void runSquare80(){
  moveForward(MOTOR_ON_SQUARE_80, 80);
  turnLeft90();
  moveForward(MOTOR_ON_SQUARE_80, 80);
  turnLeft90();
  moveForward(MOTOR_ON_SQUARE_80, 80);
  turnLeft90();
  moveForward(MOTOR_ON_SQUARE_80, 80);
  turnLeft90();
}

void runFigure8() {
  motorLeft.forward(MOTOR_POWER_FIGURE-25);
  motorRight.forward(MOTOR_POWER_FIGURE);
  delay(9800);
  motorLeft.stop();
  motorRight.stop();
  delay(150);
  motorLeft.forward(MOTOR_POWER_FIGURE + 1);
  motorRight.forward(MOTOR_POWER_FIGURE - 25);
  delay(10150);
  motorLeft.stop();
  motorRight.stop();

  motorLeft.forward(100);
  motorRight.backward(100);
  delay(2500);
  motorLeft.stop();
  motorRight.stop();
}

void loop() {
  int pwm;
  // put your main code here, to run repeatedly:
  if(!enabled) {
    enabled = digitalRead(START_BUTTON_PIN);
    return;
  }
  //runSquare();
  //runSquare80();
  runFigure8();
  enabled = 0;
}

