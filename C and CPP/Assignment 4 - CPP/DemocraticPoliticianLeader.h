//
// Created by victor on 1/7/23.
//

#ifndef PROJECT_5_DEMOCRATICPOLITICIANLEADER_H
#define PROJECT_5_DEMOCRATICPOLITICIANLEADER_H

#include "Politician.h"
#include <iostream>
using namespace std;

/// DemocraticPoliticianLeader inherit from Politician
class DemocraticPoliticianLeader : public Politician {

public:
    DemocraticPoliticianLeader(string _first_name, string _last_name, int _id, int _power):
            Politician(_first_name, _last_name, _id, _power) {}

    /// override abstract class methods :
    void printPolitician() const override;
    int getPowerForElections() const override;
    bool TakePartInThePrimaries() const override;

    /// destructor:
    ~DemocraticPoliticianLeader() { }
};

#endif //PROJECT_5_DEMOCRATICPOLITICIANLEADER_H
