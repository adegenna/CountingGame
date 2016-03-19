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
  currentLevel_ = 0;
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
    if (val <= sum_)
      nodes_[i] = new Node(val,K_,sum_,level_+1);
    else
      nodes_[i] = NULL;
  }

}

void Node::calcTree() {
  // Function to calculate entire decision tree

  // Set mother node (node 0)
  setNodes();
  // Tree initialization
  totalLevels_ = 10;
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
  // Recursive tree creation
  while (sizeCurrent != 0) {
    for (int i=0; i<sizeCurrent; i++) {
      fprintf(fout,"LEVEL = %d\tVALUE = %d\n",current[i]->level_,current[i]->N_);
      for (int j=0; j<K_; j++) {
	// Look at K_ child nodes of current node
	child = current[i]->nodes_[j];
	if (child) {
	  // If node exists (i.e. is not null), set child nodes
	  child->setNodes();
	  next.push_back(child);
	  numNext++;
	}

      }
    }
    // Reset current nodes for next level iteration
    current.swap(next);
    next.clear();
    sizeCurrent = numNext;
    numNext = 0;
  }
  fclose(fout);
}

int Node::evaluatePossibilities(int newChoice) {
  // Function to evaluate possible tree of choices and pick the choice
  // which has the greatest probability of future success

  Node* currentNode = this;
  // Go to current node of decision tree
  if (currentLevel_ != 0) {
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
  printf("User choice = %d\n",currentNode->nodes_[newChoiceInd]->N_);
  history_.push_back(newChoiceInd);
  currentNode = currentNode->nodes_[newChoiceInd];
  currentLevel_ += 1;
  // Evaluate subtree of possible choices and find optimal choice
  vector<int> IND;
  Node* searchNode;
  int indSize;
  int score[K_];
  bool flag;
  // Initialize score
  for (int i=0; i<K_; i++) {
    score[i] = 0;
  }
  int Choice = 0;
  while (Choice < K_) {
    // Go to node specified by Choice
    searchNode = currentNode->nodes_[Choice];
    flag = false;
    if (searchNode) {
      while (flag==false) {
	// If IND is not empty, go to node specified by it
	if (!IND.empty()) {
	  printf("size(IND) = %d \t",IND.size());
	  for (int i=0; i<IND.size(); i++)
	    printf("%d ",IND[i]);
	  printf("\n");
	  for (int i=0; i<IND.size(); i++) {
	    searchNode = searchNode->nodes_[IND[i]];
	  }
	}
	// Search down leftmost unsearched branch until sum_ is reached
	while (searchNode->N_ != sum_) {
	  searchNode = searchNode->nodes_[0];
	  IND.push_back(0);
	}
	// Evaluate cost: +1 if sum_ is reached at user's turn, -1 otherwise
	if (searchNode->level_ % 2 == 0)
	  score[Choice] += 1;
	else
	  score[Choice] += -1;
	// Reset IND
	indSize = IND.size();
	if (indSize > 1) { 
	  IND[indSize-2] += 1;
	  IND.resize(indSize-1);
	  searchNode = currentNode->nodes_[Choice];
	}
	else {
	  flag = true;
	}
	// Check to see if we are done evaluating nodes_[Choice]
	if (IND[0] == K_)
	  flag = true;
      }
    }
    Choice++;
  }




  // Print scores to file
  int selection = 0;
  int scoreSelect = score[0];
  for (int i=0; i<K_; i++) {
    printf("CHOICE %d = %d, COST = %d\n",i+1,currentNode->nodes_[i]->N_,score[i]);
    if (score[i] < scoreSelect) {
      scoreSelect = score[i];
      selection = i;
    }
  }
  // Update history
  history_.push_back(selection);
  currentLevel_++;
  printf("COMPUTER CHOICE: ADD %d, TOTAL = %d\n\n",selection+1,currentNode->nodes_[selection]->N_);
  
  return currentNode->nodes_[selection]->N_;
}
