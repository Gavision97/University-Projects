//
// Created by victor on 12/31/22.
//
#include "Map.h"
#include "Robot.h"
#include <cstring>
#include <iostream>
using namespace std;
#include <string>
#include <cstdio>
#include <cstdlib>
using namespace std;

////

/// define MACROS to eliminate rewrite code :

#define FINISH_SCRIPT finish_script(robot_arr)
#define PRINT_ROBOT cout << "Robot: " << curr_r->GetRobotID() << " MAP: " << curr_r ->GetRobotMap() << " GPS: " << curr_r ->GetRobotX() << "," << curr_r ->GetRobotY() << endl
#define PRINT_NEW_ROBOT cout << "New Robot: " << curr_r->GetRobotID() << " MAP: " << curr_r ->GetRobotMap() << " GPS: " << curr_r ->GetRobotX() << "," << curr_r ->GetRobotY() << endl
#define PRINT_DELETED_ROBOT cout << "Robot deleted: " << curr_r->GetRobotID() << " MAP: " << curr_r ->GetRobotMap() << " GPS: " << curr_r ->GetRobotX() << "," << curr_r ->GetRobotY() << endl
#define PRINT_ROBOT_WITHOUT_MAP_NUMBER cout << "Robot: " << robot_arr[k]->GetRobotID() << " GPS: " << robot_arr[k]->GetRobotX() << ',' << robot_arr[k]->GetRobotY() << endl

//// the next function helps to find out if specific Robot exist in the
//// dynamic allocated robot array by it's id : ( returns pointer to that given robot if exist )

Robot * FindRobot(Robot ** r, int id){
    for(int i = 0; i < Robot::get_num_robots(); i ++)
        if(r[i]->GetRobotID() == id)
            return r[i];
    return NULL; /// thus the robot now exist in the dynamic allocated robot's array
}

/// Case No.1 :

Robot ** AddRobot(Map& m1, Map& m2, Robot** r){
    int x ,y ,map_choise;
    cout << "Enter MAP number: " << endl;
    cin >> map_choise;
    if(map_choise != 1 && map_choise != 2) {
        cout << "Invalid MAP number " << endl;
        return r;
    }
    cout << "Enter Coordinates (X,Y): " << endl;
    cin >> x >> y;
    if(x > 7 || x < 0 || y > 7 || y < 0){
        x = -1;
        y = -1;
    }
    int fixed_x = 6-y; /// the map inserted like in the pdf picture, so make changes to know the exact (x,y)
    int fixed_y =  x;
    if(map_choise == 1)
        if(m1.GetMapsXY(fixed_x, fixed_y) == 1) { /// wall !
            cout << "Invalid location" << endl;
            return r;
        }
    if(map_choise == 2)
        if(m2.GetMapsXY(fixed_x, fixed_y) == 1) { /// wall !
        cout << "Invalid location" << endl;
        return r;
    }
    Robot::IncrementRobotNum(); /// number of robots ++ by using static function with static variable
    Robot::IncreaseRobotID(); /// robot's id ++ by using static function with static variable
    int id = Robot::GetNextRobotID(); /// Get next robot's ID by using static function with static variable
    Robot *curr_r = new Robot(id ,x, y, map_choise);
    int num_of_robots = Robot::get_num_robots();
    if(num_of_robots == 1){
        r = new Robot *[1];
        r[0] = curr_r;
        PRINT_NEW_ROBOT; /// uses macro
        return r;
    }
    Robot **temp = new Robot*[num_of_robots];
    for(int i = 0; i < num_of_robots -1; i++) {
        Robot* deep_copy_r = nullptr;
        deep_copy_r = new Robot(*r[i]); /// Preforming DeepCopy for new robot, so when we delete it, the copy will remain untouched.
        temp[i] = deep_copy_r;
    }
    temp[num_of_robots -1] = curr_r;
    for(int j = 0; j < num_of_robots -1; j++) { /// Deallocating the memory of r before assigning to new Robot's array
        delete r[j];
    }
    delete[] r;
    r = temp; /// Robots array after the changes
    PRINT_NEW_ROBOT; /// uses macro
    return r;
}
/// Case No.2 :

