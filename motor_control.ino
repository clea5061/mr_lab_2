
/**
 * Author(s): Evan Cleary, Gabriel Bowerson, Nathan Sarrault
 * Date: 4/23/2018
 * Amended: 4/30/2018
 * Class: CE-442
 * Assignment: Lab 4
 *
 * Implements more advanced control of a differential drive robot
 * Allows for encoders, ultrasonic sensor, and light sensor
 *
 */
 
#include <Wire.h>
#include <I2CEncoder.h>
#include <NewPing.h>
#include "pinout.h"
#include "motor.h"
#include "robot.h"
#include "robotv2.h"
#include "light_sensor.h"

#define DEL 500

char enabled = 0;
char dir = 0;

I2CEncoder leftEncoder, rightEncoder;
Motor motorLeft(MOTOR_LEFT_DIR_PIN, MOTOR_LEFT_DRIVE_PIN, &leftEncoder, 0);
Motor motorRight(MOTOR_RIGHT_DIR_PIN, MOTOR_RIGHT_DRIVE_PIN, &rightEncoder, 1, 1.0f);
NewPing ultraSonic(12, 13);
LightSensor ls(LIGHT_SENSOR_LEFT_PIN, LIGHT_SENSOR_CENTER_PIN, LIGHT_SENSOR_RIGHT_PIN);
Vision vision;
Robot2 second_robot(&motorLeft, &motorRight);

void setup() {
  // put your setup code here, to run once:
  Wire.begin();
  rightEncoder.init(MOTOR_393_TORQUE_ROTATIONS, MOTOR_393_TIME_DELTA);
  leftEncoder.init(MOTOR_393_TORQUE_ROTATIONS, MOTOR_393_TIME_DELTA);
  leftEncoder.setReversed(true);
  second_robot.enable_vision(&vision);
  second_robot.enable_collision(&ultraSonic);
  
  Serial.begin(57600);
  //rightEncoder.setReversed(true);
}

int power = 0;
int first = 0;
LightCollision* collision;
void loop() {
  int pwm;
  // put your main code here, to run repeatedly:
  if(!enabled) {
    enabled = digitalRead(START_BUTTON_PIN);
    return;
  }
  // if(!first) {
  //   ls.calibrate();
  //   first = 1;
  //   delay(1000);
  //   enabled = 0;
  //   return;
  // }
  
  //collision = ls.check_collisions();
  //first_robot.forward_indeterminate(12.0f);
  second_robot.drive(8);

  //first_robot.line_follow(12.0f);
  enabled = 0;
}

