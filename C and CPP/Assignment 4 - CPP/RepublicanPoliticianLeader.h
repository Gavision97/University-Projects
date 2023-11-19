//
// Created by victor on 1/7/23.
//

#ifndef PROJECT_5_REPUBLICANPOLITICIANLEADER_H
#define PROJECT_5_REPUBLICANPOLITICIANLEADER_H

#include "Politician.h"
#include <iostream>
using namespace std;

/// RepublicanPoliticianLeader class inherit from Politician
class RepublicanPoliticianLeader : public Politician {
public:
    RepublicanPoliticianLeader(string _first_name, string _last_name, int _id, int _power):
            Politician(_first_name, _last_name, _id, _power) {}
    /// overrode abstract class methods :
    void printPolitician() const override;
    int getPowerForElections() const override;
    bool TakePartInThePrimaries() const override;

    /// destructor :
    ~RepublicanPoliticianLeader() { }
};

#endif //PROJECT_5_REPUBLICANPOLITICIANLEADER_H
