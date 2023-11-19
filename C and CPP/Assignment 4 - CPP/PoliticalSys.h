//
// Created by victor on 1/10/23.
//

#ifndef MY_FINAL_PROJ_POLITICALSYS_H
#define MY_FINAL_PROJ_POLITICALSYS_H

#include <iostream>
#include <fstream>
#include <cstdio>
#include "RepublicanParty.h"
#include "DemocraticParty.h"
#include "DemocraticPoliticianSocial.h"
#include "DemocraticPoliticianLeader.h"
#include "RepublicanPoliticianLeader.h"
#include "RepublicanPoliticianSocial.h"
#include "Exceptions.h"
#include "vector"
#include <utility>
#include <limits>
#include <sstream>
#include "string"
using namespace std;

/*
 Description : to avoid saving for each politician his political side &
 his role in the party, I created 2 vectors of pointers to each possible option of politician.
 also 2 vectors of pointers for each political side party (D/R).
 2 more vectors of pointers to hold all politicians and all parties for their priority enter to the
 system/party . last vector is temp vector to hold pointers to all parties and sort
 them every time there is any change in politician/party by first size, and then string
 to know in O(1) which party is the biggest.
 */
class PoliticalSys {
private:
    vector<Politician*> AllPoliticianList;
    vector<Party*> AllPartiesList;

    vector<Politician*> DemocraticPoliticianList;
    vector<Politician*> RepublicanPoliticianList;
    vector<Party*> DemocraticPartyList;
    vector<Party*> RepublicanPartyList;

    /// helper vector to tell in O(1) who's the biggest party:
    vector<Party*> AllPartiesFor_O1_check;

public:
    /// constructor :
    PoliticalSys() = default;
    explicit PoliticalSys(const string& file_stream);

    //// main interface methods :
    void addPolitician();
    void removePolitician();
    void addParty();
    void removeParty();
    void elections() const;
    void printPoliticians() const;
    void printParties() const;
    void BiggestParty() const;

    /// helper methods for Politician.cpp :
    bool CheckIfIdExsist(int _id) const;
    bool CheckIfPartyExsist(const string& _party_name) const;
    int getRepublicPartySize(const string& _party_name) const;
    int getDemocraticPartySize(const string& _party_name) const;
    void removePartyFromSideList(Party* p);
    char getPartySide(Party* p )const; /// without saving field !
    Party* getPoliticianPartyD(int _id) const;
    Party* getPoliticianPartyR(int _id) const;
    Party* getPartyByName(const string& _name) const;

    /// destructor :
    ~PoliticalSys();
};


#endif //MY_FINAL_PROJ_POLITICALSYS_H
