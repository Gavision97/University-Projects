//
// Created by victor on 1/10/23.
//

#include "PoliticalSys.h"

//// destructor : (deallocating all the memory that allocated)
PoliticalSys::~PoliticalSys() {
    for(auto iter : AllPoliticianList)
        delete iter;
    for(auto iter : AllPartiesList)
        delete iter;
}

//// start main interface methods :

/// the next method tries to add politician to the political system
/// after that, if there are any available party that fit to his political side, he will be
/// added & notified (using observer pattern) with the party chairman (if the party has one)

void PoliticalSys::addPolitician() {
    int int_flag =0 , power_flag=0;
    cout << "---Create Politician---" << endl;
    string _f_name, _l_name;
    int _id, _power;
    char _politic_side, _role;
    while (true) {
        try {
            cout << "First name:" << endl;
            cin >> _f_name;
            cout << "Last name:" << endl;
            cin >> _l_name;
            cout << "ID:" << endl;
            cin >> _id;
            /// clear cin content to avoid infinite loop in case bad input :
            /// (same thing whenever receive integer from user)

            if(cin.fail()) int_flag = 1;
            cin.clear();
            cin.ignore(reinterpret_cast<streamsize>(numeric_limits<streamsize>::max), '\n');
            cout << "Power:" << endl;
            cin >> _power;
            if(cin.fail()) power_flag = 1;
            cin.clear();
            cin.ignore(reinterpret_cast<streamsize>(numeric_limits<streamsize>::max), '\n');
            cout << "Republican or Democratic person" << endl;
            cin >> _politic_side;
            cout << "Leader or Social" << endl;
            cin >> _role;
            /// Check if any of the input are invalid, and trow exception if needed :
            if (CheckIfIdExsist(_id) || _id < 0 || int_flag == 1) throw InvalidIdException();
            else if (_power < 0 || power_flag == 1) throw InvalidValueException();
            else if (_politic_side != 'D' && _politic_side != 'R') throw InvalidValueException();
            else if (_role != 'S' && _role != 'L') throw InvalidValueException();
            ///
            Politician *new_politician;
            if (_politic_side == 'D' && _role == 'L') {
                new_politician = new DemocraticPoliticianLeader(_f_name, _l_name, _id, _power);
                if(!new_politician) exit(1);
                DemocraticPoliticianList.push_back(new_politician);
            } else if (_politic_side == 'D' && _role == 'S') {
                new_politician = new DemocraticPoliticianSocial(_f_name, _l_name, _id, _power);
                if(!new_politician) exit(1);
                DemocraticPoliticianList.push_back(new_politician);
            } else if (_politic_side == 'R' && _role == 'L') {
                new_politician = new RepublicanPoliticianLeader(_f_name, _l_name, _id, _power);
                if(!new_politician) exit(1);
                RepublicanPoliticianList.push_back(new_politician);
            } else {
                new_politician = new RepublicanPoliticianSocial(_f_name, _l_name, _id, _power);
                if(!new_politician) exit(1);
                RepublicanPoliticianList.push_back(new_politician);
            }

            //// push the new politician to all politician list :
            AllPoliticianList.push_back(new_politician);

            //// search party for the new politician : (if there is any that fit)
            if(! AllPartiesList.empty()){
                char side = _politic_side;
                if(side == 'R' && !RepublicanPartyList.empty()){
                    if(RepublicanPartyList.size() == 1){
                        RepublicanPartyList[0]->AddPolitician(new_politician);
                        return;
                    }
                    //// first add the new politician to the first party that fits :
                    RepublicanPartyList[0]->AddPolitician(new_politician);
                    Party* curr_party = DemocraticPartyList[0];
                    for(auto next_p : DemocraticPartyList) {
                        /// for each party with same political side, check if fits better for him:
                        if(next_p->getParyName() != curr_party->getParyName() && next_p->getPartySize() < curr_party->getPartySize()){
                            curr_party->RemovePolitician(new_politician);
                            next_p->AddPolitician(new_politician);
                            curr_party = next_p;
                        }
                    }
                    return;
                }
                else if(side == 'D' && !DemocraticPartyList.empty()){
                    if(DemocraticPartyList.size() == 1){
                        DemocraticPartyList[0]->AddPolitician(new_politician);
                        return;
                    }
                    //// first add the new politician to the first party that fits :
                    DemocraticPartyList[0]->AddPolitician(new_politician);
                    Party* curr_party = DemocraticPartyList[0];
                    for(auto next_p : DemocraticPartyList) {
                        /// for each party with same political side, check if fits better for him:
                        if(next_p->getParyName() != curr_party->getParyName() && next_p->getPartySize() < curr_party->getPartySize()){
                            curr_party->RemovePolitician(new_politician);
                            next_p->AddPolitician(new_politician);
                            curr_party = next_p;
                        }
                    }
                    return;
                }
            }
            /// finished adding the politician and there is no matching party for him, thus return :
            return;
        }
            /// handle the exception if there any :
        catch (const InvalidIdException &ex) {
            cout << ex.what() << endl;
        }
        catch (const InvalidValueException &ex) {
            cout << ex.what() << endl;
        }
    }
}
/// done

