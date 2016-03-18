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
  //FILE* fout = fopen("Tree.out","w");
  //fprintf(fout,"TREE CALCULATION: LEAVES = %d, LEVELS = %d\n\n\n",K_,level_);
  //for (int i=0; i<K_; i++)
  //  fprintf(fout,"LEVEL = %d\tVALUE = %d\n",nodes_[i]->level_,nodes_[i]->N_);
  //fprintf(fout,"\n");
  // Recursive tree creation
  for (int k=0; k<depth-1; k++) {
    for (int i=0; i<sizeCurrent; i++) {
      // Set child nodes for current nodes at current level
      for (int j=0; j<K_; j++) {
	child = current[i]->nodes_[j];
	child->setNodes();
	//for (int jj=0; jj<K_; jj++)
	  //fprintf(fout,"LEVEL = %d\tVALUE = %d\n",child->nodes_[jj]->level_,child->nodes_[jj]->N_);
        // Track next level of nodes
	next.push_back(child);
	numNext++;
      }
    }
    //fprintf(fout,"\n");
    // Reset current nodes for next level iteration
    current.swap(next);
    next.clear();
    sizeCurrent = numNext;
    numNext = 0;
  }
  //fclose(fout);
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
  int searchLevels = totalLevels_-currentLevel_;
  int IND[searchLevels];
  Node* searchNode;
  for (int i=0; i<searchLevels; i++) {
    IND[i] = 0;
  }
  int id = searchLevels-1;
  int val;
  int score[K_];
  bool flag;
  // Initialize score
  for (int i=0; i<K_; i++) {
    score[i] = 0;
  }
  while (IND[0] < K_) {
    // Go to node specified by IND
    searchNode = currentNode;
    for (int j=0; j<searchLevels; j++) {
      searchNode = searchNode->nodes_[IND[j]];
    }
    // Evaluate score of searchNode
    val = searchNode->N_;
    score[IND[0]] += abs(sum_-val);
    // Update IND
    IND[id]++;
    for (int i=searchLevels-1; i>-1; i--) {
      if ((IND[i] == K_) && (i != 0)) {
	IND[i] = 0;
	IND[i-1]++;
      }
      else if ((IND[i] == K_) && (i == 0)) {
	break;
      }
    }
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
