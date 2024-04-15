// header files
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

// input maxes
#define MAX_RESPONSE 100000
#define MAX_FOOD 10000
#define MAX_COMMAND 10
#define MAX_TRIE 32

// struct definition for a trie node
typedef struct node{
  int sub_trie; // the ammount of food from below and including this node
  int my_ammount; // amount of food given
  struct node * children[MAX_TRIE]; // children, 0-9 and a-v
}node;



// function prototypes
void delete_trie(node * root);
node * add(node * root, char * response, int food);
void sum(node * root, char * response, int * min, int * max);
void change(node * root, char * response, char * change);
int idx(char response);
node * create_node();
void trim(char * line);

// main function
int main(){
  // root node for the trie
  node * root = create_node();
  
  // strings to take input
  char * line = (char*)malloc(sizeof(char) * MAX_RESPONSE);
  char * command = (char*)malloc(sizeof(char) * MAX_COMMAND);
  char * response = (char*)malloc(sizeof(char) * MAX_RESPONSE);
  char * new = (char*)malloc(sizeof(char) * MAX_RESPONSE);
  // variable to store the food
  int food;
  // hold the min and max food ammounts
  int max;
  int min;

  // execute the input commands
  while(1){
    // takes in the line
    fgets(line, MAX_RESPONSE, stdin);

    // trims the white space and new line characters
    trim(line);

    // parses out the command
    sscanf(line, "%s", command);

    if(strcmp(command, "ADD") == 0){ // add is the input, add a new family
      sscanf(line, "%*s %s %d", response, &food);
      root = add(root, response, food);
    }
    else if(strcmp(command, "CHANGE") == 0){ // change is the input, change the response
      sscanf(line, "%*s %s %s", response, new);
      change(root, response, new);
    }
    else if(strcmp(command, "SUM") == 0){ // sum is the input, print the possible min and max
      sscanf(line, "%*s %s", response);
      sum(root, response, &min, &max);
      printf("%d %d\n", min, max);
    }
    else if(strcmp(command, "QUIT") == 0){ // quit is the input, break the loop
      break;
    }
  }

  // free memory
  delete_trie(root);
  free(command);
  free(response);
  free(new);

  return 0;
}

// deletes the trie
void delete_trie(node * root){
  // base case
  if(!root){
    return;
  }

  // delete all children
  for(int i = 0; i < MAX_TRIE; i++){
    delete_trie(root -> children[i]);
  }

  free(root);
}

// adds a new family to the trie based on the response
node * add(node * root, char * response, int food){
  // current node to traverse the trie
  node * current = root;

  // loop until '\0' in response
  for(int i = 0; response[i]; i++){
    // find the index
    int index = idx(response[i]);
    // if there is no node at the index then make one
    if(!current -> children[index]){
      current -> children[index] = create_node();
    }

    // move to the next node and add to the sub trie count
    current = current -> children[index];
    current -> sub_trie += food;
  }

  // add the food to that famalies personal ammount
  current -> my_ammount += food;

  // return the root
  return root;
}

// finds the possible min and max food
void sum(node * root, char * prefix, int * min, int * max){
  // initially set max and min to 0
  *max = 0;
  *min = 0;

  // current node to traverse the tree
  node * current = root;

  // going to add all the my ammounts in the max until the ending node of the prefix is reached then add the subtrie count of that node into min and max
  // loop until '\0' in the prefix
  for(int i = 0; prefix[i]; i++){
    int index = idx(prefix[i]);

    
    // that path doesnt exist so exit
    if(!current){
      break;
    }

    if(current -> my_ammount > 0){
      *max += current -> my_ammount;
    }

    // move to the next node
    current = current -> children[index];
  }

  // add the subtrie to the max and min values
  if(current){
    *min += current -> sub_trie;
    *max += current -> sub_trie;
  }
}

// changes the previous response to the new one
void change(node * root, char * response, char * change){
  // current node to traverse the trie
  node * current = root;

  // variable to hold that famalies food
  int ammount = 0;

  // find the response to be deleted
  // loop until '\0' in response
  for(int i = 0; response[i]; i++){
    int index = idx(response[i]);
    // null check
    if(!current -> children[index]){
      continue;
    }
    current = current -> children[index];
  }
  ammount = current -> my_ammount;

  // start back at the beginning
  current = root;

  // go back and remove the food
  // loop until '\0' in response
  for(int i = 0; response[i]; i++){
    int index = idx(response[i]);
    // null check
    if(!current -> children[index]){
      continue;
    }
    current = current -> children[index];
    current -> sub_trie -= ammount;
  }

  // put the food in the changed response
  root = add(root, change, ammount);
}

// function to find the index
int idx(char response){
  if(isdigit(response)){
    return response - '0';
  }
  else{
    return response - 'a' + 10;
  }  
}

// function that creates and returns a new node
node * create_node(){
  // initialize new node
  node * new_node = (node*)malloc(sizeof(node));
  new_node -> sub_trie = 0;
  new_node -> my_ammount = 0;

  // set all children to null
  for(int i = 0; i < MAX_TRIE; i++){
      new_node -> children[i] = NULL;
  }

  // return the new node
  return new_node;
}

// trims the white space and new line characters
void trim(char * line){
  // starting white space
  char * start = line;
  while(isspace(*start)){
    start++;
  }

  // ending white space
  int end = strlen(start);
  while(end > 0 && isspace(start[end - 1])){
    end--;
  }

  // put '\0'
  start[end] = '\0';

  // shift to start if not already there
  if(start != line){
    memmove(line, start, end + 1);
  }
}

