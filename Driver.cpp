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
  // Explain rules
  printf("######################\nCOUNTING GAME\n######################\n\n");
  printf("EXPLANATION: THERE ARE TWO PLAYERS (USER + COMPUTER).\n");
  printf("YOU SELECT A TOTAL SUM (N) AND A NUMBER OF CHOICES (K).\n");
  printf("WHOEVER STARTS FIRST BEGINS BY SELECTING A NUMBER BETWEEN 1 AND K.\n");
  printf("THE NEXT PLAYER DOES THE SAME, AND SO ON UNTIL THE TOTAL SUM N IS REACHED.\n");
  printf("WHOEVER REACHES THE TOTAL SUM N LOSES.\n\n");
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
    printf("COMPUTER GOES FIRST. THERE ARE %d CHOICES. FIRST PLAYER TO %d LOSES\n\n",choices,gameSum);
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
    printf("ITERATION = %d\n",iter+1);
    sum = tree.evaluatePossibilities(-1);
    iter++;
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
