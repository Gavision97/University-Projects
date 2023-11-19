#include <stdlib.h>
#include <string.h>
#include "Defs.h"
#include "LinkedList.h"
#include "HashTable.h"
#include "MultiValueHashTable.h"
#include "Jerry.h"

//// Define macros to help eliminate rewrite code :

#define FINISH_SCRIPT_1 finish_script(JerryMVHT, JerryHash, planet_arr, PhyLinkedList, JerriesID, i, 1 )
#define FINISH_SCRIPT_2 finish_script(JerryMVHT, JerryHash, planet_arr, PhyLinkedList, JerriesID, num_of_planets, 2 )
#define FINISH_SCRIPT_3 finish_script(JerryMVHT, JerryHash, planet_arr, PhyLinkedList, JerriesID, num_of_planets, 3 )
#define FINISH_SCRIPT_4 finish_script(JerryMVHT, JerryHash, planet_arr, PhyLinkedList, JerriesID, num_of_planets, 4 )
#define PRINT_7_MENU print_7()
#define PRINT_8_MENU print_8()
#define SCAN_BUFFER scanf("%s", buffer)

void print_7(){
    printf("What information do you want to know ? \n");
    printf("1 : All Jerries \n");
    printf("2 : All Jerries by physical characteristics \n");
    printf("3 : All known planets \n");
}
void print_8(){
    printf("What activity do you want the Jerries to partake in ? \n");
    printf("1 : Interact with fake Beth \n");
    printf("2 : Play golf \n");
    printf("3 : Adjust the picture settings on the TV \n");
}
//// Define functions for JerryLL (JerryID - LinkedList) See ReadMe for more explanation:
Element copyID_LL(Element element){
    if(! element) return NULL;
    return element;
}
status freeID_LL(Element element){
    //// JerryID is LinkedList of Jerris ids pointers, so we dont want to free the pointer that will
    //// cause free from the hash table the contains the real data value, so we just return (same concept returns with
    //// other data structures that contains pointers to the real data ( See ReadMe for further explanation)
    if(! element) return failure;
    return success;
}

status printID_LL(Element element){
    if(! element) return failure;
    printf("%s\n", (char*)element);
    return success;
}
bool equalName(Element element1, Element element2){
    if(! element1 || ! element2) return false;
    if(strcmp((char*)element1, (char*)element2) == 0) return true;
    return false;
}

//// Define functions for JerryMVHT (MultiValueHashTable) See ReamMe for more explanation :
Element copyPhyMVHT(Element element){
    if(! element) return NULL;
    return element;
}
status freePhyMVHT(Element element){
    if(! element) return failure;
    return success;
}
status printPhyMVHT(Element element) {
    if (!element) return failure;
    printf("%s\n", (char *) element);
}
Element copyIdMVHT(Element element){
    if(! element) return NULL;
    return element;
}
status freeIdMVHT(Element element){
    if(! element) return failure;
    return success;
}
status printIdMVHT(Element element){
    if(! element) return failure;
    printf("%s\n", (char*)element);
    return success;
}
/// Define the functions that going to be used for creating JerryHash : (See ReadeMe for more explanation)
Element copyJerry(Element element){
    if(! element) return NULL;
    return (Jerry*)element;
}
status freeJerry(Element element){
    if(! element) return failure;
    if(DestroyJerry((Jerry*)element) == failure) return failure;
    return success;
}
status printJerry(Element element){
    if(! element) return failure;
    if(PrintJerry((Jerry*)element) == failure) return failure;
    return success;
}
Element copyID(Element element){
    if(! element) return NULL;
    return (char*)element;
}
status freeID(Element element){ /// no allocation has been made for jerry's ID.
    if(! element) return failure;
    free((char*)element);
    return success;
}
status printID(Element element){
    if(! element) return failure;
    printf("%s\n", (char*)element);
    return success;
}
int tansformIntoNum(Element element){
    if(! element) return -1;
    int temp = *(int*)element;
    return(*(int*)element);
}
//// Define functions for PhycLinkedList: (equalFunc has taken from JerryMVHT above) See ReadMe for more explanation
Element copyPhyc(Element element){
    if(! element) return NULL;
    return (char*)element;
}
status freePhyc(Element element){
    if(! element) return failure;
    char* temp = (char*)element;
    free((char*)element);
    return success;
}
status printPhyc(Element element){
    if(! element) return failure;
    printf("%s\n", (char*)element);
}
///// finished.

//// Helper function to find out if a given planet exist in PlanetArr :
Planet* findPlaned(Planet** planetArr, int num_of_planets, char* SplanetName) {
    int index;
    for(index = 0 ; index < num_of_planets ; index++) {
        int result = strcmp(planetArr[index] ->planetName, SplanetName);
        if(result == 0) return planetArr[index];
    }
    return NULL;
}

