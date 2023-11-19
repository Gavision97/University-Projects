//
// Created by victor on 1/7/23.
//

#include "DemocraticPoliticianSocial.h"

/// override print function for Democratic Politician that is social :
void DemocraticPoliticianSocial::printPolitician() const {
    // todo check for null
    cout << "Democratic Person:" << first_name << " " << last_name <<
         ", Id:" << id << ", Power:" << power << ", Type:S"
         << ", Chairman: " << chairman << endl;
}

/// social politician double his power during elections :
int DemocraticPoliticianSocial::getPowerForElections() const {
    return power*2;
}

bool DemocraticPoliticianSocial::TakePartInThePrimaries() const {return false;}