//// the next method tries to remove politician from the politician system &
//// from his party: (if he had any)

void PoliticalSys::removePolitician() {
    Party* removed_politician_party = nullptr;
    int outer_flag = 1, int_flag =0;
    cout << "---Remove Politician---" << endl;
    int _id;
    while (true) {
        try {
            cout << "Enter the ID:" << endl;
            cin >> _id;
            if(cin.fail()) int_flag = 1;
            cin.clear();
            cin.ignore(reinterpret_cast<streamsize>(numeric_limits<streamsize>::max), '\n');
            if (!CheckIfIdExsist(_id) || _id < 0 || int_flag == 1) throw InvalidIdException();
            /// remove politician from his exact party (if he got any) :
            for (auto iter: AllPartiesList) {
                vector<Politician *> curr_politician_list = iter->getPoliticianList();
                if (curr_politician_list.empty()) continue;
                for (auto sec_iter: curr_politician_list)
                    if (sec_iter->getID() == _id) {
                        removed_politician_party = iter;
                        iter->RemovePolitician(sec_iter); /// found his party !
                        outer_flag = 0;
                        break;
                    }
                if(outer_flag == 0) break; /// already removed him, no point to keep iterate
            }
            int flag = 1;
            Politician *del_p;
            for (auto iter: AllPoliticianList)
                if (iter->getID() == _id) {
                    del_p = iter;
                    break;
                }
            /// now remove from him from his political side list of politician :
            auto position = find(RepublicanPoliticianList.begin(), RepublicanPoliticianList.end(), del_p);
            if (position != RepublicanPoliticianList.end()) {
                RepublicanPoliticianList.erase(position);
                flag = 0;
            }
            if (flag == 1) {
                position = find(DemocraticPoliticianList.begin(), DemocraticPoliticianList.end(), del_p);
                DemocraticPoliticianList.erase(position);
            }
            position = find(AllPoliticianList.begin(), AllPoliticianList.end(), del_p);
            if(removed_politician_party != nullptr) {
                int party_chairman_id = removed_politician_party->getChairmanID();
                if (party_chairman_id == 0 && del_p->getID() != party_chairman_id){
                    AllPoliticianList.erase(position);
                    delete del_p;
                    return;
                }
                else if (del_p->getID() == party_chairman_id) {
                    AllPoliticianList.erase(position);
                    /// if we got here, it means that del_p was his party chair man !
                    /// thus notify his party's new chairman to be None :
                    removed_politician_party->notify("None");
                    delete del_p;
                    return;
                }
                else{
                    AllPoliticianList.erase(position);
                    delete del_p;
                    return;
                }
            }
        }
            /// handle exceptions if there any :
        catch (const InvalidIdException &ex) {
            cout << ex.what() << endl;
        }
    }
}
/// done


//// the next method adds party to the politician system, and tries to also
/// add politician to the party (if there any politicians that fit with their
/// political side), after that notified them with new chairman as "None"
/// using observer pattern :
/// (new party with no chairman yet)

