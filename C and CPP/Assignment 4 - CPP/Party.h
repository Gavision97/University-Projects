//
// Created by victor on 1/8/23.
//

#ifndef PROJECT5_PARTY_H
#define PROJECT5_PARTY_H

#include <string>
#include "Politician.h"
#include "vector"
#include "algorithm"

using namespace std;

/// abstract class with all of the Observer Pattern pure virtual
///  functions need to be implemented in Party class :
class Iparty {
public:
    virtual void notify(string _chairman)= 0;
    virtual void AddPolitician(Politician *p)=0;
    virtual bool RemovePolitician(Politician *p)=0;
};

class Party : public Iparty {
protected:
    string party_name, party_chairman;
    vector<Politician*> ListOfPoliticians;
    int chairman_id;
public:
    /// constructors :
    explicit Party(string _party_name): party_name(_party_name) {party_chairman = "None";chairman_id = 0;}

    /// deep copy constructor :
    Party(const Party& other): party_name(other.party_name), party_chairman(other.party_chairman),
    chairman_id(other.chairman_id){}

    virtual void notify(string _chairman) override;
    virtual bool RemovePolitician(Politician* p) override;
    virtual void AddPolitician(Politician *p) override;

    void Primemeries();
    int CalcPartyPower() ;
    vector<Politician*> getPoliticianList() const { return ListOfPoliticians;}

    /// pure virtual function for primaries :
    /// (this print function used to preform polymorphism in the parties
    /// and print their data without knowing/holding their political side R/D)
    virtual void PrintPartyInfo() = 0;

    /// get methods :
    string getParyName() const {return party_name;}
    string getPartyChairman() const {return party_chairman;}
    int getChairmanID() const {return chairman_id;}
    int getPartySize() const {return ListOfPoliticians.size(); }

    /// destructor :
    virtual ~Party() = default;
};


#endif //PROJECT5_PARTY_H

