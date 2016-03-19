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
  char* line;
  printf("ENTER DESIRED SUM OF GAME: ");
  line = readline("> ");
  int gameSum = atoi(line);
  printf("\n");
  printf("ENTER NUMBER OF CHOICES: ");
  line = readline("> ");
  int choices = atoi(line);
  printf("\n");
  printf("ENTER WHO GOES FIRST (USER = 1, COMPUTER = 2): ");
  line = readline("> ");
  int firstPlayer = atoi(line);
  if (firstPlayer == 1)
    printf("YOU GO FIRST. THERE ARE %d CHOICES. FIRST PLAYER TO %d LOSES\n\n",choices,gameSum);
  else
    printf("COMPUTER GOES FIRST. THERE ARE  %d CHOICES. FIRST PLAYER TO %d LOSES\n\n",choices,gameSum);
  free(line);
  // Initialize first node
  Node tree = Node(0,choices,gameSum,0);
  // Create tree
  tree.calcTree();
  // Play game
  int sum = 0;
  int iter = 0;
  int userChoice;
  if (firstPlayer != 1) {
    sum = tree.evaluatePossibilities(-1);
    printf("COMPUTER CHOOSES %d\n\n",sum);
  }
  while (sum < gameSum) {
    char* line = readline("> ");
    if (!line) break;
    if (*line) add_history(line);
    userChoice = atoi(line);
    while ((userChoice > choices) || (sum + userChoice > gameSum) || (userChoice < 1)) {
      printf("INVALID CHOICE. ");
      line = readline(" >");
      userChoice = atoi(line);
    }
    printf("ITERATION = %d\n",iter+1);
    sum = tree.evaluatePossibilities(sum+userChoice);
    free(line);
    iter++;
  }

  return 0;
}
