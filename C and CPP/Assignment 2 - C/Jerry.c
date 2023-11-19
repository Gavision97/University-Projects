#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Defs.h"
#include "Jerry.h"


static int findIndex(Jerry* jerry, char *p_name){
    int i;
    for(i=0; i < jerry -> numOfPhyc; i++){
        if(jerry -> phyC[i] != NULL && strcmp(jerry->phyC[i] ->phy_name ,p_name ) == 0)
            return i;
    }
    return failure;
}

Jerry* JerryCreate(char* id,char* dimension, int happiness,Planet* planet){
    Jerry* n_Jerry = (Jerry*) malloc(sizeof(Jerry));
    if(! n_Jerry) return NULL;
    (n_Jerry) -> ID = (char *) malloc(strlen(id)+1);
    if(! n_Jerry -> ID){
        printf("Memory Problem\n");
        return NULL;
    }
    if(happiness < 0 || happiness > 100) return NULL; //// checks if range of happiness in the correct range
    n_Jerry -> ID = strcpy((n_Jerry) -> ID, id);
    n_Jerry -> happiness = happiness;
    n_Jerry -> planet = planet;
    if(!n_Jerry -> planet) return NULL;
    Origin* origin = (Origin*)malloc(sizeof(Origin));
    if(! origin){
        free(n_Jerry);
        printf("Memory Problem\n");
        return NULL;
    }
    if(OriginCreate(origin, planet, dimension) == failure) return NULL;
    n_Jerry -> origin = origin;
    n_Jerry -> numOfPhyc = 0;
    n_Jerry -> phyC = NULL;
    return n_Jerry;
}

Planet* PlanetCreate(char *name, float x, float y, float z){
    Planet * n_Planet = (Planet*)malloc(sizeof (Planet));
    if(! n_Planet) {
        printf("Memory Problem\n");
        return NULL;
    }
    n_Planet -> planetName = (char*)malloc(strlen(name)+1);
    if(! n_Planet -> planetName) {
        printf("Memory Problem\n");
        DestroyPlanet(n_Planet);
        return NULL;
    }
    n_Planet -> planetName = strcpy(n_Planet -> planetName, name);
    n_Planet -> x = x;
    n_Planet -> y = y;
    n_Planet -> z = z;
    return n_Planet;
}

PhysicalChar* PhyCCreate(char *name, float value){
    PhysicalChar* n_PhyC = (PhysicalChar*)malloc(sizeof (PhysicalChar));
    if(! n_PhyC) {
        printf("Memory Problem\n");
        return NULL;
    }
    n_PhyC -> phy_name = (char*)malloc(strlen(name)+1);
    if(! n_PhyC -> phy_name){
        printf("Memory Problem\n");
        DestroyPhyC(n_PhyC);
        return NULL;
    }
    n_PhyC -> phy_name = strcpy((n_PhyC) -> phy_name, name);
    n_PhyC -> phy_value = value;
    return n_PhyC;
}

status OriginCreate(Origin* n_Origin, Planet* planet, char* dimension){
    n_Origin -> planetD = planet;
    n_Origin -> dimension= (char*)malloc(strlen(dimension)+1);
    if(! n_Origin -> dimension){
        printf("Memory Problem\n");
        return failure;
    }
    n_Origin -> dimension = strcpy(n_Origin -> dimension, dimension);
    return success;
}

bool PhyIn(Jerry* jerry, char* p_name){
    return findIndex(jerry, p_name) != failure;
}

status PhyAdd(Jerry* jerry, PhysicalChar* Phyc){
    jerry -> numOfPhyc ++;
    jerry -> phyC = (PhysicalChar**) realloc(jerry -> phyC, sizeof(PhysicalChar*)*(jerry -> numOfPhyc));
    if(! jerry -> phyC) {
        printf("Memory Problem\n");
        return failure;
    }
    jerry -> phyC[jerry -> numOfPhyc -1] = Phyc;
    return success;
}

