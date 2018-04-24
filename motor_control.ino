
#include <Wire.h>
#include <I2CEncoder.h>
#include <NewPing.h>

/**
 * Author(s): Evan Cleary, Gabriel Bowerson, Nathan Sarrault
 * Date: 4/23/2018
 * Class: CE-442
 * Assignment: Lab 3
 *
 * Implements more advanced control of a differential drive robot
 * Allows for encoders and ultrasonic sensor
 *
 */
#define START_BUTTON_PIN 11

#define MOTOR_LEFT_DIR_PIN 2
#define MOTOR_LEFT_DRIVE_PIN 3
#define MOTOR_RIGHT_DIR_PIN 4
#define MOTOR_RIGHT_DRIVE_PIN 5

#include "motor.h"
#include "robot.h"
char enabled = 0;
char dir = 0;

Motor motorLeft(MOTOR_LEFT_DIR_PIN, MOTOR_LEFT_DRIVE_PIN, 1);
Motor motorRight(MOTOR_RIGHT_DIR_PIN, MOTOR_RIGHT_DRIVE_PIN, 0, 1.0f);
NewPing ultraSonic(12, 13);
I2CEncoder leftEncoder, rightEncoder;
Robot first_robot(&motorLeft, &motorRight, &leftEncoder, &rightEncoder, &ultraSonic);

void setup() {
  // put your setup code here, to run once:
  Wire.begin();
  Serial.begin(9600);
  Serial.println("Initializing");
  rightEncoder.init(MOTOR_393_TORQUE_ROTATIONS, MOTOR_393_TIME_DELTA);
  leftEncoder.init(MOTOR_393_TORQUE_ROTATIONS, MOTOR_393_TIME_DELTA);
  leftEncoder.setReversed(true);
  //rightEncoder.setReversed(true);
  Serial.println("Initialized");
}

int power = 0;
void loop() {
  int pwm;
  // put your main code here, to run repeatedly:
  if(!enabled) {
    enabled = digitalRead(START_BUTTON_PIN);
    return;
  }

  first_robot.forward(12.0f, 48);
  first_robot.turn_left(90);
  first_robot.forward(12.0f, 48);
  first_robot.turn_left(90);
  first_robot.forward(12.0f, 48);
  first_robot.turn_left(90);
  first_robot.forward(12.0f, 48);
  first_robot.turn_left(90);
  enabled = 0;

 // power+= 10;
}

