//
// Created by victor on 1/8/23.
//

#include "Party.h"


void Party::Primemeries() {
    string chosen_chairman;
    int max_power = -1;
    for(auto iter : ListOfPoliticians){
        if((*iter).TakePartInThePrimaries()) {
            if(max_power < (*iter).getPower())
                max_power = (*iter).getPower();
        }
    }
    /// find the first leader in the party that has the max power
    for(auto iter : ListOfPoliticians)
        if((*iter).TakePartInThePrimaries() && (*iter).getPower() == max_power){
            chosen_chairman = (*iter).getName();
            party_chairman = chosen_chairman;
            notify(chosen_chairman); /// notify all of the politician with their chairman
            chairman_id = iter->getID();
            cout << chosen_chairman << " is the chairman of " << party_name << endl;
            return;
        }
    cout << party_chairman << " is the chairman of " << party_name << endl;
}

/// the next method notifies all the observers (politician in the current party)
/// who's their new chosen chairman after primaries
void Party::notify(std::string _chairman) {
    if(_chairman == "None"){
        chairman_id = 0;
        party_chairman = "None";
    }
    else
        party_chairman = _chairman;
    if(ListOfPoliticians.empty())
        return;
    for(auto iter : ListOfPoliticians)
        (*iter).notifyPolitician(_chairman);
}

/// the next method calculates party total power for the election :
int Party::CalcPartyPower() {
    if(ListOfPoliticians.empty())
        return 0;
    int total_power = 0;
    for(auto iter : ListOfPoliticians)
        total_power += (*iter).getPowerForElections();
    return total_power;
}

/// The next method tries to remove given politician from the current party :
bool Party::RemovePolitician(Politician *p) {
    if(ListOfPoliticians.empty())
        return false;
    auto iter = find(ListOfPoliticians.begin(), ListOfPoliticians.end(), p);
    if(iter != ListOfPoliticians.end()) {
        ListOfPoliticians.erase(iter);
        return true;
    }
    return false;
}

//// the next method adds politician to it's politician list :
void Party::AddPolitician(Politician *p) {
    ListOfPoliticians.push_back(p);
}