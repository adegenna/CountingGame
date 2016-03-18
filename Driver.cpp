#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <random>
#include "Node.h"

using namespace std;

// Driver program to test Bucket class

int main(int argc, const char *argv[]) {
  // Initialize first node
  Node tree = Node(0,5,17,0);
  // Create tree
  tree.calcTree(5);
  // Play game
  int sum = 0;
  sum = tree.evaluatePossibilities(1);
  sum = tree.evaluatePossibilities(sum+2);
  sum = tree.evaluatePossibilities(sum+3);
  sum = tree.evaluatePossibilities(sum+4);
  sum = tree.evaluatePossibilities(sum+1);

}
