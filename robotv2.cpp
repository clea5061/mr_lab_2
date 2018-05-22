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
    if (mLastMotorPoll == 0)
        return vector;
    
    vector.left = mLeftMotor->get_actual_speed();
    vector.right = mRightMotor->get_actual_speed();
    mLastMotorPoll = millis();
    return vector;
}

float Robot2::convert_to_power(float val) {
    return 3.25f * val + 5.4;
}

void Robot2::update_drives() {
    Serial.print("Target Velocity: ");
    Serial.print("Y: ");
    Serial.print(mTargetVelocity.y);
    Serial.print("OMG: ");
    Serial.println(mTargetVelocity.omega);
    PidVector motor_states = poll_motor_velocities();
    float error = (motor_states.left-motor_states.right)/PID_P;
    float lSpeed = convert_to_power(mTargetVelocity.y);
    if(mTargetVelocity.omega > 0) {
        mRightMotor->drive(convert_to_power(mTargetVelocity.y-mTargetVelocity.omega));
        mLeftMotor->drive(lSpeed);
    } else if(mTargetVelocity.omega < 0) {
        mLeftMotor->drive(convert_to_power(mTargetVelocity.y+mTargetVelocity.omega));
        //Serial.println(convert_to_power(mTargetVelocity.y+mTargetVelocity.omega));
        mRightMotor->drive(lSpeed);
    } else {
        mLeftMotor->drive(lSpeed);
        mRightMotor->drive(lSpeed+error);
    }
}

bool Robot2::check_collisions() {
  int distance = mUltraSonic->ping_cm();
  if(distance== 0) return false;
  return distance < 18;
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
            if (mLightSensor) {
            }
            if (mVision) {
                offset_to_vel(mVision->get_object_offset(), &mTargetVelocity);
                // VisionOffset offset;
                // offset.x = -1;
                // offset.z = 0;
                // offset_to_vel(&offset, &mTargetVelocity);
            }
            if(mCycle % 3 == 0) {
                //update_drives();
            }
        }
        mCycle++;
    }
}