void PoliticalSys::addParty() {
    string temp;
    cout << "---Create Party---" << endl;
    string _party_name;
    char _polital_side;
    while (true) {
        try {
            cout << "Name:" << endl;
            cin >> _party_name;
            cout << "Republican or Democratic party" << endl;
            cin >> _polital_side;

            if (CheckIfPartyExsist(_party_name))
                throw InvalidValueException();
            if (_polital_side != 'R' && _polital_side != 'D')
                throw InvalidValueException();

            /// create party :
            Party *new_party;
            if (_polital_side == 'R') {
                new_party = new RepublicanParty(_party_name);
                if(!new_party) exit(1);
                RepublicanPartyList.push_back(new_party);
            } else {
                new_party = new DemocraticParty(_party_name);
                if(!new_party) exit(1);
                DemocraticPartyList.push_back(new_party);
            }
            /// add the party to all parties list :
            AllPartiesList.push_back(new_party);

            /// now all the current politicians check the new party : (if possible)
            int curr_poli_party_size;
            if(_polital_side == 'R'){
                for(auto iter : RepublicanPoliticianList){
                    Party* temp_party = getPoliticianPartyR(iter->getID());
                    if(temp_party == nullptr){ /// in case curr politician does not have party
                        new_party->AddPolitician(iter);
                        continue;
                    }
                    curr_poli_party_size = getRepublicPartySize(_party_name);
                    if(curr_poli_party_size == 0) {
                        new_party->AddPolitician(iter);
                        temp_party->RemovePolitician(iter);
                    }
                    else{
                        curr_poli_party_size = temp_party ->getPartySize();
                        if(curr_poli_party_size > new_party ->getPartySize()){
                            temp_party->RemovePolitician(iter);
                            new_party->AddPolitician(iter);
                        }
                    }
                }
            }
            else { /// _political_side == 'D'
                for(auto iter : DemocraticPoliticianList){
                    Party* temp_party = getPoliticianPartyD(iter->getID());
                    if(temp_party == nullptr){
                        new_party ->AddPolitician(iter);
                        continue;
                    }
                    curr_poli_party_size = getDemocraticPartySize(_party_name);
                    if(curr_poli_party_size == 0) {
                        new_party->AddPolitician(iter);
                        temp_party->RemovePolitician(iter);
                    }
                    else{
                        curr_poli_party_size = temp_party ->getPartySize();
                        if(curr_poli_party_size > new_party ->getPartySize()){
                            temp_party->RemovePolitician(iter);
                            new_party->AddPolitician(iter);
                        }
                    }
                }
            }
            /// notify all the new member that their new chairman is None !
            new_party->notify("None");

            AllPartiesFor_O1_check.push_back(new_party);
            sort(AllPartiesFor_O1_check.begin(), AllPartiesFor_O1_check.end(), [](Party* first, Party* second){
                if(first->getPartySize() != second->getPartySize()) return first->getPartySize() < second->getPartySize() ;
                return first ->getParyName() < second ->getParyName();
            });
            return;
        }
            /// handle exceptions if there any :
        catch (const InvalidValueException &ex) {
            cout << ex.what() << endl;
        }
    }
}
/// done


//// the next method removes party from the politician system and
//// fines new party for the politician that took party
/// in the removed party (if there was any), if there is no any
/// available party for them they'll remained without party, and
/// if there is available party, they will be added and notified with
/// the party's chairman : (observer pattern)

