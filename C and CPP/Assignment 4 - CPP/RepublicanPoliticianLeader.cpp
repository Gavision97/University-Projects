//
// Created by victor on 1/7/23.
//

#include "RepublicanPoliticianLeader.h"

/// override print function for Republican Politician that is leader :
void RepublicanPoliticianLeader::printPolitician() const {

    cout << "Republican Person:" << first_name << " " << last_name <<
         ", Id:" << id << ", Power:" << power << ", Type:L"
         << ", Chairman: " << chairman << endl;
}

int RepublicanPoliticianLeader::getPowerForElections() const {
    return power;
}

bool RepublicanPoliticianLeader::TakePartInThePrimaries() const {return true;}