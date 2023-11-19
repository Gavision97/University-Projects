//
// Created by victor on 1/7/23.
//

#ifndef PROJECT_5_DEMOCRATICPOLITICIANSOCIAL_H
#define PROJECT_5_DEMOCRATICPOLITICIANSOCIAL_H

#include "Politician.h"
#include <iostream>
using namespace std;
/// DemocraticPoliticianSocial inherit from Politician
class DemocraticPoliticianSocial : public Politician {

public:
    DemocraticPoliticianSocial(string _first_name, string _last_name, int _id, int _power):
    Politician(_first_name, _last_name, _id, _power) {}

    /// override abstract methods:
    void printPolitician() const override;
    int getPowerForElections() const override;
    bool TakePartInThePrimaries() const override;

    /// destructor :
    ~DemocraticPoliticianSocial() { }
};

#endif //PROJECT_5_DEMOCRATICPOLITICIANSOCIAL_H
