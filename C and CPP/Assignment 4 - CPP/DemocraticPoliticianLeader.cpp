//
// Created by victor on 1/7/23.
//

#include "DemocraticPoliticianLeader.h"

/// override print function for Democratic Politician that is leader :
void DemocraticPoliticianLeader::printPolitician() const {
    // todo check for null
    cout << "Democratic Person:" << first_name << " " << last_name <<
         ", Id:" << id << ", Power:" << power << ", Type:L"
         << ", Chairman: " << chairman << endl;
}

int DemocraticPoliticianLeader::getPowerForElections() const {
    return power;
}

bool DemocraticPoliticianLeader::TakePartInThePrimaries() const { return true;}