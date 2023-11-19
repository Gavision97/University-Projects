//
// Created by victor on 1/10/23.
//

#ifndef MY_FINAL_PROJ_EXCEPTIONS_H
#define MY_FINAL_PROJ_EXCEPTIONS_H

#include <iostream>
#include <exception>

using namespace std;

class InvalidIdException : public exception {
public:
    virtual const char* what() const throw(){
        return "Please enter valid id";
    }
};

class InvalidNameException : public exception {
public:
    virtual const char* what() const throw(){
        return "Please enter valid name";
    }
};

class InvalidValueException : public exception {
public:
    virtual const char* what() const throw(){
        return "Please enter valid details";
    }
};
#endif //MY_FINAL_PROJ_EXCEPTIONS_H
