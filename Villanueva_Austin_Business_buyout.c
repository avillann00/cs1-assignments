#include <stdio.h>
#include <stdlib.h>

// stack node structure
typedef struct node{
    long int wealth;
    struct node * next;
}node;

// stack structure to be purchased
typedef struct stack{
    node * head;
}stack;

node * create_shop(int wealth);
void push(stack * to_purchase, int wealth);
int pop(stack * to_purchase);
void merge_sort(int * shops, int num_shops);
void delete_stack(stack * to_purchase);
long int find_turning(int * shops, int bts, int num_shops, stack * to_purchase);

int main(){
    // the number of shops
    long int num_shops;
    // the wealth of the BTS shop
    long int bts;
    // stack that holds the to be purchased
    stack * to_purchase = (stack*)malloc(sizeof(stack));

    // scans input
    scanf("%ld %ld", &num_shops, &bts);

    // each wealth for the shops in the area
    int * shops = (int*)malloc(sizeof(int) * num_shops);

    for(long int i = 0; i < num_shops; i++){
        scanf("%d", &shops[i]);
    }

    // sort the array
    merge_sort(shops, num_shops);

    long int turning_point = find_turning(shops, bts, num_shops, to_purchase);

    // variable to store the wealth to beat
    long int highest_wealth = shops[num_shops - 1];

    long int j;
    if(bts > shops[0]){ // bts is not even greater than the least wealthy shop (initial check)
        
        // starts buying shops
        for(j = 0; j < num_shops; j++){
            if(bts > highest_wealth){ // the minimum number of buyouts it takes to become the wealthiest, stop comparing
                break;
            }
            
            // bts buys the wealthiest shop available
            if(to_purchase -> head != NULL){
                bts += pop(to_purchase);

                if(bts > shops[turning_point]){ // checks if any more shops become available to be purchased and if there is it pushes them onto the stack
                    turning_point = find_turning(shops, bts, num_shops, to_purchase);
                }
            }
        }
    }

    // isnt possible for bts to be the wealthiest
    if(j == 0){
        printf("-1");
    }
    // number of buyouts it took to become the wealthiest
    else{
        printf("%ld", j);
    }
    
    // free allocated memory
    free(shops);
    delete_stack(to_purchase); 

    return 0;
}

// function for creating a shop node
node * create_shop(int wealth){
    node * new_shop = (node*)malloc(sizeof(node));
    new_shop -> wealth = wealth;
    new_shop -> next = NULL;
    
    return new_shop;
}

// pushes the to be purchased shops onto the stack
void push(stack * to_purchase, int wealth){
    node * new_shop = create_shop(wealth);

    // if there is more than one node in the stack
    if(to_purchase -> head != NULL){
        new_shop -> next = to_purchase -> head;
    }

    to_purchase -> head = new_shop;
}

// return the wealthiest shop that can be purchased
int pop(stack * to_purchase){
    // if NULL
    if(!to_purchase -> head) return 0;

    // temp node to be freed
    node * temp = to_purchase -> head;

    int res = to_purchase -> head -> wealth;

    // head becomes next shop on the stack
    to_purchase -> head = to_purchase -> head -> next;
    free(temp);

    // return the shops wealth to be added
    return res;
}

// function to sort shop wealth
void merge_sort(int * shops, int length){
    if(length <= 1){ // base case
        return;
    }

    // front half
    merge_sort(shops, length / 2);
    // back half
    merge_sort(shops + (length / 2), length - (length / 2));

    // pointers for the 1st and 2nd halfs
    int front = 0;
    int back = length / 2;
    // temp array for sorting
    int * temp = (int*)malloc(sizeof(int) * length);

    // sorting
    for(int i = 0; i < length; i++){
        if((front == (length / 2)) || (back != length && shops[front] > shops[back])){
            temp[i] = shops[back];
            back++;
        }
        else{
            temp[i] = shops[front];
            front++;
        }
    }

    // copy contents
    for(int i = 0; i < length; i++){
        shops[i] = temp[i];
    }
    free(temp);
}

// frees the stack
void delete_stack(stack * to_purchase){
    if(!to_purchase -> head) return;
    while(to_purchase -> head){
        node * temp = to_purchase -> head;
        to_purchase -> head = to_purchase -> head -> next;
        free(temp);
    }
}

// search to find the turning point and push all shops until then
long int find_turning(int * shops, int bts, int num_shops, stack * to_purchase){
    long int turning_point = 0;
    for(long int i = 0; i < num_shops; i++){
        if(shops[i] > bts){
            turning_point = i;
            break;
        }
        push(to_purchase, shops[i]);
    }
    return turning_point;
}
