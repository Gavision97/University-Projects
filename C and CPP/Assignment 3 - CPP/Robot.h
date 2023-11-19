//
// Created by victor on 12/30/22.
//

#ifndef UNTITLED1_ROBOT_H
#define UNTITLED1_ROBOT_H
#include <iostream>
using namespace std;

/// define macro for later function returned status :
typedef enum e_status {success =1 , failure = -1} status;

class Robot
{
private:
    int x, y, map, robot_id;
    static int num_robots, next_robot_id;
    int flag;

public:
    ///Constructors :
    Robot();
    Robot(int x, int y, int map, int flag) ;
    Robot(const Robot &r);
    /// destructor:
    ~Robot();
    /// declaration of Robot's functions :
    void SetXY(int _x, int _y);
    void SetMap(int _map);
    void SetRobotID(int _id);
    int GetRobotID() const;
    int GetRobotX()const;
    int GetRobotY()const;
    int GetRobotMap() const;
    static void IncreaseRobotID();
    static void DecrementRobotNum();
    static void IncrementRobotNum();
    void SetRobotFlag(int f);
    void SetFlagToDelete();
    int GetRobotFlag() const;
    static int get_num_robots();
    static int GetNextRobotID();
};

#endif //UNTITLED1_ROBOT_H
