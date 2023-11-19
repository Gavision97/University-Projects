//
// Created by victor on 1/7/23.
//

#ifndef PROJECT_5_DEMOCRATICPARTY_H
#define PROJECT_5_DEMOCRATICPARTY_H

#include "Party.h"

class DemocraticParty : public Party {

public:
    /// constructor :
    explicit DemocraticParty(string _party_name) : Party(_party_name) {}

    /// override pure virtual methods :

    void PrintPartyInfo() override;
    ~DemocraticParty() { }
};
#endif //PROJECT_5_DEMOCRATICPARTY_H
