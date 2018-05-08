/**
 * Author(s): Evan Cleary, Gabriel Bowerson, Nathan Sarrault
 * Date: 4/23/2018
 * Ammended: 4/30/2018
 * Class: CE-442
 * Assignment: Lab 3
 *
 * Robot class structure
 *
 */
#ifndef ROBOT_H
#define ROBOT_H
#include "motor.h"
#include "light_sensor.h"
#include <Wire.h>
#include <I2CEncoder.h>
#include <NewPing.h>

class Robot {
  public:
    Robot(Motor* left, Motor* right, I2CEncoder* leftE, I2CEncoder* rightE, NewPing* ultra, LightSensor* light_sensor);
    void turn_right(float);
    void turn_left(float);
    void forward(float, int);
    void backward(float, int);
    void forward(float, int, char);
    void forward_indeterminate(float);
    void forward_collision(float, int);
    void maintain_distance(float);
    void backward(int);
    void stop();
    void line_follow(float);
 protected:
    int initialSpeed(float speed);
    int drive(float speed, char direction);
    LightCollision* light_wall();
    Motor* m_rightMotor;
    Motor* m_leftMotor;
    LightSensor* m_lightSensor;
    bool collision(int);
    float m_leftMotor_average;
    float m_rightMotor_average;
    I2CEncoder* m_leftEncoder;
    I2CEncoder* m_rightEncoder;
    NewPing* m_ultraSonic;
};
#endif