//// The next function finished the script according to some flag.
//// The flag changes during the program at each stage that created new data structure.
void finish_script(MultiVHash JerryMVHT, hashTable JerryHash, Planet** planets, LinkedList phyCLinkedList,
                   LinkedList JerriesID, int num_of_planets, int flag ) {
    if(flag == 1 && planets){
        for(int i=0 ; i <= num_of_planets-1 ; i++) {
            if (DestroyPlanet(planets[i]) == failure) {
                exit(1);
            }
        }
        exit(1);
    }

    if(flag == 2 && planets && JerryHash && phyCLinkedList && JerriesID){
        for(int i=0 ; i <= num_of_planets-1 ; i++)
            if (DestroyPlanet(planets[i]) == failure) exit(1);
        if(destroyHashTable(JerryHash) == failure || DestroyList(phyCLinkedList) != List_Success || DestroyList(JerriesID) != List_Success) exit(1);
    }

    if(flag == 3 && planets && JerryHash){
        if(destroyHashTable(JerryHash) != success || DestroyMultiValueHashTable(JerryMVHT) != MVHT_Success
           || DestroyList(phyCLinkedList) != List_Success || DestroyList(JerriesID) != List_Success) exit(1);
        for(int i=0 ; i <= num_of_planets-1 ; i++)
            if (DestroyPlanet(planets[i]) == failure) exit(1);
    }

    if(flag == 4 && planets && JerryHash ) {
        if ((DestroyMultiValueHashTable(JerryMVHT) != MVHT_Success) || destroyHashTable(JerryHash) == failure
        || DestroyList(phyCLinkedList) == failure || DestroyList(JerriesID) == failure)
            exit(1);
        for (int i = 0; i <= num_of_planets -1; i++) {
            if (DestroyPlanet(planets[i]) == failure) {
                free(planets);
                exit(1);
            }
        }
    }
}
/// The next function initialize the data structures from tha main with the information from the file (after reading it already)
MultiVHash InitJerryMVHT(hashTable JerryHash, LinkedList PhycList,LinkedList id_ll, int num_of_Jerries){
    if(! JerryHash || ! PhycList || ! id_ll) return NULL;
    MultiVHash JerryMVHT = CreateMultiValueHashTable(copyPhyMVHT, freePhyMVHT, printPhyMVHT, copyIdMVHT, freeIdMVHT, printIdMVHT,
                                                     equalName, tansformIntoNum, num_of_Jerries);
    int num_of_phyC = GetLengthList(PhycList);
    if(num_of_phyC == 0) return JerryMVHT;
    for(int i = 1 ; i <= num_of_phyC ; i++){
        char* temp_phyc = (char*)GetDataByIndex(PhycList, i);
        if(! temp_phyc) return NULL;
        char* copy_temp_phy = temp_phyc;
        for(int j = 1 ; j <= num_of_Jerries ; j++){
            char* jerryID = (char*)GetDataByIndex(id_ll, j);
            Jerry* temp_jerry = (Jerry*) lookupInHashTable(JerryHash, jerryID);
            if(! temp_jerry) return NULL;
            if(PhyIn(temp_jerry, temp_phyc) == true) {
                if(AddToMultiValueHashTable(JerryMVHT, copy_temp_phy, jerryID) != MVHT_Success) return NULL;
            }
        }
    }
    return JerryMVHT;
}
//// The next function helps to find out if a give physical characteristic is jerry's physical characteristic:
bool PhycInJerry(MultiVHash JerryMVHT, char* phyc, char* j_id){
    if(JerryMVHT == NULL) return false;
    LinkedList temp_j_ls = LookupInMultiValueHashTable(JerryMVHT, phyc);
    if(! temp_j_ls) return false;
    if(SearchByKeyInList(temp_j_ls, j_id) != NULL)
        return true;
    return false;
}
/// The next function prints jerrys by each physical characteristic :
bool PrintJerriesByPhyc(MultiVHash JerryMVHT,hashTable JerryHash, char* phyc){
    if(JerryMVHT == NULL) return false;
    printf("%s : \n", phyc);
    LinkedList JerryLL = LookupInMultiValueHashTable(JerryMVHT, phyc);
    int JerryLLLenght = GetLengthList(JerryLL);
    for(int i = 1 ; i <= JerryLLLenght ; i ++){
        char* j_id = GetDataByIndex(JerryLL, i);
        Jerry* j = lookupInHashTable(JerryHash, j_id);
        if(PrintJerry(j) == failure) return false;
    }
    return true;
}

//// Interface function :
//// No.1:

