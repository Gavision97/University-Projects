#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include  "Defs.h"
#include "Jerry.h"
#include <unistd.h>
#include <ctype.h>

void MemoryProblem(){
    printf("Memory Problem\n");
    exit(0);
}
// The next function helps the main to find the correct planet due to its string name :
Planet* findPlaned(Planet** planetArr, int num_of_planets, char* SplanetName) {
    int index;
    for(index = 0 ; index < num_of_planets ; index++) {
        int result = strcmp(planetArr[index] ->planetName, SplanetName);
        if(result == 0) return planetArr[index]; // return the correct planet structure !!
    }
    return NULL;
}

Jerry* findJerry(Jerry** jerryArr, int num_of_jerries, char* sJerryName){
    int index;
    for(index = 0 ; index < num_of_jerries ; index++) {
        int result = strcmp(jerryArr[index]->ID, sJerryName);
        if (result == 0) return jerryArr[index];
    }
    return NULL;
}
char* ToUpperFunc(char* word){
    int i = 0;
    while(word[i]){
        word[i] = toupper(word[i]);
        i++;
    }
    return word;
}
// CASE 3
// The next function help the main function to add physical characteristic to Jerry.
status AddPhyC_main(Jerry** jerriesA, int num_of_jerries){
    if(num_of_jerries == 0 ) return  failure;
    PhysicalChar* phyC_to_add = NULL;
    char buffer[300];
    printf("What is your Jerry's ID ?\n");
    scanf("%s", buffer);
    Jerry* tempJ = findJerry(jerriesA, num_of_jerries, buffer);
    if( tempJ == NULL){
        printf("OH NO! I CAN'T FIND HIM RICK !\n");
        return success; // which means return to the main interface menu
    }
    else{
        printf("What physical characteristic can you add to Jerry - %s ?\n", tempJ ->ID);
        scanf("%s", buffer);
        char* phyC = (char *) malloc(strlen(buffer)+1);
        if(! phyC) MemoryProblem();
        strcpy(phyC, buffer);
        if(PhyIn(tempJ, phyC) == true){
            phyC = ToUpperFunc(phyC);
            printf("RICK I ALREADY KNOW HIS %s !\n", phyC);
            free(phyC);
            return success; // which means return to the main interface menu
        }
        // else, which means there is no such physical characteristic in Jerry.
        float val;
        printf("What is the value of his %s ?\n", phyC);
        scanf("%f", &val);
        phyC_to_add = PhyCCreate(phyC, val);
        if(PhyAdd(tempJ, phyC_to_add) == failure) return  failure ; // failed to add that physical characteristic to Jerry !
        free(phyC);
        PrintJerry(tempJ);
    }
    return success;
}
// CASE 4
status delete_main(Jerry** jerriesA,int num_of_jerries) {
    if(num_of_jerries == 0 ) return  failure;
    char buffer[300];
    printf("What is your Jerry's ID ?\n");
    scanf("%s", buffer);
    Jerry* tempJ = findJerry(jerriesA, num_of_jerries, buffer);
    if (tempJ == NULL) {
        printf("OH NO! I CAN'T FIND HIM RICK !\n");
        return success; // which means return to the main interface menu
    }
    printf("What physical characteristic do you want to remove from Jerry - %s ?\n", tempJ->ID);
    scanf("%s", buffer);
    char* phyC = (char *) malloc(strlen(buffer)+1);
    if(! phyC) MemoryProblem();
    strcpy(phyC, buffer);
    if(PhyIn(tempJ, phyC) == false){
        // convert phyC to upper case :
        phyC = ToUpperFunc(phyC);
        printf("RICK I DON'T KNOW HIS %s !\n", phyC);
        free(phyC);
        return success; // which means return to the main interface menu
    }
    if(PhyDelete(tempJ, phyC) == failure) return  failure;
    free(phyC);
    PrintJerry(tempJ);
    return success;
}

