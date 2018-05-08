/**
 * Author(s): Evan Cleary, Gabriel Bowerson, Nathan Sarrault
 * Date: 4/23/2018
 * Amended: 4/30/2018
 * Class: CE-442
 * Assignment: Lab 3
 *
 * Robot class that controls a differential drive system with encoders of the wheels.
 * Takes in 2 motors, 2 encoders, an ultrasonic sensor, and light sensor
 */
#include "robot.h"
#include <Arduino.h>

#define PROP_VAL 5.0f
#define DIST_KP  2.0f

Robot::Robot(Motor* leftMotor, Motor* rightMotor, I2CEncoder* leftEncoder, I2CEncoder* rightEncoder, NewPing* ultraSonic, LightSensor* lightSensor) {
  m_leftMotor = leftMotor;
  m_rightMotor = rightMotor;
  m_leftEncoder = leftEncoder;
  m_rightEncoder = rightEncoder;
  m_ultraSonic = ultraSonic;
  m_lightSensor = lightSensor;
}

/**
 * Turns the robot right, in place, the given degrees
 * 
 * @param degrees, How many degrees are we turning?
 */
void Robot::turn_right(float degrees) {
  int l_speed = initialSpeed(12.0f);
  int leftEnc = 0, rightEnc = 0;
  float traveled = 0;
  float error = 0;
  m_leftEncoder->zero();
  m_rightEncoder->zero();
  m_leftMotor->forward(l_speed);
  m_rightMotor->backward(l_speed);
  while(traveled < degrees){
    delay(50);
    leftEnc = abs(m_leftEncoder->getRawPosition());
    rightEnc = abs(m_rightEncoder->getRawPosition());
    error = (leftEnc-rightEnc)/PROP_VAL;
    m_leftEncoder->zero();
    m_rightEncoder->zero();
    
    m_leftMotor->forward(l_speed);
    m_rightMotor->backward(l_speed + error);

    traveled += leftEnc*0.2154;
  }
  stop();
  m_leftEncoder->zero();
  m_rightEncoder->zero();
}

/**
 * Turns the robot left, in place, the given degrees
 * 
 * @param degrees, How many degrees are we turning?
 */
void Robot::turn_left(float degrees) {
  int l_speed = initialSpeed(12.0f);
  int leftEnc = 0, rightEnc = 0;
  float traveled = 0;
  float error = 0;
  m_leftEncoder->zero();
  m_rightEncoder->zero();
  m_leftMotor->backward(l_speed);
  m_rightMotor->forward(l_speed);
  while(traveled < degrees){
    delay(50);
    leftEnc = abs(m_leftEncoder->getRawPosition());
    rightEnc = abs(m_rightEncoder->getRawPosition());
    error = (leftEnc-rightEnc)/PROP_VAL;
    m_leftEncoder->zero();
    m_rightEncoder->zero();
    
    m_leftMotor->backward(l_speed);
    m_rightMotor->forward(l_speed + error);

    traveled += leftEnc*0.2289;
  }
  stop();
  m_leftEncoder->zero();
  m_rightEncoder->zero();
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
  forward(speed, distance, 1);
}

/**
 * Moves the robot forward at the given speed for the given distance
 * Speed is defined in inches/sec, Distance is defined in inches
 * 
 * @param speed Speed of the robot in inches/sec
 * @param distance Distance for robot to travel in inches
 * @param collision_det Are we checking for collisions?
 */
void Robot::forward(float speed, int distance, char collision_det) {
  int l_speed = Robot::initialSpeed(speed);
  float finalDist = (distance/(10.16f*PI))*627.2;
  int traveled = 0;
  LightCollision* lCol;
  while(traveled < finalDist || finalDist < 0) {
    traveled += drive(l_speed, 1);
    
    if(collision_det) {
      lCol = light_wall();
      if(lCol->left) {
        stop();
        turn_left(90);
      } else if(lCol->right) {
        stop();
        turn_right(90);
      }
    }
    delay(100);
  }
  stop();
}

