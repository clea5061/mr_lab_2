/**
 * Author(s): Evan Cleary, Gabriel Bowerson, Nathan Sarrault
 * Date: 4/23/2018
 * Class: CE-442
 * Assignment: Lab 3
 *
 * Robot class structure
 *
 */
 #ifndef ROBOT_H
#define ROBOT_H
#include "motor.h"
#include <Wire.h>
#include <I2CEncoder.h>
#include <NewPing.h>

class Robot {
  public:
    Robot(Motor* left, Motor* right, I2CEncoder* leftE, I2CEncoder* rightE, NewPing* ultra);
    void turn_right(float);
    void turn_left(float);
    void forward(float, int);
    void backward(int);
    void stop();
  private:
    Motor* m_rightMotor;
    Motor* m_leftMotor;
    int calculatePowerLevel(float targetSpeed, int powerLevel, float realSpeed, float timeDelta);
    int initialSpeed(float speed);
    bool collision();
    float m_leftMotor_average;
    float m_rightMotor_average;
    I2CEncoder* m_leftEncoder;
    I2CEncoder* m_rightEncoder;
    NewPing* m_ultraSonic;
};
#endif
