//
// Created by victor on 12/30/22.
//
#include "Robot.h"
using namespace std;

/// initializing two static values :
int Robot::num_robots = 0;
int Robot::next_robot_id = 0;


Robot::~Robot() {}

/// implement constructors :
Robot::Robot() {}

Robot::Robot(const Robot& r) { /// deep copy constructor
    SetMap(r.GetRobotMap());
    SetXY(r.GetRobotX(), r.GetRobotY());
    SetRobotID(r.GetRobotID());
    SetRobotFlag(r.GetRobotFlag());
}

Robot::Robot(int id, int x, int y, int map) { //// constructor for case 1 when we add new robot with given values
    this ->robot_id = id;
    this -> x = x;
    this ->y = y;
    this ->map = map;
    this ->flag = 0; /// for case No5
}
//// finished

/// implementation of Robot's function :

void Robot::DecrementRobotNum() {
    --num_robots;
}
void Robot::IncrementRobotNum() {
    ++num_robots;
}
void Robot::IncreaseRobotID() {
    ++next_robot_id;
}
int Robot::GetNextRobotID(){ /// return the next robot id by static value
    return next_robot_id;
}

int Robot::get_num_robots() {
    return num_robots;
}

int Robot::GetRobotX() const {
    return this ->x;
}

int Robot::GetRobotY() const {
    return this ->y;
}

int Robot::GetRobotID() const {
    return this ->robot_id;
}

int Robot::GetRobotMap() const {
    return this ->map;
}

void Robot::SetXY(int _x, int _y) {
    this ->x = _x;
    this ->y = _y;
}

void Robot::SetMap(int _map) {
    this ->map = _map;
}

void Robot::SetRobotID(int _id) {
    this ->robot_id = _id;
}

void Robot::SetFlagToDelete() { /// sets robots flag to 1 , now we know to delete him on cases 5 & 6
    this ->flag = 1;
}
 int Robot::GetRobotFlag() const { /// for cases 5 &6 to know if to delete robot that located on wall (x,y)
     return this ->flag;
}

void Robot::SetRobotFlag(int f) {
    this -> flag = f;
}