void PoliticalSys::removeParty() {
    if (AllPartiesList.empty()) return;
    cout << "---Remove Party---" << endl;
    string _party_name;
    do {
        try {
            cout << "Enter party name:" << endl;
            cin >> _party_name;
            if (!CheckIfPartyExsist(_party_name))
                throw InvalidNameException();
            Party *removed_party = getPartyByName(_party_name);
            int removed_size = removed_party->getPartySize();
            int flag = 1;
            if (removed_size == 0) { /// no politicians in curr party
                auto position = find(DemocraticPartyList.begin(), DemocraticPartyList.end(), removed_party);
                if(position != DemocraticPartyList.end()) {
                    DemocraticPartyList.erase(position);
                    flag = 0;
                }
                if(flag == 1){
                    position = find(RepublicanPartyList.begin(), RepublicanPartyList.end(), removed_party);
                    RepublicanPartyList.erase(position);
                }
                position = find(AllPartiesList.begin(), AllPartiesList.end(), removed_party);
                AllPartiesList.erase(position);
                return;
            }
            else{
                char side = getPartySide(removed_party);
                for(auto iter : removed_party->getPoliticianList()) {
                    bool notified = false;
                    if(side == 'D') {
                        if (DemocraticPartyList.size() != 1) {
                            /// first add the current politician to the first party that's fit:
                            if (DemocraticPartyList[0]->getParyName() == removed_party->getParyName())
                                DemocraticPartyList[1]->AddPolitician(iter);
                            else DemocraticPartyList[0]->AddPolitician(iter);
                            Party *curr_party = DemocraticPartyList[0];
                            for (auto next_p: DemocraticPartyList) {
                                /// for each party with same political side, check if fits better for him:
                                if (next_p->getParyName() != curr_party->getParyName() &&
                                    next_p->getPartySize() < curr_party->getPartySize() &&
                                    next_p->getParyName() != removed_party->getParyName()) {
                                    curr_party->RemovePolitician(iter);
                                    next_p->AddPolitician(iter);
                                    curr_party = next_p;
                                }
                            }
                            iter->notifyPolitician(
                                    curr_party->getPartyChairman()); /// notify the politician with his new party chairman
                            notified = true;
                        }
                    }
                    else { /// side == 'R'
                        if (RepublicanPartyList.size() > 1) {
                            /// first add the current politician to the first party that's fit:
                            if (RepublicanPartyList[0]->getParyName() == removed_party->getParyName())
                                RepublicanPartyList[1]->AddPolitician(iter);
                            else RepublicanPartyList[0]->AddPolitician(iter);
                            Party *curr_party = RepublicanPartyList[0];
                            for (auto next_p: RepublicanPartyList) {
                                /// for each party with same political side, check if fits better for him:
                                if (next_p->getParyName() != curr_party->getParyName() &&
                                    next_p->getPartySize() < curr_party->getPartySize() &&
                                    next_p->getParyName() != removed_party->getParyName()) {
                                    curr_party->RemovePolitician(iter);
                                    next_p->AddPolitician(iter);
                                    curr_party = next_p;
                                }
                            }
                            iter->notifyPolitician(
                                    curr_party->getPartyChairman()); /// notify the politician with his new party chairman
                            notified = true;
                        }
                    }
                    if(! notified) {/// in case curr politician doesn't have any new party
                        iter->notifyPolitician("None");
                        }
                    /// finally remove curr politician from his previous party :
                    removed_party->RemovePolitician(iter);
                }
            }
            /// now remove the party from parties lists :
            removePartyFromSideList(removed_party);
            auto position = find(AllPartiesList.begin(), AllPartiesList.end(), removed_party);
            AllPartiesList.erase(position);
            position = find(AllPartiesFor_O1_check.begin(),AllPartiesFor_O1_check.end(), removed_party);
            AllPartiesFor_O1_check.erase(position);
            sort(AllPartiesFor_O1_check.begin(), AllPartiesFor_O1_check.end(), [](Party* first, Party* second){
                if(first->getPartySize() != second->getPartySize()) return first->getPartySize() < second->getPartySize() ;
                return first ->getParyName() < second ->getParyName();
            });
            delete removed_party;
            return;
        }
        /// Catch the exception if there any :
        catch (const InvalidNameException &ex) {
            cout << ex.what() << endl;
        }
    } while(true);
}
/// done

/// the next method execute election by preforming primaries in each party &
/// then choosing the party with the maximum power that joined first to the
/// politician system : (in case there are few parties with the same maximum power)

void PoliticalSys::elections() const {
    if(AllPartiesList.empty()) return;
    cout << "----Primaries----" << endl;
    for(auto iter : AllPartiesList)
        iter->Primemeries();
    cout << "----Elections----" << endl;
    int max_power = 0;
    for(auto iter : AllPartiesList) {
        int curr_party_election_power = iter->CalcPartyPower();
        cout <<  "Party: " << iter->getParyName() << ",Power: " << curr_party_election_power << endl;
        if(curr_party_election_power > max_power)
            max_power = curr_party_election_power;
    }
    string winner_party, prime_minister;
    for(auto iter : AllPartiesList){
        if(iter->CalcPartyPower() == max_power) {
            winner_party = iter->getParyName();
            prime_minister = iter ->getPartyChairman();
            break;
        }
    }
    cout << "----Elections Results----" << endl;
    cout << winner_party << " party won the elections and " << prime_minister << " is the prime minister" << endl;
}
/// done

/// the next method prints all the politician in the
/// political system using polymorphism to print each
/// politician by his own unique print function :

void PoliticalSys::printPoliticians() const {
    if(AllPoliticianList.empty()) return;
    cout << "----Politicians----" << endl;
    for(auto iter : AllPoliticianList)
        iter -> printPolitician();
}
/// done