status AddJerryBoree(MultiVHash JerryMVHT, hashTable JerryHash, LinkedList JerriesID, Planet** planet_arr,
                     LinkedList PhyLinkedList,int num_of_planets){
    if(! JerryHash ||! JerriesID || ! JerryMVHT) return failure;
    char j_ID[SIZE];
    printf("What is your Jerry's ID ? \n");
    scanf("%s", j_ID);
    if(SearchByKeyInList(JerriesID, j_ID) != NULL){
        printf("Rick did you forgot ? you already left him here ! \n");
        return success;
    }
    char j_planet[SIZE];
    printf("What planet is your Jerry from ? \n");
    scanf("%s", j_planet);
    Planet* new_planet = findPlaned(planet_arr, num_of_planets, j_planet);
    if(! new_planet){
        printf("%s is not a known planet ! \n", j_planet);
        return success;
    }

    char j_dimension[SIZE];
    printf("What is your Jerry's dimension ? \n");
    scanf("%s", j_dimension);

    int j_happiness;
    printf("How happy is your Jerry now ? \n");
    scanf("%d", &j_happiness);
    char* id_copy_hash = (char*) calloc(strlen(j_ID) +1, sizeof(char));
    if(! id_copy_hash){
        if(DestroyPlanet(new_planet) == failure) return failure;
        printf("Memory Problem\n");
    }
    strncpy(id_copy_hash,j_ID, strlen(j_ID));
    char* id_copy = id_copy_hash;
    Jerry* newJerry = JerryCreate(j_ID, j_dimension, j_happiness, new_planet);
    if(! newJerry){
        free(id_copy_hash);
        if(DestroyPlanet(new_planet) == failure) return failure;
        printf("Memory Problem\n");
        return failure;
    }
    if(addToHashTable(JerryHash, id_copy_hash, newJerry) != success) {
        free(id_copy_hash);
        if(DestroyPlanet(new_planet) == failure) return failure;
        if(DestroyJerry(newJerry) != success) return failure;
        return failure;
    }
    if(AppendNode(JerriesID, id_copy) != List_Success){
        free(id_copy_hash);
        if(DestroyPlanet(new_planet) == failure) return failure;
        if(DestroyJerry(newJerry) != success) return failure;
        return failure;
    }
    if(PrintJerry(newJerry) != success) return failure;
    char* temp = GetDataByIndex(JerriesID,5);
    return success;
}
/// Finished with No1 option in the interface menu

/// No.2 :
status AddPhycToJerry(MultiVHash JerryMVHT, hashTable JerryHash, LinkedList PhyLinkedList ){
    if(! JerryHash || ! JerryMVHT) return failure;
    char buffer[SIZE];
    printf("What is your Jerry's ID ? \n");
    SCAN_BUFFER;
    char j_ID1[SIZE];
    strcpy(j_ID1, buffer);
    Jerry *j = (Jerry *) lookupInHashTable(JerryHash, j_ID1);
    if(j == NULL){
        printf("Rick this Jerry is not in the daycare ! \n");
        return success;
    }
    printf("What physical characteristic can you add to Jerry - %s ? \n", j_ID1);
    SCAN_BUFFER;
    char j_phy[SIZE];
    strcpy(j_phy, buffer);
    if(PhycInJerry(JerryMVHT, j_phy, j_ID1) == true){
        printf("The information about his %s already available to the daycare ! \n", j_phy);
        return success;
    }
    int j_phy_val;
    printf("What is the value of his %s ? \n", j_phy);
    scanf("%d", &j_phy_val);
    PhysicalChar* newPhyc = PhyCCreate(j_phy, j_phy_val);
    if(! newPhyc){
        printf("Memory Problem\n");
        return failure;
    }
    if(PhyAdd(j, newPhyc) == failure) return failure;
    LinkedList temp = LookupInMultiValueHashTable(JerryMVHT,j_phy);
    if(temp == NULL){
        char* phy_copy = (char*) calloc(strlen(j_phy)+1,sizeof(char));
        if(! phy_copy){
            if(DestroyPhyC(newPhyc) == failure) return failure;
            printf("Memory Problem\n");
            return failure;
        }
        strncpy(phy_copy,j_phy, strlen(j_phy));
        char* phy_copyMVHT = phy_copy;
        if(AddToMultiValueHashTable(JerryMVHT, phy_copy , GetJerryID(j)) != MVHT_Success) return failure;
        if(AppendNode(PhyLinkedList, phy_copy) == failure) return failure;
    }
    else {
        AddToMultiValueHashTable(JerryMVHT, j_phy, GetJerryID(j));
    }
    if(PrintJerriesByPhyc(JerryMVHT, JerryHash, buffer) == false) return failure;
    return success;
}
/// Finished with No2 option in the interface menu

