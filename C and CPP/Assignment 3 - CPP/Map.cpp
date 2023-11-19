//
// Created by victor on 12/30/22.
//
#include "Map.h"
#include <iostream>
#include <string>
using namespace std;

Map::Map(){};

Map::~Map(){};

//// the next function sets the first game map :

void Map::SetFirst() {
    int first[7][7] = {{1,0,0,1,1,0,1},
                       {1,1,0,0,0,0,1},
                       {0,1,0,1,1,1,0},
                       {0,0,0,1,1,1,0,},
                       {1,0,1,1,0,1,0},
                       {1,0,1,0,0,1,0},
                       {1,0,0,0,0,0,0}};
    for(int i = 0 ; i < 7 ; i ++)
        for(int j = 0 ; j < 7 ; j ++)
            this ->map[i][j] = first[i][j];
}

/// the next function sets the second game map:

void Map::SetSecond() {
    int second[7][7] = {{1,1,0,0,0,1,1},
                        {1,1,0,1,1,1,1},
                        {1,1,0,0,0,1,1},
                        {0,1,1,1,0,1,1},
                        {0,0,0,0,0,1,1},
                        {1,1,0,1,1,1,0},
                        {1,0,1,0,0,0,0}};
    for(int i = 0 ; i < 7 ; i ++)
        for(int j = 0 ; j < 7 ; j ++)
            this ->map[i][j] = second[i][j];
}

/// the next function return the value ( 0 or 1 ) of maps (X,Y) coordination :

int Map::GetMapsXY(int x, int y) { return map[x][y];}

/// implementing operator overloading : + , += , = , == , <<

Map Map::operator+(const Map &other) {
    Map res;
    for (int i = 0; i < 7; i++) {
        for (int j = 0; j < 7; j++) {
            if (this->map[i][j] == 0 && other.map[i][j] == 0)
                res.map[i][j] = 0;
            else if (this->map[i][j] == 1 && other.map[i][j] == 0)
                res.map[i][j] = 1;
            else if (this->map[i][j] == 0 && other.map[i][j] == 1)
                res.map[i][j] = 1;
            else if (this->map[i][j] == 1 && other.map[i][j] == 1)
                res.map[i][j] = 1;
        }
    }
    return res;
}

const Map& Map ::operator+=(const Map &other) {
    for(int i = 0; i < 7; i++){
        for(int j = 0 ; j < 7 ; j ++){
            if (this->map[i][j] == 0 && other.map[i][j] == 0)
                this ->map[i][j] = 0;
            else if (this->map[i][j] == 1 && other.map[i][j] == 0)
                this ->map[i][j] = 1;
            else if (this->map[i][j] == 0 && other.map[i][j] == 1)
                this ->map[i][j] = 1;
            else if (this->map[i][j] == 1 && other.map[i][j] == 1)
                this ->map[i][j] = 1;
        }
    }
    return *this;
}

Map& Map::operator=(const Map& other){
    /// check for self-assigment by comparing the
    /// address of the implicit object and the parameter
    if(this == &other)
        return *this;

    for(int i = 0 ; i < 7 ; i ++)
        for(int j = 0 ; j < 7 ; j ++)
            this ->map[i][j] = other.map[i][j];
    return *this;
}

bool Map::operator==(const Map& other){
    for(int i = 0 ; i < 7 ; i ++)
        for(int j = 0 ; j < 7 ; j ++)
            if(this ->map[i][j] != other.map[i][j])
                return false;
    return true;
}

ostream& operator<<(ostream& out, const Map& m){
    for(int i = 0 ; i < 7 ; i ++) {
        cout<< "[";
        for (int j = 0; j < 6; j++) {
            out << m.map[i][j] << " ";
        }
        out << m.map[i][6] <<"]"<< endl;
    }
    return out;
}




