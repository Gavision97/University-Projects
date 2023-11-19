#ifndef C_HW2_JERRY_NEW_H
#define C_HW2_JERRY_NEW_H

#endif //C_HW2_JERRY_NEW_H

#ifndef C_HW2_JERRY_H
#define C_HW2_JERRY_H
#include <stdio.h>
#include  "Defs.h"
#define SIZE 30
#define MAX_INPUT_SIZE 300

typedef struct Planet_t {
    char* planetName; // Buffer for planet's name.
    float x,y,z; // Planet's coordinates.
}Planet;

typedef struct Origin_t {
    Planet* planetD; // Jerry's planet.
    char* dimension; // Jerry's dimension.
}Origin;

typedef struct Physical_char_t {
    char* phy_name; // characteristic name.
    float phy_value; // characteristic value.
}PhysicalChar;

typedef struct Jerry_r{
    char* ID; // Jerry's ID.
    int happiness; // Jerry's rate of happiness. (0-100)
    Origin* origin; // Pointer to Jerry's origin.
    int numOfPhyc; // The total amount of Jerry's physical characteristic
    Planet* planet;
    PhysicalChar** phyC; // Array of pointers for Jerry's physical characteristics.
}Jerry;


// The declaration of the functions:

/* The first function creates Jerry and initialize he's characteristics.
 * All arguments have been passed by address,except one, so changes will be valid-
 * a. char* - pointer to Jerry's ID.
 * b. char* - pointer to jerry's dimension.
 * c. int - Integer between 0-100 tht represents Jerry's happiness rate.
 * d. Planet* - Pointer to Jerry's planet.
 * The function return pointer to jerry after he has modified.
*/
Jerry* JerryCreate(char*, char* , int , Planet*);

/* The next function creates planet and initialize he's characteristics.
 * The first two arguments have been passed by address, so changes will be valid.
 * a. char* - pointer to planet's name.
 * b+c+d -- coordinates x,y & z that represents planet's location in space.
 * c+d+e float - coordinates x,y & z that represents planet's location in space.
 * The function returns pointer to the planet after modified.
 */
Planet*  PlanetCreate(char*, float, float, float);

/*The next function creates physical characteristic.
 * Characteristic name and physical characteristic have been passed by address.
 * a. char* - pointer to the phyC.
 * b. float - the value of phyC.
 * The function return pointer to the PhyC after it has been modified.
 */
PhysicalChar* PhyCCreate(char*, float);
/*The next function creates Origin structure.
 * a. Origin* - pointer to the origin.
 * b. Planet* - pointer to the planet.
 * c. char* - pointer to the dimension.
 * The function return status due to its success/failure to create Origin structure.
 */
status OriginCreate(Origin* ,Planet*, char*);
/*
 * The next function gets pointer to Jerry and pointer to phyC name and checks if Jerry have that phyC.
 * returns true/false.
 */
bool PhyIn(Jerry*, char*);
/*
 * The next function gets pointer to Jerry and pointer to phyC and tries to add the phyC to Jerry.
 * return status.
 */
status PhyAdd(Jerry*, PhysicalChar*);
/*
 * The next function gets pointer to Jerry and pointer to phyC name and tries to delete that phyC from Jerry.
 * return status.
 */
status PhyDelete(Jerry*, char*);
/*
 * The next function gets Jerry and tries to print his details.
 * returns status.
 */
status PrintJerry(Jerry*);
/*
 * The next function gets pointer to Planet and tries to print Planet's details.
 * return status.
 */
status PrintPlanet(Planet*);
/*
 * The next function gets pointer to Jerry and tries to destroy/free all Jerry details.
 * returns status.
 */
status DestroyJerry(Jerry*);
/*
 * The next function gets pointer to Planet and tries to destroy/free all Planets details
 * return status.
 */
status DestroyPlanet(Planet*);
/*
 * The next function gets pointer to Origin and tries to destroy/free Origins details.
 * returns status.
 */
status DestroyOrigin(Origin*);
/*
 * The next function gets pointer to phyC and tries to destroy/free phyC details.
 * returns status.
 */
status DestroyPhyC(PhysicalChar*);

#endif //C_HW2_JERRY_H