/// No.3 :
status DeletePhycFromJerry(MultiVHash JerryMVHT, hashTable JerryHash) {
    if (!JerryHash || !JerryMVHT) return failure;
    char j_ID[SIZE];
    printf("What is your Jerry's ID ? \n");
    scanf("%s", j_ID);
    Jerry *j = (Jerry *) lookupInHashTable(JerryHash, j_ID);
    if (j == NULL) {
        printf("Rick this Jerry is not in the daycare ! \n");
        return success;
    }
    char j_phyc[SIZE];
    printf("What physical characteristic do you want to remove from Jerry - %s ? \n", j_ID);
    scanf("%s", j_phyc);
    if (PhycInJerry(JerryMVHT, j_phyc, j_ID) == false) {
        printf("The information about his %s not available to the daycare ! \n", j_phyc);
        return success;
    }
    RemoveFromMultiValueHashTable(JerryMVHT, j_phyc, j_ID);
    if(PhyDelete(j, j_phyc) != success) return failure;
    if(PrintJerry(j) == failure) return failure;
    return success;
}
/// Finished with No3 option in the interface menu

/// No.4 :
/// The next function helping to remove Jerry from MVHT:
status RemoveJerryFromMulti(MultiVHash JerryMVHT, LinkedList PhyLinkedList, char* j){
    if(!JerryMVHT || ! PhyLinkedList) return failure;
    int size = GetLengthList(PhyLinkedList);
    if(size == 0) return success;
    for(int i = 1 ; i <= size ;i++){
        char* phy = GetDataByIndex(PhyLinkedList, i);
        RemoveFromMultiValueHashTable(JerryMVHT, phy, j);
    }
    return success;
}

status RemoveJerryFromDaycare(MultiVHash JerryMVHT, hashTable JerryHash,LinkedList PhyLinkedList, LinkedList JerriesID){
    if(! JerryMVHT || ! JerryHash || ! JerriesID) return failure;
    char buffer[SIZE];
    printf("What is your Jerry's ID ? \n");
    SCAN_BUFFER;
    char j_ID[SIZE];
    strcpy(j_ID, buffer);
    Jerry *j = (Jerry *) lookupInHashTable(JerryHash, j_ID);
    if (j == NULL) {
        printf("Rick this Jerry is not in the daycare ! \n");
        return success;
    }
    if(GetJerriesNumOfPhyc(j) == 0){
        if(DeleteNode(JerriesID, j_ID) == List_Failure) return failure;
        if(removeFromHashTable(JerryHash, j_ID) == failure) return failure;
        printf("Rick thank you for using our daycare service ! Your Jerry awaits ! \n");
        return success;
    }
    if(DeleteNode(JerriesID, j_ID) == List_Failure) return failure;
    RemoveJerryFromMulti(JerryMVHT, PhyLinkedList, j_ID);
    if(removeFromHashTable(JerryHash, j_ID) == failure) {
        return failure;
    }
    printf("Rick thank you for using our daycare service ! Your Jerry awaits ! \n");
    return success;
}
/// Finished with No4 option in the interface menu

/// No.5 :
status TakeJerryByPhyc(MultiVHash JerryMVHT, hashTable JerryHash, LinkedList JerriesID, LinkedList PhyLinkedList) {
    if (! JerryHash || ! JerryMVHT || ! PhyLinkedList) return failure;
    char phyc[SIZE];
    printf("What do you remember about your Jerry ? \n");
    scanf("%s", phyc);
    LinkedList j_ll = LookupInMultiValueHashTable(JerryMVHT, phyc);
    if (!j_ll) {
        printf("Rick we can not help you - we do not know any Jerry's %s ! \n", phyc);
        return success;
    }
    int val;
    printf("What do you remember about the value of his %s ? \n", phyc);
    scanf("%d", &val);
    float values[GetLengthList(j_ll)];
    for (int i = 1; i <= GetLengthList(j_ll); i++) {
        char *j_id = GetDataByIndex(j_ll, i);
        Jerry* j = lookupInHashTable(JerryHash, j_id);
        float temp = GetPhycVal(j, phyc);
        values[i - 1] = temp;
    }
    int closer = (int)values[0];
    int min = abs((int)values[0] - val);
    int min_indx = 1;
    for(int j =0 ; j< GetLengthList(j_ll) -1; j++){
        if(min > abs((int)values[j+1] - val) ) {
            min_indx = j+2;
            closer = values[j+1];
        }
    }
    printf("Rick this is the most suitable Jerry we found : \n");
    char *s_j_id = (char*) GetDataByIndex(j_ll, min_indx);
    Jerry* j = lookupInHashTable(JerryHash, s_j_id);
    if(PrintJerry(j) == failure) return failure;
    if(DeleteNode(JerriesID, s_j_id) == List_Failure) return failure;
    if(RemoveJerryFromMulti(JerryMVHT, PhyLinkedList, s_j_id) != success) return failure;
    if(removeFromHashTable(JerryHash, s_j_id) == failure) return failure;
    printf("Rick thank you for using our daycare service ! Your Jerry awaits ! \n");
    return success;
}
/// Finished with No.5 option in the interface menu

