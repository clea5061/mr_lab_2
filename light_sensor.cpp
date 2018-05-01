/**
 * Author(s): Evan Cleary, Gabriel Bowerson, Nathan Sarrault
 * Date: 4/30/2018
 * Class: CE-442
 * Assignment: Lab 4
 *
 * Light sensor that determines if the sensor is colliding with a calibrated black
 */
#include "light_sensor.h"
#include <Arduino.h>

LightSensor::LightSensor(char left, char center, char right) {
  m_left_pin = left;
  m_center_pin = center;
  m_right_pin = right;
}

/**
 * Retrieves the current values of the light sensor
 */
void LightSensor::poll(){
  m_value.left = analogRead(m_left_pin);
  m_value.center = analogRead(m_center_pin);
  m_value.right = analogRead(m_right_pin);
}

/**
 * Polls the values of the light sensor and checks if any of them collide with
 * the calibrated black
 * @return LightCollision structure Value will be 1 if sensor is colliding
 */
LightCollision* LightSensor::check_collisions(){
  poll();
  m_collision_vector.left = threshold_check(m_value.left, m_black_cal.left);
  m_collision_vector.center = threshold_check(m_value.center, m_black_cal.center);
  m_collision_vector.right = threshold_check(m_value.right, m_black_cal.right);
  return &m_collision_vector;
}

/**
 * Compares the given value with the calibrated value against the black threshold
 */
char LightSensor::threshold_check(int value, int cal_value) {
  return (value - cal_value < BLACK_THRESHOLD && value - cal_value > -BLACK_THRESHOLD) ? 1 : 0;
}

/**
 * Executes the calibration procedure. This runs for 500ms taking 10 measurements to
 * obtain an average value for black. This is then stored for the time the sensor object
 * is maintained.
 */
void LightSensor::calibrate() {
  unsigned long start = millis();
  int poll_count = 0;
  while(millis() - start < 500) {
    poll_count++;
    poll();
    m_black_cal.left += m_value.left;
    m_black_cal.center += m_value.center;
    m_black_cal.right += m_value.right;
    delay(50);
  }
  m_black_cal.left /= poll_count;
  m_black_cal.center /= poll_count;
  m_black_cal.right /= poll_count;
}

