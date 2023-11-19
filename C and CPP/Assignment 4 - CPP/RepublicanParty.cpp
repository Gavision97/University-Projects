//
// Created by victor on 1/7/23.
//
#include "RepublicanParty.h"

void RepublicanParty::PrintPartyInfo() {
    cout << "Republican Party: " << party_name << ", chairman:" << party_chairman << ", Size:" << ListOfPoliticians.size() << endl;
    if(ListOfPoliticians.empty())
        return;
    for(auto iter : ListOfPoliticians) {
        cout << '\t';
        (*iter).printPolitician();
    }
}