//// No.6 :
status TakeJerryBySad(MultiVHash JerryMVHT, hashTable JerryHash, LinkedList JerriesID, LinkedList PhyLinkedList){
    if (!JerryHash || !JerryMVHT || ! JerriesID) return failure;
    if(GetLengthList(JerriesID) == 0){
        printf("Rick we can not help you - we currently have no Jerries in the daycare ! \n");
        return success;
    }
    int len = GetLengthList(JerriesID);
    int happiness_Arr[len];
    for(int i = 1 ; i <= len; i++){
        Jerry* j = lookupInHashTable(JerryHash, GetDataByIndex(JerriesID, i));
        int j_happiness = GetJerryHappiness(j);
        happiness_Arr[i-1] = j_happiness;
    }
    int min = happiness_Arr[0];
    int min_indx = 1;
    for(int j = 0 ; j < len -1 ; j ++){
        if(min > happiness_Arr[j+1]){
            min = happiness_Arr[j+1];
            min_indx = j+2;
        }
    }
    Jerry* saddest_j = lookupInHashTable(JerryHash, GetDataByIndex(JerriesID, min_indx));
    printf("Rick this is the most suitable Jerry we found : \n");
    if(PrintJerry(saddest_j) == failure) return failure;
    //// Now delete Jerry from all of our Data structures :
    if(DeleteNode(JerriesID, GetJerryID(saddest_j)) == failure) return failure;
    if(RemoveJerryFromMulti(JerryMVHT, PhyLinkedList, GetJerryID(saddest_j)) == failure) return failure;
    if(removeFromHashTable(JerryHash, GetJerryID(saddest_j)) == failure) return failure;
    ////
    printf("Rick thank you for using our daycare service ! Your Jerry awaits ! \n");
    return success;
}
/// Finished with No.6 option in the interface menu

//// No.7 :
static status PrintJerries(hashTable JerryHash, LinkedList JerriesID){
    if(! JerryHash || ! JerriesID) return failure;
    for(int i = 1 ; i <= GetLengthList(JerriesID) ; i++){
        if(PrintJerry(lookupInHashTable(JerryHash, GetDataByIndex(JerriesID, i))) == failure) return failure;
    }
    return success;
}
static status PrintPlanetsMain(Planet** planet_arr, int num_of_planets){
    if(! planet_arr) return failure;
    for(int i = 0 ; i < num_of_planets ; i++){
        if(PrintPlanet(planet_arr[i]) == failure) return failure;
    }
    return success;
}
status ShowMeWhatYouGot(MultiVHash JerryMVHT, hashTable JerryHash, LinkedList JerriesID, Planet** planet_arr, LinkedList PhyLinkedList, int num_of_planets) {
    if (!JerryHash || !JerryMVHT || !planet_arr || !JerriesID) return failure;
    char buffer[SIZE];
    PRINT_7_MENU;
    char input[SIZE];
    char temp;
    scanf("%s", input);
    temp = input[0];
    if(strlen(input) != 1)
        temp = 'a';
    switch (temp) {
        case '1':
            if (GetLengthList(JerriesID) == 0) {
                printf("Rick we can not help you - we currently have no Jerries in the daycare ! \n");
                return success;
            }
            if (PrintJerries(JerryHash, JerriesID) == failure) return failure;
            return success;
        case '2':
            printf("What physical characteristics ? \n");
            scanf("%s", buffer);
            char *phyC_name = (char *) malloc(strlen(buffer) + 1);
            if (!phyC_name) {
                printf("Memory problem\n");
                return failure;
            }
            strcpy(phyC_name, buffer);
            char* phyc = SearchByKeyInList(PhyLinkedList, phyC_name);
            if (!phyc || GetLengthList(JerriesID) == 0 || GetLengthList(LookupInMultiValueHashTable(JerryMVHT,phyc)) < 0) {
                printf("Rick we can not help you - we do not know any Jerry's %s ! \n", phyC_name);
                free(phyC_name);
                return success;
            }
            LinkedList j_by_phyc = LookupInMultiValueHashTable(JerryMVHT, phyC_name);
            printf("%s : \n", phyC_name);
            for (int i = 1; i <= GetLengthList(j_by_phyc); i++) {
                if(PrintJerry(lookupInHashTable(JerryHash, GetDataByIndex(j_by_phyc, i))) == failure) return failure;
            }
            free(phyC_name);
            return success;
        case '3':
            if (PrintPlanetsMain(planet_arr, num_of_planets) == failure) {
                return failure;
            }
            return success;
        default:
            printf("Rick this option is not known to the daycare ! \n");
            return success;
    }
}
/// Finished with No.7 option in the interface menu

