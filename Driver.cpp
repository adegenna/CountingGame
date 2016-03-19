#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <random>
#include <readline/readline.h>
#include <readline/history.h>
#include "Node.h"

using namespace std;

// Driver program to test Bucket class

int main(int argc, const char *argv[]) {
  // Initialize first node
  Node tree = Node(0,2,21,0);
  // Create tree
  tree.calcTree();
  // Play game
  int sum = 0;
  int userChoice;
  for (int iter=0; iter<15; iter++) {
    char* line = readline("> ");
    if (!line) break;
    if (*line) add_history(line);
    userChoice = atoi(line);
    printf("Iteration = %d\n",iter+1);
    sum = tree.evaluatePossibilities(sum+userChoice);
    free(line);
  }
  
}