status PhyDelete(Jerry* jerry, char* p_name) {
    if(jerry -> numOfPhyc ==0) return failure;
    int index = findIndex(jerry, p_name);
    if(index == failure) return failure; //// In case there is no such physical characteristic in Jerry
    if(jerry ->numOfPhyc == 1){ //// in case there are only one characteristic.
        DestroyPhyC(jerry -> phyC[0]);
        jerry ->numOfPhyc = 0;
        return success;
    }
    PhysicalChar* tmp_p = jerry -> phyC[index];
    if(! tmp_p) return failure;
    if(index == jerry ->numOfPhyc -1) DestroyPhyC(jerry -> phyC[index]);
    else {
        DestroyPhyC(jerry->phyC[index]);
        for (int j = index; j < jerry->numOfPhyc - 1; j++)
            jerry->phyC[j] = jerry->phyC[j + 1];
    }
    jerry -> phyC = (PhysicalChar**) realloc(jerry -> phyC, sizeof(PhysicalChar*)*(jerry -> numOfPhyc)) ; //// reallocated new memory after deleting physical characteristic.
    if(! jerry -> phyC) return failure;
    jerry -> numOfPhyc --;
    return success;
}

status PrintJerry(Jerry* jerry){
    if(! jerry) return failure;
    printf("Jerry , ID - %s : \n", jerry -> ID);
    printf(("Happiness level : %d \n"), jerry -> happiness);
    printf(("Origin : %s \n"), jerry -> origin -> dimension);
    printf(("Planet : %s (%.2f,%.2f,%.2f) \n"), jerry -> planet ->planetName, jerry -> planet ->x, jerry -> planet ->y , jerry -> planet ->z);
    if(jerry -> numOfPhyc > 0) {
        printf(("Jerry's physical Characteristics available : \n"));
        printf("\t");
        for (int i = 0; i < jerry->numOfPhyc -1; i++) {
            if(jerry -> phyC[i] != NULL) printf("%s : %.2f , ", jerry -> phyC[i] ->phy_name, jerry -> phyC[i] ->phy_value);
        }
        int last = jerry->numOfPhyc -1;
        if(jerry -> phyC[last] != NULL) printf("%s : %.2f \n", jerry -> phyC[last] ->phy_name, jerry -> phyC[last] ->phy_value);
    }
    return success;
}

status PrintPlanet(Planet* planet){
    if(! planet) return failure;
    printf(("Planet : %s (%.2f,%.2f,%.2f) \n"), planet ->planetName, planet ->x, planet->y , planet ->z);
    return success;
}


status DestroyPlanet(Planet* planet){
    if(! planet) return failure;
    free(planet ->planetName);
    free(planet);
    return success;
}

status DestroyOrigin(Origin* origin){
    if(! origin) return failure;
    free(origin ->dimension);
    free(origin);
    return  success;
}
status DestroyJerry(Jerry* jerry){
    if(! jerry) return failure;
    free(jerry -> ID);
    DestroyOrigin(jerry -> origin);
    if(jerry ->phyC != NULL) {
        for(int i = 0 ; i < jerry -> numOfPhyc ; i++)
            DestroyPhyC(jerry -> phyC[i]);
    }
    jerry ->planet = NULL;
    free(jerry -> phyC);
    free(jerry);
    return success;
}

status DestroyPhyC(PhysicalChar* phyC){
    if(! phyC) return failure;
    free(phyC ->phy_name);
    free(phyC);
    return success;
}

//// New functions to help in JerryBoree project :

char* GetJerryID(Jerry* jerry){
    if(! jerry) return NULL;
    return jerry ->ID;
}

float GetPhycVal(Jerry* j, char* phyC_name){
    if(! j) return -1;
    int phy_index = findIndex(j, phyC_name);
    if(phy_index == failure) return -1;
    PhysicalChar* temp_phy = j ->phyC[phy_index];
    if(! temp_phy) return -1;
    return temp_phy ->phy_value;
}

int GetJerryHappiness(Jerry* j){
    if(! j) return -1;
    return j ->happiness;
}
int GetJerriesNumOfPhyc(Jerry* j){
    if(! j) return -1;
    return j ->numOfPhyc;
}
status AddToJerryHappiness(Jerry* j, int amount){
    if(! j) return failure;
    j ->happiness = j ->happiness +amount;
    return success;
}

status SubstractJerryHappiness(Jerry* j, int amount) {
    if (!j) return failure;
    j ->happiness = j ->happiness - amount;
    return success;
}
status SetJerryHappiness(Jerry* j, int amount){
    if(! j) return failure;
    j ->happiness = amount;
    return success;
}
PhysicalChar** GetJerriesPhyc(Jerry* j){
    if(! j) return NULL;
    return j ->phyC;
}
float GetPlanetX(Planet* p){
    if(! p) return -1;
    return p ->x;

}
float GetPlanetY(Planet* p){
    if(! p ) return -1;
    return p ->y;
}
float GetPlanetZ(Planet* p) {
    if (!p) return -1;
    return p->z;
}