/// the next method uses polymorphism to print each party by
/// her own unique print function :
void PoliticalSys::printParties() const {
    if (AllPartiesList.empty()) return;
    cout << "----Parties----" << endl;
    for (auto iter: AllPartiesList)
        iter->PrintPartyInfo();
}
/// done

/// the next method uses the temp vector that hold pointers to parties
/// in the political system to know which one is the biggest in O(1) :
/// (in every change with politician/parties the vector got sorted
/// by first size & then by string, see for example method addParly())

void PoliticalSys::BiggestParty() const {
    if(AllPartiesFor_O1_check.empty()) return;
    Party* biggest = AllPartiesFor_O1_check.back();
    cout << "----Biggest Party----" << endl;
    cout << "[" << biggest->getParyName() << "," << biggest->getPartySize() << "]" << endl;
}
/// done.



/// implement all of the helper methods for PoliticianSys :

/// the next method helps to find out if a hive politician exist in the system :
bool PoliticalSys::CheckIfIdExsist(int id) const{
    for(auto iter : AllPoliticianList)
        if(iter->getID() == id)
            return true;
    return false;
}

/// the next method help to find out if a given party exist in the system :
bool PoliticalSys::CheckIfPartyExsist(const string& _party_name) const {
    for(auto iter : AllPartiesList)
        if(iter->getParyName() == _party_name)
            return true;
    return false;
}

int PoliticalSys::getDemocraticPartySize(const string& _party_name) const {
    for(auto iter : DemocraticPartyList)
        if(iter->getParyName() == _party_name)
            return iter->getPoliticianList().size();
    return 0;
}

int PoliticalSys::getRepublicPartySize(const string& _party_name) const {
    for(auto iter : RepublicanPartyList)
        if(iter->getParyName() == _party_name)
            return iter->getPoliticianList().size();
    return 0;
}

Party *PoliticalSys::getPoliticianPartyD(int _id) const {
    for(auto iter : DemocraticPartyList){
        vector<Politician*> curr_poli_list = iter->getPoliticianList();
        for(auto sec_iter : curr_poli_list)
            if(sec_iter->getID() == _id)
                return iter;
    }
    return nullptr;
}

Party *PoliticalSys::getPoliticianPartyR(int _id) const {
    for(auto iter : RepublicanPartyList){
        vector<Politician*> curr_poli_list = iter->getPoliticianList();
        for(auto sec_iter : curr_poli_list)
            if(sec_iter->getID() == _id)
                return iter;
    }
    return nullptr;
}

//// the next method help to find and return party by its name
Party *PoliticalSys::getPartyByName(const string& _name) const {
    for (auto iter: AllPartiesList)
        if (iter->getParyName() == _name)
            return iter;
    return nullptr;
}

void PoliticalSys::removePartyFromSideList(Party *p){
    auto position = find(RepublicanPartyList.begin(), RepublicanPartyList.end(), p);
    if(position != RepublicanPartyList.end()) {
        RepublicanPartyList.erase(position);
        return;
    }
    position = find(DemocraticPartyList.begin(), DemocraticPartyList.end(), p);
    if(position != RepublicanPartyList.end()){
        DemocraticPartyList.erase(position);
        return;
    }
}

char PoliticalSys::getPartySide(Party *p) const {
    for(auto iter : RepublicanPartyList)
        if(iter->getParyName() == p->getParyName())
            return 'R';
    for(auto iter : DemocraticPartyList)
        if(iter ->getParyName() == p ->getParyName())
            return 'D';
    return 'N';
}