/// helper function:
static void NoJerries(){
    printf("Rick we can not help you - we currently have no Jerries in the daycare ! \n");
}

/// No.8 :
static status InteractWithFakeBeth(hashTable JerryHash, LinkedList JerriesID) {
    if (!JerriesID || !JerryHash) return failure;
    int num_of_jerries = GetLengthList(JerriesID);
    if (num_of_jerries == 0) {
        NoJerries();
        return success;
    }
    for (int i = 1; i <= num_of_jerries; i++) {
        Jerry *j = lookupInHashTable(JerryHash, GetDataByIndex(JerriesID, i));
        int j_happiness = GetJerryHappiness(j);
        if (j_happiness >= 20) {
            if (j_happiness + 15 > 100) {
                if (SetJerryHappiness(j, 100) == failure) return failure;
                continue;
            }
            if(AddToJerryHappiness(j, 15) == failure) return failure;
            continue;
        } else {
            if (j_happiness - 5 < 0) {
                if (SetJerryHappiness(j, 0) == failure) return failure;
                continue;
            }
            if (SubstractJerryHappiness(j, 5) == failure) return failure;
            continue;
        }
    }
    return success;
}

static status PlayGolf(hashTable JerryHash, LinkedList JerriesID) {
    if (!JerriesID || !JerryHash) return failure;
    int num_of_jerries = GetLengthList(JerriesID);
    if (num_of_jerries == 0) {
        NoJerries();
        return success;
    }
    for (int i = 1; i <= num_of_jerries; i++) {
        Jerry *j = lookupInHashTable(JerryHash, GetDataByIndex(JerriesID, i));
        int j_happiness = GetJerryHappiness(j);
        if (j_happiness >= 50) {
            if (j_happiness + 10 > 100) {
                if (SetJerryHappiness(j, 100) == failure) return failure;
                continue;
            }
            if (AddToJerryHappiness(j, 10) == failure) return failure;
            continue;
        } else {
            if (j_happiness - 10 < 0) {
                if (SetJerryHappiness(j, 0) == failure) return failure;
                continue;
            }
            if (SubstractJerryHappiness(j, 10) == failure) return failure;
            continue;
        }
        return success;
    }
}

static status AdjustThePicture(hashTable JerryHash, LinkedList JerriesID) {
    if (!JerriesID || !JerryHash) return failure;
    int num_of_jerries = GetLengthList(JerriesID);
    if (num_of_jerries == 0) {
        NoJerries();
        return success;
    }
    for (int i = 1; i <= num_of_jerries; i++) {
        Jerry *j = lookupInHashTable(JerryHash, GetDataByIndex(JerriesID, i));
        int j_happiness = GetJerryHappiness(j);
        if(j_happiness + 20 > 100) {
            if(SetJerryHappiness(j, 100) == failure) return failure;
            continue;
        }
        if(AddToJerryHappiness(j, 20) == failure) return failure;
    }
    return success;
}

status PlayWithJerries(hashTable JerryHash, LinkedList JerryID){
    if(! JerryHash ||  ! JerryID) return failure;
    char buffer[SIZE];
    char input[SIZE];
    char temp;
    if(GetLengthList(JerryID) == 0){
        printf("Rick we can not help you - we currently have no Jerries in the daycare ! \n");
        return success;
    }
    PRINT_8_MENU;
    scanf("%s", input);
    temp = input[0];
    if(strlen(input) != 1)
        temp = 'a';
    switch (temp) {
        case '1':
            if(InteractWithFakeBeth(JerryHash, JerryID) == failure) return failure;
            printf("The activity is now over ! \n");
            if(PrintJerries(JerryHash, JerryID) == failure) return failure;
            return success;
        case '2':
            if(PlayGolf(JerryHash, JerryID) == failure) return failure;
            printf("The activity is now over ! \n");
            if(PrintJerries(JerryHash, JerryID) == failure) return failure;
            return success;
        case '3':
            if(AdjustThePicture(JerryHash, JerryID) == failure) return failure;
            printf("The activity is now over ! \n");
            if(PrintJerries(JerryHash, JerryID) == failure) return failure;
            return success;
        default:
            printf("Rick this option is not known to the daycare ! \n");
            return success;
    }
}
/// Finished with No.8 option in the interface menu


