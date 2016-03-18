#ifndef __NODE_H__
#define __NODE_H__

#include <vector>

class Node {
 public:
  Node(int N, int K, int sum, int level);
  ~Node();
  Node** nodes_;
  void setNodes();
  int getNPts();
  int getLevel();
  void calcTree(int depth);
  int evaluatePossibilities(int newChoice);

  // These should really be private...
  int N_;                     // Node value
  int K_;                     // Number of leaves
  int level_;                 // Node level in tree heirarchy
  int sum_;                   // Objective (desired) sum
  std::vector<int> history_;  // History of choices made
  int currentLevel_;          // Current level
  int totalLevels_;           // Total levels of entire tree
};


#endif
