#ifndef _H_RB_V2_
#define _H_RB_V2_

#include "motor.h"
#include "light_sensor.h"
#include <Wire.h>
#include <I2CEncoder.h>
#include <NewPing.h>
#include "velocity_vector.h"

struct pid_vector {
    int right, left;
};

typedef struct pid_vector PidVector;

class Robot2 {
    public:
        Robot2(Motor* left, Motor* right);
        void enable_collision(NewPing* ultra);
        void enable_light_wall(LightSensor* light_sensor);
        void enable_vision(Vision* vision);
        void drive(float);
    private:
        float convert_to_power(float val);
        void update_drives();
        bool check_collisions();
        PidVector poll_motor_velocities();
        bool m_driving;
        Velocity mVelocity;
        Velocity mTargetVelocity;
        long mLastMotorPoll;
        Motor* mLeftMotor,* mRightMotor;
        NewPing* mUltraSonic;
        Vision* mVision;
        LightSensor* mLightSensor;
        unsigned long mCycle;
};
#endif
