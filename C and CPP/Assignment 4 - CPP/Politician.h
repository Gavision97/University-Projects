//
// Created by victor on 1/7/23.
//

#ifndef PROJECT_5_POLITICIAN_H
#define PROJECT_5_POLITICIAN_H

/// include all needed libraries :
#include <iostream>
using namespace std;
#include <string>


/// abstract class with the Observer Pattern pure virtual function
///that need to be implemented in Politician class :
class Ipolitician {
public:
    virtual void notifyPolitician(string chairman) = 0;
};

/// Politician is an abstract class because there is two politicians type : Democratic & Republican
class Politician : public Ipolitician {

protected:
    string first_name;
    string last_name;
    string chairman;
    int id, power;
public:
    /// constructors :
    Politician(string _first_name, string _last_name,int _id, int _power):
            first_name(_first_name), last_name(_last_name), id(_id), power(_power)
    {chairman = "None";}

    /// deep copy constructor :
    Politician(const Politician& other) :
    first_name(other.first_name), last_name(other.last_name), chairman(other.chairman),
    id(other.id), power(other.power){}

    //// operator overloading :
    Politician& operator=(const Politician& other);
    bool operator<(const Politician& other) const;
    bool operator==(const Politician& other) const;

    /// Politician observer function to update chairman when needed : (for Observer Pattern)
    virtual void notifyPolitician(string _chairman) override;

    /// virtual function to print the Politician as needed :
    /// IMPORTANT !! : the next pure virtual function make are
    /// used to make sure we dont hold any field/function to
    /// know what is the political side (D/R) & role (L/S)
    /// of the politician (as mentioned in the project instructions)
    virtual void printPolitician()const =0; /// make politician abstract class
    virtual int getPowerForElections() const =0;
    virtual bool TakePartInThePrimaries() const=0;

    /// get methods :
    int getPower() const {return power;}
    string getName() const {return first_name;}
    int getID() const {return id;}

    /// destructor :
    virtual ~Politician() { }

};

#endif //PROJECT_5_POLITICIAN_H
