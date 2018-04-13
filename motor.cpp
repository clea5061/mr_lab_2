#include "motor.h"
#include "arduino.h"

Motor::Motor(char d_pin, char s_pin): Motor(d_pin, s_pin, 1, 1){}

Motor::Motor(char d_pin, char s_pin, char forward): Motor(d_pin, s_pin, forward, 1) {}

Motor::Motor(char d_pin, char s_pin, char forward, float scaleFactor) {
  m_direction_pin = d_pin;
  m_drive_pin = s_pin;
  m_drive_speed = 0;
  m_forward = forward;
  m_scale_factor = scaleFactor;
  pinMode(m_direction_pin, OUTPUT);
  pinMode(m_drive_pin, OUTPUT);
}

void Motor::update_motor(){
  analogWrite(m_drive_pin, 0);
  delay(25);
  digitalWrite(m_direction_pin, m_direction);
  analogWrite(m_drive_pin, m_drive_speed);
}

void Motor::forward(char speed) {
  m_direction = m_forward;
  go(speed);
}

void Motor::backward(char speed) {
  m_direction = !m_forward;
  go(speed);
}

void Motor::go(char speed) {
  m_drive_speed = map(speed*m_scale_factor, 0, 100, 0, 255);
  update_motor();
}

void Motor::stop() {
  m_drive_speed = 0;
  update_motor();
}

