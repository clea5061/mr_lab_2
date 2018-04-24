/**
 * Author(s): Evan Cleary, Gabriel Bowerson, Nathan Sarrault
 * Date: 4/23/2018
 * Class: CE-442
 * Assignment: Lab 3
 *
 * Robot class that controls a differential drive system with encoders of the wheels.
 * Takes in 2 motors, 2 encoders, and an ultrasonic sensor
 */
#include "robot.h"
#include <Arduino.h>

#define DEGREES_PER_SECOND 75.6f

Robot::Robot(Motor* leftMotor, Motor* rightMotor, I2CEncoder* leftEncoder, I2CEncoder* rightEncoder, NewPing* ultraSonic) {
  m_leftMotor = leftMotor;
  m_rightMotor = rightMotor;
  m_leftEncoder = leftEncoder;
  m_rightEncoder = rightEncoder;
  m_ultraSonic = ultraSonic;
}

/**
 * Turns the robot right, in place, the given degrees
 * 
 * @param degrees, How many degrees are we turning?
 */
void Robot::turn_right(float degrees) {
  int turnTime = (degrees/DEGREES_PER_SECOND)*1000;
  int start = millis();
  int last = millis();
  m_leftMotor->forward(initialSpeed(12));
  m_rightMotor->backward(initialSpeed(12));
    while(millis()-start < turnTime) {
    m_leftMotor->forward(calculatePowerLevel(12, m_leftMotor->get_drive_percent(), m_leftEncoder->getRawPosition(), millis()-last));
    m_rightMotor->backward(calculatePowerLevel(12, m_rightMotor->get_drive_percent(), -1*m_rightEncoder->getRawPosition(), millis()-last));
    m_leftEncoder->zero();
    m_rightEncoder->zero();
    last = millis();
  }
  m_rightMotor->stop();
  m_leftMotor->stop();
}

/**
 * Turns the robot left, in place, the given degrees
 * 
 * @param degrees, How many degrees are we turning?
 */
void Robot::turn_left(float degrees) {
  int turnTime = (degrees/DEGREES_PER_SECOND)*1000;
  int start = millis();
  int last = millis();
  m_leftMotor->backward(initialSpeed(12));
  m_rightMotor->forward(initialSpeed(12));
  while(millis()-start < turnTime) {
    m_leftMotor->backward(calculatePowerLevel(12, m_leftMotor->get_drive_percent(), -1*m_leftEncoder->getRawPosition(), millis()-last));
    m_rightMotor->forward(calculatePowerLevel(12, m_rightMotor->get_drive_percent(), m_rightEncoder->getRawPosition(), millis()-last));
    m_leftEncoder->zero();
    m_rightEncoder->zero();
    last = millis();
  }
  m_rightMotor->stop();
  m_leftMotor->stop();
}

/**
 * Calculates the percent power level based on the target speed and real speed of the robot
 * This works to achieve a linear velocity
 */
int Robot::calculatePowerLevel(float targetSpeed, int powerLevel, float realSpeed, float timeDelta) {
  float realSpeedTime = (realSpeed/timeDelta)*1000; // Multiply by 1000 to get ticks/second
  float revSec = realSpeedTime/627.2f;
  float linVel = revSec*4*PI;
  if(linVel < targetSpeed) {
    powerLevel++;
  } else {
    powerLevel--;
  }
  //Serial.println(powerLevel);
  return powerLevel;
}

/**
 * Calcualte initial speed, this was found utilizing a linear regression
 * of power level vs encoder ticks
 */
int Robot::initialSpeed(float speed) {
  return 3.25f * speed + 5.4;
}

/**
 * Moves the robot forward at the given speed for the given distance
 * Speed is defined in inches/sec, Distance is defined in inches
 * 
 * @param speed Speed of the robot in inches/sec
 * @param distance Distance for robot to travel in inches
 */
void Robot::forward(float speed, int distance) {
  float calcDistance = 0;
  int rightEnc, leftEnc;
  int startTime = 0;
  int lastTime = 0, dT = 0;
  int initSpeed = initialSpeed(speed);
  m_rightMotor->forward(initSpeed);
  m_leftMotor->forward(initSpeed);
  startTime = millis();
  // Lock into drive loop until we have traversed out distance
  while(calcDistance < distance-3) { //We subtract 3 because of some overshoot when breaking
    dT = millis()-lastTime;
    lastTime = millis();
    if(dT <= 0 ){
      dT = 1;  
    }
    rightEnc = m_rightEncoder->getRawPosition();
    leftEnc = m_leftEncoder->getRawPosition();
    Serial.print("Right: ");
    Serial.println(rightEnc);
    Serial.print("Left: ");
    Serial.println(leftEnc);
    calcDistance += (((rightEnc+leftEnc)/2)/627.2)*4*PI;
    m_rightEncoder->zero();
    m_leftEncoder->zero();
    if (collision()) {
       if(random(500) < 250) {
        turn_left(90);
       } else {
        turn_right(90);
       }
    }
    m_rightMotor->forward(calculatePowerLevel(speed, m_rightMotor->get_drive_percent(), rightEnc, dT));
    m_leftMotor->forward(calculatePowerLevel(speed, m_leftMotor->get_drive_percent(), leftEnc, dT));
    delay(100);
  //Serial.println(calcDistance);
  }
  m_rightMotor->stop();
  m_leftMotor->stop();
}

/**
 * Detects collisions 1.5 feet fro mthe robot.
 * 
 * @returns whether the robot is about to collide with something
 */
bool Robot::collision() {
  int distance = m_ultraSonic->ping_in();
  return distance < 18;
}

