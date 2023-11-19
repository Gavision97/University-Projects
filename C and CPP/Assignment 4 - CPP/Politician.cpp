//
// Created by victor on 1/7/23.
//
#include <string>
#include <cstdio>
using namespace std;
#include "Politician.h"

/// implementing Politician methods :
void Politician::notifyPolitician(string _chairman){
    this ->chairman = _chairman;
}

/// compare two politicians by their power :
Politician& Politician::operator=(const Politician &other) {
    if(*this == other)
        return *this;
    this ->first_name = other.first_name;
    this ->last_name = other.last_name;
    this ->chairman = other.chairman;
    this ->id = other.id;
    this ->power = other.power;

    return *this;
}

bool Politician::operator<(const Politician &other) const {
    return this ->power > other.power;
}

bool Politician::operator==(const Politician &other) const {
    return this ->id == other.id;
}