Robot ** DeleteRobot(Robot** r, int id, int flag){ /// flag makes sure to not print robots for case 5 & 6
    Robot* curr_r = nullptr;
    curr_r = FindRobot(r, id);
    if(! curr_r){
        cout << "Invalid Robot number" << endl; /// TODO CHECK IF NEED TO PRINT THAT
        return r;
    }
    if(flag == 0 ) PRINT_DELETED_ROBOT;
    int num_before_del = Robot::get_num_robots();
    if(id < 1 || num_before_del == 0) /// No such robot exist !
        return r;
    Robot::DecrementRobotNum(); ///  Preforming : num_of_robots -- by using static function with static variable
    if(num_before_del == 1){/// Only one element in Robot's array
        delete r[0];
        return r;
    }
    int indx = 0;
    int num_of_robots = Robot::get_num_robots();
    Robot ** temp = new Robot*[num_of_robots];
    for(int i = 0 ; i < num_of_robots +1 ; i++) {
        if (r[i]->GetRobotID() != id){
            Robot* deep_copy_r = new Robot(*r[i]); /// Preforming DeepCopy for new robot, so when we delete it, the copy will remain untouched.
            temp[indx] = deep_copy_r;
            indx ++;
        }
    }
    for(int j = 0; j < num_before_del ; j ++) { /// Deallocating the memory of r before assigning to new Robot's array
        delete r[j];
    }
    delete[] r;
    r = temp; /// Robot's array after the changes
    return r;
}
/// Case No.3 :

Robot ** MoveRobot(Map& m1, Map& m2, Robot** r) {
    char input[SIZE];
    int rob_num;
    cout << "Enter Robot number:" << endl;
    cin >> rob_num;
    int num_of_robots = Robot::get_num_robots();
    if (rob_num < 1 || num_of_robots == 0) /// In case there in so such robot
        return r;
    Robot *curr_r = FindRobot(r, rob_num);
    if(! curr_r){
        cout << "Invalid Robot number" << endl;
        return r;
    }
    cout << "Enter direction:" << endl;
    cin >> input;
    if (curr_r->GetRobotX() == -1 && curr_r->GetRobotY() == -1) /// In case the robot is out of the fame (-1,-1,)
        return r;
    char temp = input[0];
    switch (temp) {
        case 'L':
            if (curr_r->GetRobotX() == 0) {
                curr_r->SetXY(-1, -1);
                return r;
            }
            curr_r->SetXY(curr_r->GetRobotX() - 1, curr_r->GetRobotY());
            PRINT_ROBOT; /// uses macro
            return r;
        case 'R':
            if (curr_r->GetRobotX() == 6) {
                curr_r->SetXY(-1, -1);
                return r;
            }
            curr_r->SetXY(curr_r->GetRobotX() + 1, curr_r->GetRobotY());
            PRINT_ROBOT; /// uses macro
            return r;
        case 'U':
            if (curr_r->GetRobotY() == 6) {
                curr_r->SetXY(-1, -1);
                return r;
            }
            curr_r->SetXY(curr_r->GetRobotX(), curr_r->GetRobotY() + 1);
            PRINT_ROBOT; /// uses macro
            return r;
        case 'D':
            if (curr_r->GetRobotY() == 0) {
                curr_r->SetXY(-1, -1);
                return r;
            }
            curr_r->SetXY(curr_r->GetRobotX(), curr_r->GetRobotY() - 1);
            PRINT_ROBOT; /// uses macro
            return r;
        default:
            return r;
    }
}
/// Case No.4 :

Robot ** PreformeCase4(Map MAP1,Map MAP2,Robot** robot_arr) {
    Map temp_map = MAP1 + MAP2; /// uses operator overloading from class map
    cout << temp_map << endl; /// uses operator overloading from class map
    int num_of_robots = Robot::get_num_robots();
    if (num_of_robots == 0) return robot_arr; /// no robots to print
    for (int i = 0; i < 7; i++)
        for (int j = 0; j < 7; j++) {
            {
                int fixed_x = 6 - j; /// the map inserted like in the pdf picture, so make changes to know the exact (x,y)
                int fixed_y = i;
                if (temp_map.GetMapsXY(fixed_x, fixed_y) == 0) { /// fine route
                    for (int k = 0; k < num_of_robots; k++)
                        if (robot_arr[k]->GetRobotX() == i && robot_arr[k]->GetRobotY() == j) {
                            PRINT_ROBOT_WITHOUT_MAP_NUMBER; /// uses macro
                        }
                }
            }
        }
    return robot_arr;
}