void Robot::forward_collision(float speed, int threshold) {
  int l_speed = Robot::initialSpeed(speed);
  while(!collision(threshold)) {
    drive(l_speed, 1);
    delay(50);
  }
  stop();
}

void Robot::backward(float speed, int distance) {
  int l_speed = Robot::initialSpeed(speed);
  float finalDist = (distance/(10.16f*PI))*627.2;
  int traveled = 0;
  while(traveled < finalDist || finalDist < 0) {
    traveled += drive(l_speed, 0);
    Serial.print("Traveled: ");
    Serial.print(traveled);
    Serial.print("/");
    Serial.println(finalDist);
    delay(100);
  }
  stop();
}

int Robot::drive(float speed, char dir) {
    float error = 0;
    int rightEnc, leftEnc;
    rightEnc = abs(m_rightEncoder->getRawPosition());
    leftEnc = abs(m_leftEncoder->getRawPosition());
    error = (leftEnc - rightEnc)/PROP_VAL;
    m_rightEncoder->zero();
    m_leftEncoder->zero();
    if(dir) {
      m_leftMotor->forward(speed);
      m_rightMotor->forward(speed + error);
    } else {
      m_leftMotor->backward(speed);
      m_rightMotor->backward(speed + error);
    }
    return leftEnc;
}

/**
 * Enables the line following algorithm of the robot
 * This will follow a black line.
 * 
 * @param speed, Speed in inches/sec
 */
void Robot::line_follow(float speed) {
  float l_speed = initialSpeed(speed);
  float r_speed = l_speed;
  float r_scale = 1, l_scale = 1, e_scale = 1;
  int rightEnc, leftEnc;
  int track_dir = 0;
  LightCollision* lCol;
  float error = 0;
  while(1) {
    if(collision(50)) {
      stop();
      continue;
    }
    lCol = m_lightSensor->check_collisions();
    if(lCol->left || lCol->right){
      if(lCol->left) {
        l_scale = 0;
        r_scale = 1.3;
      }
      if(lCol->right) {
        l_scale = 1.3;
        r_scale = 0;
      }
      e_scale = 0;
    } else if(lCol->center){
      l_scale = 1;
      r_scale = 1;
      e_scale = 1;
    }
    rightEnc = m_rightEncoder->getRawPosition();
    leftEnc = m_leftEncoder->getRawPosition();
    error = (leftEnc - rightEnc)/PROP_VAL;
    m_rightEncoder->zero();
    m_leftEncoder->zero();
    m_leftMotor->forward(l_speed*l_scale);
    m_rightMotor->forward(r_speed*r_scale + error*e_scale);
    delay(50);
  }
}

/**
 * Moves the robot forward at the given speed for an unlimited distance.
 * @param speed in inches/sec
 */
void Robot::forward_indeterminate(float speed) {
  forward(speed, -1);
}

/**
 * Makes the robot maintain a certain distance in CM from an object
 */
void Robot::maintain_distance(float distance) {
  while(true) {
    int ac_dist = m_ultraSonic->ping_cm();
    Serial.println(ac_dist);
    float error = ac_dist - distance;
    if (ac_dist) {
      if (error > 0) {
        forward(12, error/DIST_KP, 0);
      } else if (error < 0) {
        backward(12, -1*error/DIST_KP);
      }
    } else {
      forward_collision(12, distance);
    }
    delay(25);
  }
}

/**
 * Stops the robot
 */
void Robot::stop() {
  m_rightMotor->stop();
  m_leftMotor->stop();
  delay(100);
}

/**
 * Checks for collisions on the light sensor
 */
LightCollision* Robot::light_wall() {
  return m_lightSensor->check_collisions();
}

/**
 * Detects collisions 1.5 feet from the robot.
 * 
 * @returns whether the robot is about to collide with something
 */
bool Robot::collision(int threshold) {
  int distance = m_ultraSonic->ping_cm();
  if(distance== 0) return false;
  return distance < threshold;
}