/// The next function help to find the number of jerries in the file.
/// That number is the hash size.
static int FindJerryNumber(FILE* f, int num_of_planets){
    int num_of_jerries = 0;
    char* tab = "\t";
    char line[SIZE];
    char *temp_arr;
    char delim[] = " :,\n\r";  // eliminate those characters !
    if (f == NULL) exit(0);
    fgets(line, sizeof(line), f);
    for (int i = 0; i < num_of_planets; i++)
        fgets(line, sizeof(line), f);
    fgets(line, sizeof(line), f); /// reads the line "Jerries" from the file
    while(1) {
        if( !fgets(line, sizeof(line), f)) break;
        char *temp = strtok(line, delim);
        char* substring = strstr(temp, tab);
        if(substring != NULL)
            continue;
        else num_of_jerries++;
    }
    return num_of_jerries;
}

int main(int argc, char* argv[]) {
    int num_of_planets;
    num_of_planets = atoi(argv[1]);

    //// The data sructures for the project : (See ReadMe for more explanation)
    hashTable JerryHash;
    MultiVHash JerryMVHT;
    LinkedList PhyLinkedList;
    LinkedList JerriesID;

    Planet **planet_arr = (Planet **) malloc((num_of_planets) * sizeof(Planet *));
    if (!planet_arr) {
        printf("Memory Problem\n");
        exit(1);
    }
    int num_of_jerries = 0;
    char line[SIZE];
    char *temp_arr;
    char delim[] = " :,\t\n\r";  /// eliminates those characters !
    FILE *f1 = fopen(argv[2], "r");
    num_of_jerries = FindJerryNumber(f1, num_of_planets);
    fclose(f1);
    FILE *f = fopen(argv[2], "r");
    if (f == NULL) exit(0);
    fgets(line, sizeof(line), f);

    //// Creatint planets_arr:
    char buffer[SIZE];
    int i;
    for (i = 0; i < num_of_planets; i++) {
        fgets(line, sizeof(line), f);
        char *arr[4];
        int k = 0;
        char *token = strtok(line, delim);
        while (token) {
            arr[k] = (char *) malloc(strlen(token) + 1);
            if (!arr[k]) {
                printf("Memory Problem\n");
                FINISH_SCRIPT_1;
            }
            strcpy(arr[k], token);
            k++;
            token = strtok(NULL, delim);
        }
        planet_arr[i] = PlanetCreate(arr[0], atof(arr[1]), atof(arr[2]), atof(arr[3]));
        for (int p = 0; p < 4; p++) { //// free the array for the next planet (if there are one)
            free(arr[p]);
        }
        if (planet_arr[i] == NULL) FINISH_SCRIPT_1;
    }

    //// finished with planets_arr/
    //// Creating data strunctures for the task : (Explanation in ReadMe)
    JerriesID = CreateLinkedList(copyID_LL, freeID_LL, equalName, printID_LL);
    if (!JerriesID)
        finish_script(JerryMVHT, JerryHash, planet_arr, PhyLinkedList, JerriesID, num_of_planets, 1);

    PhyLinkedList = CreateLinkedList(copyPhyc, freePhyc, equalName, printPhyc);
    if (!PhyLinkedList) finish_script(JerryMVHT, JerryHash, planet_arr, PhyLinkedList, JerriesID, num_of_planets, 1);

    JerryHash = createHashTable(copyID, freeID, printID, copyJerry, freeJerry, printJerry,
                                equalName, tansformIntoNum, num_of_jerries);
    if (!JerryHash) finish_script(JerryMVHT, JerryHash, planet_arr, PhyLinkedList, JerriesID, num_of_planets, 1);

    //// reads Jerries from file :
    fgets(line, SIZE, f); //// reads the line "Jerries"
    int flag = 1;

    while (1) { //// iterate until the end of the file.
        if (flag == 1) {
            if (!fgets(line, sizeof(line), f))
                break;
        }
        char *id = strtok(line, delim);
        char *origin_name = strtok(NULL, delim);

        Planet *J_planet = findPlaned(planet_arr, num_of_planets, strtok(NULL, delim));
        if (!J_planet) FINISH_SCRIPT_2;

        int happiness = atoi(strtok(NULL, delim));
        Jerry *temp_jerry = JerryCreate(id, origin_name, happiness, J_planet);
        char *copy_id_hash = (char *) calloc(strlen(id) + 1, sizeof(char));
        if (!copy_id_hash) {
            DestroyJerry(temp_jerry);
            printf("Memory Problem\n");
            FINISH_SCRIPT_2;
        }
        strncpy(copy_id_hash, id, strlen(id));
        if (addToHashTable(JerryHash, copy_id_hash, temp_jerry) == failure) FINISH_SCRIPT_2;
        char *id_ll = copy_id_hash;
        if(AppendNode(JerriesID, id_ll) == failure) FINISH_SCRIPT_2;

        //// now, initial the phyC for the last jerry that added.
        //// also, initialize PhycLinkedList that holds all of the physical characteristics that
        //// available.

        int count = 0;
        while (1) {
            flag = 0;
            if (!fgets(line, sizeof(line), f)) {
                flag = 1;
                break;
            }
            temp_arr = (char *) malloc(strlen(line) + 1);
            if (!temp_arr) {
                printf("Memory Problem\n");
                free(copy_id_hash);
                FINISH_SCRIPT_2;
            }
            strcpy(temp_arr, line);
            char *temp_check = strtok(temp_arr, delim);
            while (temp_check) {
                count++;
                temp_check = strtok(NULL, delim);
            }
            if (count == 2) { /// if true, it means that it is a physical characteristic
                char *phyC = strtok(line, delim);
                float value = atof(strtok(NULL, delim));
                PhysicalChar *phyCharacteristic = PhyCCreate(phyC, value);
                if (!phyCharacteristic) FINISH_SCRIPT_2;
                if (PhyAdd(temp_jerry, phyCharacteristic) == failure) FINISH_SCRIPT_2;
                if (SearchByKeyInList(PhyLinkedList, phyC) == NULL) {
                    char *phyCopy = (char *) calloc(strlen(phyC) + 1, sizeof(char));
                    if (!phyCopy) {
                        printf("Memory Problem\n");
                        free(copy_id_hash);
                        free(temp_arr);
                        FINISH_SCRIPT_2;
                    }
                    strncpy(phyCopy, phyC, strlen(phyC));
                    if (AppendNode(PhyLinkedList, phyCopy) != List_Success) FINISH_SCRIPT_2;
                }
                count = 0;
            } else {
                free(temp_arr);
                break;
            }
            free(temp_arr);
        }
    }
    fclose(f);

    //// finished creating JerriesLinkedList.
    //// Initialize JerryMVHT & JerryHash :
    JerryMVHT = InitJerryMVHT(JerryHash, PhyLinkedList, JerriesID, num_of_jerries);

    //// Interface menu:
    char input[SIZE];
    while (true) {
        char temp;
        printf("Welcome Rick, what are your Jerry's needs today ? \n");
        printf("1 : Take this Jerry away from me \n");
        printf("2 : I think I remember something about my Jerry \n");
        printf("3 : Oh wait. That can't be right \n");
        printf("4 : I guess I will take back my Jerry now \n");
        printf("5 : I can't find my Jerry. Just give me a similar one \n");
        printf("6 : I lost a bet. Give me your saddest Jerry \n");
        printf("7 : Show me what you got \n");
        printf("8 : Let the Jerries play \n");
        printf("9 : I had enough. Close this place \n");
        scanf(" %s", input);
        temp = input[0];
        if(strlen(input) != 1)
            temp = 'a';

        switch (temp) {
            case '1':
                if (AddJerryBoree(JerryMVHT, JerryHash, JerriesID, planet_arr, PhyLinkedList, num_of_planets) ==
                    failure)
                    FINISH_SCRIPT_3;
                break;
            case '2':
                if (AddPhycToJerry(JerryMVHT, JerryHash, PhyLinkedList) == failure)
                    FINISH_SCRIPT_3;
                break;
            case '3':
                if (DeletePhycFromJerry(JerryMVHT, JerryHash) == failure)
                    FINISH_SCRIPT_3;
                break;
            case '4':
                if (RemoveJerryFromDaycare(JerryMVHT, JerryHash, PhyLinkedList, JerriesID) == failure)
                    FINISH_SCRIPT_3;
                break;
            case '5':
                if (TakeJerryByPhyc(JerryMVHT, JerryHash, JerriesID, PhyLinkedList) == failure)
                    FINISH_SCRIPT_3;
                break;
            case '6':
                if (TakeJerryBySad(JerryMVHT, JerryHash, JerriesID, PhyLinkedList) == failure)
                    FINISH_SCRIPT_3;
                break;
            case '7':
                if (ShowMeWhatYouGot(JerryMVHT, JerryHash, JerriesID, planet_arr,PhyLinkedList,  num_of_planets) == failure)
                    FINISH_SCRIPT_3;
                break;
            case '8':
                if (PlayWithJerries(JerryHash, JerriesID) == failure)
                    FINISH_SCRIPT_3;
                break;
            case '9':
                FINISH_SCRIPT_4;
                free(planet_arr);
                printf("The daycare is now clean and close ! \n");
                exit(0);
            default:
                printf("Rick this option is not known to the daycare ! \n");
                break;
        }
    }
}
