//
// Created by victor on 12/30/22.
//

#ifndef UNTITLED1_MAP_H
#define UNTITLED1_MAP_H
#include <cstdio>
#include <iostream>
#include <string>
#define SIZE 300
using namespace std;

class Map{
private:
   int map[7][7];

public:
    /// constructor :

    Map();

    /// two initialize function for the game:

    void SetFirst();
    void SetSecond();

    /// overloading operators :

    Map operator+(const Map &other);
    const Map & operator+=(const Map& other);
    Map& operator=(const Map& other);
    bool operator==(const Map& other);
    friend ostream& operator<<(ostream& out, const Map& m);
    int GetMapsXY(int x, int y);

    /// destructor :

    ~Map();
};
#endif //UNTITLED1_MAP_H