// CASE 5
status PrintJplanet(Jerry** jerriesA,Planet** planetA, int num_of_jerries, int num_of_planets){
    if(num_of_jerries == 0) return failure;
    char buffer[300];
    printf("What planet is your Jerry from ?\n");
    scanf("%s", buffer);
    char* planetName = (char *)malloc(strlen(buffer) + 1);
    if(! planetName) MemoryProblem();

    strcpy(planetName,buffer);
    if(! planetName) return failure;
    Planet* planetT = findPlaned(planetA, num_of_planets, planetName);
    if (! planetT) {
        planetName = ToUpperFunc(planetName);
        printf("RICK I NEVER HEARD ABOUT %s !\n", planetName);
        free(planetName);
        return success;
    }
    // now try to print all the jerry's that comes from that plant !
    int counter = 0;
    for(int i = 0 ; i < num_of_jerries ; i++){
        if(strcmp(jerriesA[i] ->planet ->planetName, planetName) == 0 ){
            if(PrintJerry(jerriesA[i]) == failure) return failure;
            counter ++ ;
            continue;
        }
    }
    if(counter == 0){
        planetName = ToUpperFunc(planetName);
        printf("OH NO! I DON'T KNOW ANY JERRIES FROM %s !\n", planetName);
        free(planetName);
        return success;
    }
    free(planetName);
    return success;
}

// CASE 6
status PrintJphyC(Jerry** jerriesA, int num_of_jerries){
    if(num_of_jerries == 0) return failure;
    char buffer[300];
    int counter = 0;
    printf("What do you know about your Jerry ?\n");
    scanf("%s", buffer);
    char* phyC = (char*)malloc(sizeof(buffer)+ 1 );
    if(! phyC) MemoryProblem();

    strcpy(phyC, buffer);
    if(! phyC) return failure;
    for( int i = 0 ; i < num_of_jerries ; i++){
        if(PhyIn(jerriesA[i], phyC) == true){
            if(PrintJerry(jerriesA[i]) == failure) return failure;
            counter ++;
        }
    }
    if(counter == 0) {
        phyC = ToUpperFunc(phyC);
        printf("OH NO! I DON'T KNOW ANY JERRY'S %s !\n", phyC);
        free(phyC);
        return success;
    }
    free(phyC);
    return success;
}

