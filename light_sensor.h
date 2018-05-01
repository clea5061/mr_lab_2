/**
 * Author(s): Evan Cleary, Gabriel Bowerson, Nathan Sarrault
 * Date: 4/30/2018]
 * Class: CE-442
 * Assignment: Lab 4
 *
 * Light sensor class structure
 */
#ifndef _LIGHT_SENSOR_H
#define _LIGHT_SENSOR_H

#define BLACK_THRESHOLD 15

struct lsVector {
  int left;
  int right;
  int center;
};

struct lsCollision {
  char left;
  char right;
  char center;
};

typedef struct lsCollision LightCollision;
typedef struct lsVector LightVector;

class LightSensor {
  public:
    LightSensor(char left, char center, char right);
    void poll();
    void calibrate();
    LightCollision* check_collisions();
  private:
    char threshold_check(int value, int cal);
    char m_left_pin, m_right_pin, m_center_pin;
    LightVector m_value;
    LightVector m_black_cal;
    LightCollision m_collision_vector;
};

#endif
