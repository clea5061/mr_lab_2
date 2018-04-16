/**
 * Author(s): Evan Cleary, Gabriel Bowerson, Nathan Sarrault
 * Date: 4/17/2018
 * Class: CE-442
 * Assignment: Lab 2
 *
 * Motor class implementation. Allows for the definition of a PWM controlled motor.
 * Supports power scaling and definable forward direction.
 *
 */
#ifndef MOTOR_CNTRL_H
#define MOTOR_CNTRL_H

/**
 * Class to control a PWM motor
 */
class Motor {
  public:
    Motor(char d_pin, char s_pin);
    Motor(char d_pin, char s_pin, char forward);
    Motor(char d_pin, char s_pin, char forward, float scaleFactor);
    void forward(char speed);
    void backward(char speed);
    void stop();
  private:
    char m_direction_pin;
    char m_drive_pin;
    char m_drive_speed;
    char m_forward;
    char m_direction;
    float m_scale_factor;
    void update_motor();
    void go(char);
};

#endif
