//
// Created by victor on 1/7/23.
//
#include "RepublicanPoliticianSocial.h"

/// override print function for Republican Politician that is social :
void RepublicanPoliticianSocial::printPolitician() const {
    // todo check for null
    cout << "Republican Person:" << first_name << " " << last_name <<
         ", Id:" << id << ", Power:" << power << ", Type:S"
         << ", Chairman: " << chairman << endl;
}

/// social politician double his power during elections :
int RepublicanPoliticianSocial::getPowerForElections() const {
    return power*2 ;
}

bool RepublicanPoliticianSocial::TakePartInThePrimaries() const {return false;}