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
  Node tree = Node(0,3,10,0);
  // Create tree
  tree.calcTree(2);

}