//// the next function helps cases 5 & 6 to delete all of the robots the located on wall (x,y)
/// from the dynamic array of robots :

Robot ** DeleteRobotHelper(Robot** robot_arr, int x, int y, int m) {
    int n = Robot::get_num_robots(); /// total iterations
    for (int j = 0; j < n; j++) {
        if (robot_arr[j]->GetRobotX() == x && robot_arr[j]->GetRobotY() == y &&
            robot_arr[j]->GetRobotMap() == 1 && robot_arr[j]->GetRobotMap() == m) { /// the robot located on the wall, thus delete him
            robot_arr[j]->SetFlagToDelete(); /// set robot flag to 1, so later we will know to delete him
        }
    }
    int indx = 0; /// to make sure we dont over iterate while deleting robot from robots dynamic array
    while (indx < Robot::get_num_robots()) {
        if (robot_arr[indx]->GetRobotFlag() == 1) { /// the robot located on wall, thus delete
            robot_arr = DeleteRobot(robot_arr, robot_arr[indx]->GetRobotID(),1);
            continue;
        }
        indx++;
    }
    return robot_arr;
}
/// Case No.5 :

Robot ** PreformeCase5(Map MAP1,Map MAP2,Robot** robot_arr, int map_choise) {
    int flag = 0; /// the flag is not know what map to work on
    if(map_choise == 1) flag = 1;
    else flag = 2 ;
    if(flag == 1) {
        for (int i = 0; i < 7; i++)
            for (int j = 0; j < 7; j++) {
                int fixed_x = 6 - j;
                int fixed_y = i;
                if (MAP1.GetMapsXY(fixed_x, fixed_y) == 1)
                    robot_arr = DeleteRobotHelper(robot_arr, i, j, 1);
            }
    }
    else { /// flag == 2
        for (int i = 0; i < 7; i++)
            for (int j = 0; j < 7; j++) {
                int fixed_x = 6 - j;
                int fixed_y = i;
                if (MAP2.GetMapsXY(fixed_x, fixed_y) == 1)
                    robot_arr = DeleteRobotHelper(robot_arr, i, j, 2);
                }
    }
    return robot_arr;
}

/// Case No.6 :

Robot ** PreformeCase6(Map MAP1, Map MAP2, Robot** robot_arr, int map_choise){
    int flag = 0; /// the flag is not know what map to work on
    if(map_choise == 1) flag = 1;
    else flag = 2;
    if(flag == 1) {
        for (int i = 0; i < 7; i++)
            for (int j = 0; j < 7; j++) {
                int fixed_x = 6 - j;
                int fixedy_y = i;
                if (MAP1.GetMapsXY(fixed_x, fixedy_y) == 1)
                    robot_arr = DeleteRobotHelper(robot_arr, i, j, 1);
            }
    }
    else { /// flag == 2
        for (int i = 0; i < 7; i++)
            for (int j = 0; j < 7; j++) {
                int fixed_x = 6 - j;
                int fixed_y = i;
                if (MAP2.GetMapsXY(fixed_x, fixed_y) == 1)
                    robot_arr = DeleteRobotHelper(robot_arr, i, j, 2);
            }
    }
    return robot_arr;
}
/// Case No.8 :

