/**
 * Author(s): Evan Cleary, Gabriel Bowerson, Nathan Sarrault
 * Date: 6/7/2018
 * Class: CE-442
 * Assignment: Lab 5
 *
 * Rebuild of the robot class class with more fine grained drive control
 * and modular piece. Also adds serial communication to the robot
 */
#include "robotv2.h"

#define PID_P 5
#define ROBO_DIM_L 23

Robot2::Robot2(Motor* leftMotor, Motor* rightMotor): m_driving(true){
    mLeftMotor = leftMotor;
    mRightMotor = rightMotor;
}

void Robot2::enable_collision(NewPing* ultra) {
    mUltraSonic = ultra;
}
void Robot2::enable_light_wall(LightSensor* light_sensor) {
    mLightSensor = light_sensor;
}

void Robot2::enable_vision(Vision* vision) {
    mVision = vision;
}

PidVector Robot2::poll_motor_velocities(){
    PidVector vector;
    if (mLastMotorPoll == 0){
        mLastMotorPoll = millis();
        return vector;
    }
    
    vector.left = mLeftMotor->get_actual_speed();
    vector.right = mRightMotor->get_actual_speed();
    mLastMotorPoll = millis();
    return vector;
}

float Robot2::convert_to_power(float val) {
    return 3.25f * val + 5.4;
}

void Robot2::update_drives() {
    PidVector motor_states = poll_motor_velocities();
    float error = 0.0f;
    if(mTargetVelocity.vl == 0.0f && mTargetVelocity.vr == 0.0f){
        mRightMotor->stop();
        mLeftMotor->stop();
    } else {
        if(mTargetVelocity.vl == mTargetVelocity.vr) {
            error=(motor_states.left-motor_states.right)/PID_P;
        }
        mRightMotor->drive(convert_to_power(mTargetVelocity.vr+error));
        mLeftMotor->drive(convert_to_power(mTargetVelocity.vl));
    }
}

bool Robot2::check_collisions() {
  int distance = mUltraSonic->ping_cm();
  if(distance== 0) return false;
  return distance < 20;
}

void Robot2::drive(float speed) {
    mTargetVelocity.y = speed;
    while(m_driving) {
        if (mUltraSonic && check_collisions()) {
            mTargetVelocity.x=0;
            mTargetVelocity.y=0;
            mTargetVelocity.omega=0;
            update_drives();
        } else {
            if (mCycle % 50 == 0) {
                read_velocity(&mTargetVelocity);
            }
            if(mCycle % 3 == 0) {
                update_drives();
            }
        }
        mCycle++;
    }
}
