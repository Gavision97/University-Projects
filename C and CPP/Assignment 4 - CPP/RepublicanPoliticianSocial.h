//
// Created by victor on 1/7/23.
//

#ifndef PROJECT_5_REPUBLICANPOLITICIANSOCIAL_H
#define PROJECT_5_REPUBLICANPOLITICIANSOCIAL_H

#include "Politician.h"
#include <iostream>
using namespace std;

/// RepublicanPoliticianSocial class inherit from Politician
class RepublicanPoliticianSocial : public Politician {
public:
    RepublicanPoliticianSocial(string _first_name, string _last_name, int _id, int _power):
            Politician(_first_name, _last_name, _id, _power) {}
    /// override abstract class methods :

    void printPolitician() const  override;
    int getPowerForElections() const override;
    bool TakePartInThePrimaries() const override;

    /// destructor :

    ~RepublicanPoliticianSocial() { }
};
#endif //PROJECT_5_REPUBLICANPOLITICIANSOCIAL_H