status PreformeCase8(Map MAP1, Map MAP2, Robot** robot_arr){
    int m; /// map number
    cout << "Please enter MAP number:" << endl;
    cin >> m;
    if(m != 1 && m != 2){ /// no such map exist
        cout << "Invalid MAP number" << endl;
        return success;
    }
    int num_of_robots = Robot::get_num_robots(); /// uses static function with static variable
    if(m == 1){
        cout << MAP1 << endl; /// uses operator overloading from class map
        if(num_of_robots == 0) return success;
        for(int i = 0; i < num_of_robots; i++){
            if(robot_arr[i]->GetRobotMap() == 1 && robot_arr[i]->GetRobotX() != -1 && robot_arr[i]->GetRobotY() != -1)
                cout << "Robot: " << robot_arr[i]->GetRobotID() << " Map: "<< m <<" GPS: "<< robot_arr[i]->GetRobotX() << "," << robot_arr[i]->GetRobotY() << endl;
        }
    }
    else {
        cout << MAP2 << endl; /// uses operator overloading from class map
        if(num_of_robots == 0) return success;
        for(int i = 0; i < num_of_robots; i++){
            if(robot_arr[i]->GetRobotMap() == 2 && robot_arr[i]->GetRobotX() != -1 && robot_arr[i]->GetRobotY() != -1)
                cout << "Robot: " << robot_arr[i]->GetRobotID() << " Map: "<< m <<" GPS: "<< robot_arr[i]->GetRobotX() << "," << robot_arr[i]->GetRobotY() << endl;
        }
    }
    return success; /// in case there was problem with executing the function
}

/// the next function called when we want to exit and finish the script
/// the function makes sure do free all of the allocated memory before exiting  :

void finish_script(Robot ** robot_arr){
    int num_of_robots = Robot::get_num_robots();
    if(num_of_robots == 0){ /// in case there is no robots in the robot dynamic array
        delete[] robot_arr;
        exit(1);
    }
    for(int i = 0; i < num_of_robots; i++){
        delete robot_arr[i];
    }
    delete[] robot_arr;
    exit(1);
}

//// main interface :

int main(int argc, char* argv[]) {
    /// declaration of the maps :
    Map MAP1;
    Map MAP2;
    /// initialization of the maps :
    MAP1.SetFirst();
    MAP2.SetSecond();
    /// declaration of the dynamic array of robot for the game:
    Robot **robot_arr = nullptr;

   char input[10];
    while(true) {
        char temp;
        cout << "Robot Control Menu " << endl;
        cout << "1. Add Robot " << endl;
        cout << "2. Delete Robot " << endl;
        cout << "3. Move Robot " << endl;
        cout << "4. Operator + " << endl;
        cout << "5. Operator += " << endl;
        cout << "6. Operator = " << endl;
        cout << "7. Operator == " << endl;
        cout << "8. Operator << " << endl;
        cout << "9. Quit " << endl;
        cout << "Input your option: " << endl;
        scanf(" %s", input);
        temp = input[0];
        if (std::strlen(input) != 1)
            temp = 'a';

        switch (temp) {
            case '1':
                robot_arr = AddRobot(MAP1, MAP2, robot_arr);
                break;
            case '2':
                int robot_num;
                cout << "Enter Robot number:" << endl;
                cin >> robot_num;
                robot_arr = DeleteRobot(robot_arr, robot_num, 0);
                break;
            case '3':
                robot_arr = MoveRobot(MAP1, MAP2, robot_arr);
                break;
            case '4':
                robot_arr = PreformeCase4(MAP1, MAP2, robot_arr);
                break;
            case '5':
                int m5;
                cout << "Override MAP number:" << endl;
                cin >> m5;
                if(m5 != 1 && m5 != 2){
                    cout << "Invalid MAP number" << endl;
                    break;
                }
                if(m5 == 1) MAP1 += MAP2; /// uses operator overloading from class map
                else MAP2 += MAP1;
                robot_arr = PreformeCase5(MAP1, MAP2, robot_arr, m5);
                break;
            case '6':
                int m6;
                cout << "Override MAP number:" << endl;
                cin >> m6;
                if(m6 != 1 && m6 != 2){
                    cout << "Invalid MAP number" << endl;
                    break;
                }
                if(m6 == 1) MAP1 = MAP2; /// uses operator overloading from class map
                else MAP2 = MAP1;
                robot_arr = PreformeCase6(MAP1, MAP2, robot_arr, m6);
                break;
            case '7':
                if(MAP1 == MAP2) /// uses operator overloading from class map
                    cout << "TRUE" << endl;
                else
                    cout << "FALSE" << endl;
                break;
            case '8':
                if(PreformeCase8(MAP1, MAP2, robot_arr) == failure) FINISH_SCRIPT; /// uses macro to finish the script
                break;
            case '9':
                FINISH_SCRIPT; /// uses macro to finish the script
            default:
                cout << "Invalid input" << endl;
                break;
        }
    }
}