void finish_script(Jerry** jerries, Planet** planets, int num_of_jerries, int num_of_planets, int flag ) {
    for(int i=0 ; i <= num_of_jerries-1; i++ ){
        DestroyJerry(jerries[i]);
    }
    for(int i=0 ; i <= num_of_planets-1 ; i++) {
        DestroyPlanet(planets[i]);
    }
    if(flag){ // In case the program crashed due to memory leak.
        printf("Memory  problem\n");
        exit(1);
    }
}
int main(int argc, char* argv[]) {
    unsigned int num_of_jerryies, num_of_plannets;
    num_of_plannets = atoi(argv[1]);
    num_of_jerryies = atoi(argv[2]);

    Jerry **jerry_arr = (Jerry **) malloc((num_of_jerryies) * sizeof(Jerry *));
    Planet **planet_arr = (Planet **) malloc((num_of_plannets) * sizeof(Planet *));
    char line[SIZE];
    char *temp_arr;
    char delim[] = " :,\t\n\r";  // eliminate those characters !
    FILE *f = fopen(argv[3], "r");
    if (f == NULL) exit(0);
    fgets(line, SIZE, f);

    // create planets:
    char buffer[SIZE];
    int i;
    for (i = 0; i < num_of_plannets; i++) {
        fgets(line, sizeof(line), f);
        char *arr[4];
        int k = 0;
        char *token = strtok(line, delim); // planet gets planet name from the file.
        while (token) {
            arr[k] = (char *) malloc(strlen(token) + 1);
            if(! arr[k]) finish_script(jerry_arr, planet_arr, 0, i, 1);
            strcpy(arr[k], token);
            k++;
            token = strtok(NULL, delim);
        }
        planet_arr[i] = PlanetCreate(arr[0], atof(arr[1]), atof(arr[2]), atof(arr[3]));
        for (int p = 0; p < 4; p++) { // free the array for the next planet (if there are one)
            free(arr[p]);
        }
        if (planet_arr[i] == NULL) finish_script(jerry_arr, planet_arr, 0, i, 1);
    }

    // jerry create :
    fgets(line, SIZE, f); // reads the line "Jerries"
    fgets(line, SIZE, f);
    fgets(line, SIZE, f);

    char *id = strtok(line, delim); // reads the first jerry ( in case there are one - else will be NULL)
    for (int j = 0; j <= num_of_jerryies - 1; j++) { // initialize each jerry according to the number of them
        char *origin_name = strtok(NULL, delim);
        Planet *planet = findPlaned(planet_arr, num_of_plannets, strtok(NULL, delim));
        int happiness = atoi(strtok(NULL, delim));
        jerry_arr[j] = JerryCreate(id, origin_name, happiness, planet);

        // initialize jerries physical characteristics (in case there are)
        int count = 0;
        while (1) {
            fgets(line, sizeof(line), f);
            temp_arr = (char *) malloc(strlen(line) + 1);
            if(! temp_arr) finish_script(jerry_arr, planet_arr, j, num_of_plannets, 1);
            strcpy(temp_arr, line);
            char *temp_check = strtok(temp_arr, delim);
            while (temp_check) {
                count++;
                temp_check = strtok(NULL, delim);
            }
            if (count == 2) {
                char *phyC = strtok(line, delim);
                float value = atof(strtok(NULL, delim));
                PhysicalChar *phyCharactistic = PhyCCreate(phyC, value);
                PhyAdd(jerry_arr[j], phyCharactistic);
                count = 0;
            } else{
              free(temp_arr);
                break;
            }
            free(temp_arr);
        }

        // now when finished reading all jerries information, next step is really create one.
        if (jerry_arr[j] == NULL) finish_script(jerry_arr, planet_arr, j, num_of_plannets, 1);
        id = strtok(line, delim);
    }
    fclose(f); // finished reading from the file all the details!!


    // Interface manu :
    char input = 'q'; // temp value so that no issues will happen !
    while (input != 7) {
        char temp;
        int count = 0;
        printf("AW JEEZ RICK, what do you want to do now ?\n");
        printf("1 : Print all Jerries\n");
        printf("2 : Print all Planets\n");
        printf("3 : Add physical characteristic to Jerry\n");
        printf("4 : Remove physical characteristic from Jerry\n");
        printf("5 : Print Jerries by a planet\n");
        printf("6 : Print Jerries by a physical characteristic\n");
        printf("7 : Go home\n");
        scanf(" %c", &input);
        temp = input;
        while(temp != '\n'){
            temp = getchar();
            count++;
        }
        if(count != 1) {
            printf("RICK WE DON'T HAVE TIME FOR YOUR GAMES !\n");
            continue;
        }
        int k;
        switch (input) {
            case '1':
                for (k = 0; k < num_of_jerryies; k++) {
                    PrintJerry(jerry_arr[k]);
                }
                break;
            case '2':
                for (k = 0; k < num_of_plannets; k++) {
                    PrintPlanet(planet_arr[k]);
                }
                break;
            case '3':
                if (AddPhyC_main(jerry_arr, num_of_jerryies) == failure) {
                    finish_script(jerry_arr, planet_arr, num_of_jerryies, num_of_plannets, 1);
                }
                break;
            case '4':
                if (delete_main(jerry_arr, num_of_jerryies) == failure) {
                    finish_script(jerry_arr, planet_arr, num_of_jerryies, num_of_plannets, 1);
                }
                break;
            case '5':
                if (PrintJplanet(jerry_arr, planet_arr, num_of_jerryies, num_of_plannets) == failure) {
                    finish_script(jerry_arr, planet_arr, num_of_jerryies, num_of_plannets, 1);
                }
                break;
            case '6':
                if (PrintJphyC(jerry_arr, num_of_jerryies) == failure) {
                    finish_script(jerry_arr, planet_arr, num_of_jerryies, num_of_plannets, 1);
                }
                break;
            case '7':
                finish_script(jerry_arr, planet_arr, num_of_jerryies, num_of_plannets, 0);
                free(jerry_arr);
                free(planet_arr);
                printf("AW JEEZ RICK, ALL THE JERRIES GOT FREE !");
                exit(0);
            default:
                printf("RICK WE DON'T HAVE TIME FOR YOUR GAMES !\n");
                break;
        }
    }
}