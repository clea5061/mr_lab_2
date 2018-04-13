#ifndef MOTOR_CNTRL_H

#define MOTOR_CNTRL_H

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
