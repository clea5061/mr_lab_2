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
#include "motor.h"
#include "Arduino.h"

/**
 * Base Motor constructor that provides a active high forward and 1 scale factor
 * 
 * @param d_pin Which pin controls the direction of the motor
 * @param s_pin Which pin controlls the speed of the motor
 */
Motor::Motor(char d_pin, char s_pin): Motor(d_pin, s_pin, 1, 1){}

/**
 * Defines a motor with the given pins and forward direction with a 1 scale factor
 * 
 * @param d_pin Which pin controls the direction of the motor
 * @param s_pin Which pin controlls the speed of the motor
 * @param forward Which direction is forward, 1 or 0
 */
Motor::Motor(char d_pin, char s_pin, char forward): Motor(d_pin, s_pin, forward, 1) {}

/**
 * Defines a motor with the given pins, forward, and scale factor
 * 
 * @param d_pin Which pin controls the direction of the motor
 * @param s_pin Which pin controlls the speed of the motor
 * @param forward Which direction is forward, 1 or 0
 * @param scaleFactor the multiplier between between 0 and 1 that is applied to motor speed
 */
Motor::Motor(char d_pin, char s_pin, char forward, float scaleFactor) {
  m_direction_pin = d_pin;
  m_drive_pin = s_pin;
  m_drive_speed = 0;
  m_forward = forward;
  m_scale_factor = scaleFactor;
  pinMode(m_direction_pin, OUTPUT);
  pinMode(m_drive_pin, OUTPUT);
}

/**
 * Sets the motor to the drive direction and speed
 */
void Motor::update_motor(){
//  analogWrite(m_drive_pin, 0);
//  delay(25);
  digitalWrite(m_direction_pin, m_direction);
  analogWrite(m_drive_pin, m_drive_speed);
}

/**
 * Sets the motor to turn forward at the given speed.
 * 
 * @param speed Percent speed to run the motor at
 */
void Motor::forward(char speed) {
  m_direction = m_forward;
  go(speed);
}

/**
 * Sets the motor to turn backward at the given speed.
 * 
 * @param speed Percent speed to run the motor at
 */
void Motor::backward(char speed) {
  m_direction = !m_forward;
  go(speed);
}

/**
 * Sets the drive speed of the motor and sends values to motor
 * 
 * @param speed Percent speed to run the motor at
 */
void Motor::go(char speed) {
  m_drive_percent = speed;
  m_drive_speed = map(speed*m_scale_factor, 0, 100, 0, 255);
  update_motor();
}
/**
 * Returns the scaled drive speed of the motor
 */
int Motor::get_drive_speed() {
  return m_drive_speed;
}

/**
 * Returns the drive speed as a percentage.
 */
int Motor::get_drive_percent() {
  return m_drive_percent;
}

/**
 * Stops the motor
 */
void Motor::stop() {
  m_drive_speed = 0;
  update_motor();
}

