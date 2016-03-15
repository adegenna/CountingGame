#include "Node.h"
#include <stdlib.h>
#include <stdio.h>
#include <cmath>
#include <algorithm>

using namespace std;

Node::Node(int N, int K, int sum, int level) {
  // Node constructor
  
  N_ = N;
  K_ = K;
  sum_ = sum;
  level_ = level;
  nodes_ = new Node*[K_];
  for (int i=0; i<K_; i++)
    nodes_[i] = NULL;
  currentLevel = 0;
}

Node::~Node() {
  for (int i=0; i<K_; i++)
    delete nodes_[i];
  delete nodes_;
}

void Node::setNodes() {
  // Function to set child nodes/values
  
  int val;
  for (int i=0; i<K_; i++) {
    val = N_ + (i+1);
    nodes_[i] = new Node(val,K_,sum_,level_+1);
  }

}

void Node::calcTree(int depth) {
  // Function to calculate entire decision tree

  // Set mother node (node 0)
  setNodes();
  // Tree initialization
  depth = 2*depth;
  totalLevels_ = depth;
  int N,level;
  int K = K_;
  int sum = sum_;
  bool flag = false;
  vector<Node*> current;
  current.push_back(this);
  vector<Node*> next;
  Node* child;
  int numNext = 0;
  int sizeCurrent = 1;
  // Print to file
  FILE* fout = fopen("Tree.out","w");
  fprintf(fout,"TREE CALCULATION: LEAVES = %d, LEVELS = %d\n\n\n",K_,level_);
  for (int i=0; i<K_; i++)
    fprintf(fout,"LEVEL = %d\tVALUE = %d\n",nodes_[i]->level_,nodes_[i]->N_);
  fprintf(fout,"\n");
  // Recursive tree creation
  for (int k=0; k<depth-1; k++) {
    for (int i=0; i<sizeCurrent; i++) {
      // Set child nodes for current nodes at current level
      for (int j=0; j<K_; j++) {
	child = current[i]->nodes_[j];
	child->setNodes();
	for (int jj=0; jj<K_; jj++)
	  fprintf(fout,"LEVEL = %d\tVALUE = %d\n",child->nodes_[jj]->level_,child->nodes_[jj]->N_);
        // Track next level of nodes
	next.push_back(child);
	numNext++;
      }
    }
    fprintf(fout,"\n");
    // Reset current nodes for next level iteration
    current.swap(next);
    next.clear();
    sizeCurrent = numNext;
    numNext = 0;
  }
  fclose(fout);
}

void Node::evaluatePossibilities(int newChoice) {
  // Function to evaluate possible tree of choices and pick the choice
  // which has the greatest probability of future success

  Node* currentNode = this;
  // Go to current node of decision tree
  if (currentLevel != 0) {
    Node* currentNode = this;
    for (int i=0; i<currentLevel_; i++) {
      // Prune through history of tree to current node
      currentNode = currentNode->nodes_[history_[i]];
    }
  }
  // Find which of three children of currentNode represents user's
  // choice, append to history, and go to that node
  int newChoiceInd;
  for (int i=0; i<K_; i++) {
    if (currentNode->nodes_[i]->N_ == newChoice) {
      newChoiceInd = i;
      break;
    }
  }
  history.push_back(newChoiceInd);
  currentNode = currentNode->nodes_[newChoiceInd];
  currentLevel_ += 1;
  // Evaluate subtree of possible choices and find optimal choice
  int searchLevels = totalLevels_-currentLevel;
  int IND[searchLevels];
  Node* searchNode = currentNode;
  for (int i=0; i<searchLevels; i++) {
    IND[i] = 0;
  }
  int id = searchLevels-1;
  int val;
  int score[K_];
  bool flag;
  while (IND[0] < K_) {
    // Initialize score
    score[IND[0]] = 0;
    // Go to node specified by IND
    for (int j=0; j<searchLevels; j++) {
      searchNode = searchNode->nodes_[IND[j]];
    }
    // Evaluate score of searchNode
    val = searchNode->N_;
    score[IND[0]] += abs(sum_-val);
    // Update IND
    flag = false;
    IND[id]++;
    while (flag == false) {
      if ((IND[id] == K_) && (id != 0)) {
	IND[id] = 0;
	IND[id-1]++;
	id--;
      }
      else if ((IND[id] != K_) && (id == 0)) {
	flag = true;
	id = searchLevels-1;
      }
      else if ((IND[id] == K_) && (id == 0)) {
	flag = true;
	id = searchLevels-1;
      }
    }

  }
    
}