//// implement constructor that gets file steam and initialized data :
PoliticalSys::PoliticalSys(const string& file_stream) {
    string line, token, _f_name, _l_name;
    int _id, _power;
    basic_string<char> l_role;
    basic_string<char> l_political_side;
    char _politic_side, _role;
    ifstream f(file_stream);
    getline(f, line, '\n');
    while(getline(f, line,'\n')){
        vector<string> curr_line;
        stringstream ss(line);
        while(ss >> token){
            curr_line.push_back(token);
        }
        if(curr_line.size() < 5 || curr_line[0] == "Parties:") break; /// finished reading politicians !
        _f_name = curr_line[0];
        _l_name = curr_line[1];
        sscanf(curr_line[2].c_str(), "%d", &_id);
        sscanf(curr_line[3].c_str(), "%d", &_power);
        l_political_side = curr_line[4];
        _politic_side = l_political_side[0];
        l_role = curr_line[5];
        _role = l_role[0];
        //// create new politician :
        Politician *new_politician;
        if (_politic_side == 'D' && _role == 'L') {
            new_politician = new DemocraticPoliticianLeader(_f_name, _l_name, _id, _power);
            if(!new_politician) exit(1); /// exit the program in case allocation failed (destructor will delete all allocated memory)
            DemocraticPoliticianList.push_back(new_politician);
        } else if (_politic_side == 'D' && _role == 'S') {
            new_politician = new DemocraticPoliticianSocial(_f_name, _l_name, _id, _power);
            if(!new_politician) exit(1);
            DemocraticPoliticianList.push_back(new_politician);
        } else if (_politic_side == 'R' && _role == 'L') {
            new_politician = new RepublicanPoliticianLeader(_f_name, _l_name, _id, _power);
            if(!new_politician) exit(1);
            RepublicanPoliticianList.push_back(new_politician);
        } else {
            new_politician = new RepublicanPoliticianSocial(_f_name, _l_name, _id, _power);
            if(!new_politician) exit(1);
            RepublicanPoliticianList.push_back(new_politician);
        }

        //// push the new politician to all politician list :
        AllPoliticianList.push_back(new_politician);
    }
    /// finished with the politician, now read parties :
    string _party_name ;
    char _polital_side;
    while(getline(f, line,'\n')){
        vector<string> curr_line;
        stringstream ss(line);
        while(ss >> token){
            curr_line.push_back(token);
        }
        _party_name = curr_line[0];
        l_political_side = curr_line[1];
        _polital_side = l_political_side[0];

        /// create party :
        Party *new_party;
        if (_polital_side == 'R') {
            new_party = new RepublicanParty(_party_name);
            if(!new_party) exit(1);
            RepublicanPartyList.push_back(new_party);
        } else {
            new_party = new DemocraticParty(_party_name);
            if(!new_party) exit(1);
            DemocraticPartyList.push_back(new_party);
        }
        /// add the party to all parties list :
        AllPartiesList.push_back(new_party);

        /// now all the current politicians check the new party : (if possible)
        int curr_poli_party_size;
        if(_polital_side == 'R'){
            for(auto iter : RepublicanPoliticianList){
                Party* temp_party = getPoliticianPartyR(iter->getID());
                if(temp_party == nullptr){ /// in case curr politician does not have party
                    new_party->AddPolitician(iter);
                    continue;
                }
                curr_poli_party_size = getRepublicPartySize(_party_name);
                if(curr_poli_party_size == 0) {
                    new_party->AddPolitician(iter);
                    temp_party->RemovePolitician(iter);
                }
                else{
                    curr_poli_party_size = temp_party ->getPartySize();
                    if(curr_poli_party_size > new_party ->getPartySize()){
                        temp_party->RemovePolitician(iter);
                        new_party->AddPolitician(iter);
                    }
                }
            }
        }
        else { /// _political_side == 'D'
            for(auto iter : DemocraticPoliticianList){
                Party* temp_party = getPoliticianPartyD(iter->getID());
                if(temp_party == nullptr){
                    new_party ->AddPolitician(iter);
                    continue;
                }
                curr_poli_party_size = getDemocraticPartySize(_party_name);
                if(curr_poli_party_size == 0) {
                    new_party->AddPolitician(iter);
                    temp_party->RemovePolitician(iter);
                }
                else{
                    curr_poli_party_size = temp_party ->getPartySize();
                    if(curr_poli_party_size > new_party ->getPartySize()){
                        temp_party->RemovePolitician(iter);
                        new_party->AddPolitician(iter);
                    }
                }
            }
        }

        /// pushes the party to temp vector to know who's the biggest party in O(1) :
        /// (also sorting the vector first by size and secondly by string)
        AllPartiesFor_O1_check.push_back(new_party);
        sort(AllPartiesFor_O1_check.begin(), AllPartiesFor_O1_check.end(), [](Party* first, Party* second){
            if(first->getPartySize() != second->getPartySize()) return first->getPartySize() < second->getPartySize() ;
            return first ->getParyName() < second ->getParyName();
        });
    }
}
/// done