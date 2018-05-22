/**
 * Author(s): Evan Cleary, Gabriel Bowerson, Nathan Sarrault
 * Date: 4/17/2018
 * Amended: 4/23/2018
 * Class: CE-442
 * Assignment: Lab 2
 *
 * Motor class implementation. Allows for the definition of a PWM controlled motor.
 * Supports power scaling and definable forward direction.
 *
 */
#ifndef MOTOR_CNTRL_H
#define MOTOR_CNTRL_H
#include <I2CEncoder.h>

/**
 * Class to control a PWM motor
 */
class Motor {
  public:
    Motor(char d_pin, char s_pin, I2CEncoder* encoder);
    Motor(char d_pin, char s_pin, I2CEncoder* encoder, char forward);
    Motor(char d_pin, char s_pin, I2CEncoder* encoder, char forward, float scaleFactor);
    void drive(char speed);
    void stop();
    void forward(char speed);
    void backward(char speed);
    int get_drive_speed();
    int get_drive_percent();
    int get_actual_speed();
  private:
    char m_direction_pin;
    char m_drive_pin;
    char m_drive_speed;
    char m_drive_percent;
    char m_forward;
    char m_direction;
    I2CEncoder* m_encoder;
    float m_scale_factor;
    void update_motor();
    void go(char);
};

#endif
