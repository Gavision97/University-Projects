//
// Created by victor on 1/7/23.
//

#ifndef PROJECT_5_REPUBLICANPARTY_H
#define PROJECT_5_REPUBLICANPARTY_H

#include "Party.h"

class RepublicanParty : public Party {
public:
    /// constructor :
    explicit RepublicanParty(string _party_name) : Party(_party_name) {}

    /// override pure virtual methods :
   // bool AddPolitician(Politician *p, char politic_side) override;
    /*
    bool AddPoliticianDemocratic(Politician *p) override;
    bool AddPoliticianRepublican(Politician *p) override;
     */
    void PrintPartyInfo() override;

    ~RepublicanParty() { }

};
#endif //PROJECT_5_REPUBLICANPARTY_H
