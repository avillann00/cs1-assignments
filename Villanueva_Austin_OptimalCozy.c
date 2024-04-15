#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// the number of houses
#define NUM_HOUSES 3   

// global variables for the final answers
int most_cozy_sum;
int most_least_cozy = INT_MIN;

// holds input for the number of cats
int num_cats;

// recursive function
void combination(int house_cozy[num_cats][NUM_HOUSES], int change_cozy[num_cats][num_cats], int * houses, int index){

    // base case
    if(index == num_cats){

        // check to make sure each house is selected at least once
        int flag1 = 0;
        int flag2 = 0; 
        int flag3 = 0;
        for(int i = 0; i < num_cats; i++){
            if(houses[i] == 0) flag1 = 1;
            if(houses[i] == 1) flag2 = 1;
            if(houses[i] == 2) flag3 = 1;
        }
        if(flag1 == 0 || flag2 == 0 || flag3 == 0) return;

        // temp variable to add the coziness and compare to the global variable
        int temp = 0;
        // variable to keep track of the lowest for each combination
        int lowest = INT_MAX;

        for(int i = 0; i < num_cats; i++){
            // variable to keep track of each individual cat to compare to the lowest global variable
            int cat = 0;

            // base coziness
            cat += house_cozy[i][houses[i]];

            // altered coziness
            for(int j = 0; j < num_cats; j++){
                if(j == i) continue; // the same cat
                if(houses[i] == houses[j]){
                    cat += change_cozy[i][j];
                }
            }

            // adds to the total coziness
            temp += cat;
            // lowest current combination check
            if(cat < lowest){
                lowest = cat;
            }
        }
        
        // global variable check
        if(lowest > most_least_cozy){
            most_least_cozy = lowest;
        }
        // global variable check
        if(temp > most_cozy_sum){
            most_cozy_sum = temp;
        }
        return;
    }

    // recursive call
    for(int i = 0; i < NUM_HOUSES; i++){
        houses[index] = i;
        combination(house_cozy, change_cozy, houses, index + 1);
    }
}

// main function
int main(){
    // takes input
    scanf("%d", &num_cats);

    // array that keeps track of where the cats are
    int houses[num_cats];

    // arrays to store the input values
    int house_cozy[num_cats][NUM_HOUSES];
    int change_cozy[num_cats][num_cats];

    // takes input for the cats initial coziness based on the house
    for(int i = 0; i < num_cats; i++){
        for(int j = 0; j < NUM_HOUSES; j++){
            scanf("%d", &house_cozy[i][j]);
        }
    }

    // takes input for the cats coziness based on the other cats present
    for(int i = 0; i < num_cats; i++){
        for(int j = 0; j < num_cats; j++){
            scanf("%d", &change_cozy[i][j]);
        }
    }

    // function call
    combination(house_cozy, change_cozy, houses, 0);

    // print final result
    printf("%d %d\n", most_cozy_sum, most_least_cozy);

}
