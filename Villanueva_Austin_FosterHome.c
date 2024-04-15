// 2ND TRY


// file headers
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// helpful definitions
#define STRING_SIZE 100
#define NUM_DAYS 7
#define NUM_FAMILIES 3

// structs that hold info for each family
typedef struct family{
    char * cat; // cat name
    char * suffix; // family suffix
    int last; // cat return position
    int position; // family current position
    int position_move; // how much the family moves after each pickup
}family;

// function that initializes the families and their data to the correct info
void init_families(family * families){
    families[0].cat = (char*)malloc(sizeof(char) * STRING_SIZE);
    strcpy(families[0].cat, "empty");
    families[0].suffix = (char*)malloc((sizeof(char) * strlen("lee")) + 1);
    strcpy(families[0].suffix, "Lee");
    families[0].position = 0;
    families[0].position_move = 2;

    families[1].cat = (char*)malloc(sizeof(char) * STRING_SIZE);
    strcpy(families[1].cat, "empty");
    families[1].suffix = (char*)malloc((sizeof(char) * strlen("lyn")) + 1);
    strcpy(families[1].suffix, "Lyn");
    families[1].position = 1;
    families[1].position_move = 3;

    families[2].cat = (char*)malloc(sizeof(char) * STRING_SIZE);
    strcpy(families[2].cat, "empty");
    families[2].suffix = (char*)malloc((sizeof(char) * strlen("eve")) + 1);
    strcpy(families[2].suffix, "Eve");
    families[2].position = 2;
    families[2].position_move = 5;
}

// main function
int main(){
    // array of structs for each family
    family * families = (family*)malloc(sizeof(family) * NUM_FAMILIES);

    // initializes the families info
    init_families(families);

    // variables to store the number of cats and the number of weeks to be executed
    int num_cats, num_weeks;
    // takes input
    scanf("%d %d", &num_cats, &num_weeks);

    // allocates memory for an array to take in all the cats names
    char ** cat_array = (char**)malloc(sizeof(char*) * num_cats);
    for(int i = 0; i < num_cats; i++){
        cat_array[i] = (char*)malloc(sizeof(char) * STRING_SIZE);
    }

    // takes input
    for(int i = 0; i < num_cats; i++){
        scanf("%s", cat_array[i]);
    }

    // simulates the passing of time
    for(int week = 0; week < num_weeks; week++){
        // iterates through all the famalies
        for(int counter = 0; counter < NUM_FAMILIES; counter++){
            
            // drop off cat
            if(strcmp(families[counter].cat, "empty") != 0){
                strcpy(cat_array[families[counter].last], families[counter].cat);
                strcpy(families[counter].cat, "empty");
            }

            // pick up cat
            if(strcmp(families[counter].cat, "empty") == 0 && strcmp(cat_array[families[counter].position], "empty") != 0){
                strcpy(families[counter].cat, cat_array[families[counter].position]);
                strcat(families[counter].cat, families[counter].suffix);
                strcpy(cat_array[families[counter].position], "empty");
                families[counter].last = families[counter].position;
            }

            // move position, reset if out of bounds
            families[counter].position = (families[counter].position + families[counter].position_move) % num_cats;   
        }
    }

    // prints final results
    for(int i = 0; i < num_cats; i++){
        if(strcmp(cat_array[i], "empty") == 0){
            printf("no cat found.\n");
        }
        else{
            printf("%s\n", cat_array[i]);
        }
    }

    // free allocated memory
    for(int i = 0; i < NUM_FAMILIES; i++){
        free(families[i].cat);
        free(families[i].suffix);
    }
    free(families);
    for(int i = 0; i < num_cats; i++){
        free(cat_array[i]);
    }
    free(cat_array);

    return 0;
}
