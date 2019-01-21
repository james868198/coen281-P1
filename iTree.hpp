//
//  iTree.hpp
//  assignment1
//
//  Created by James on 2019/1/18.
//  Copyright © 2019 James. All rights reserved.
//

#ifndef iTree_hpp
#define iTree_hpp
#include <set>
#include <vector>

using namespace std;

class iTree {
private:
    vector<vector<double>> features;
    int level; // Level of the tree
    int limitHeight;
    iTree* left = nullptr;; // Pointer to left iTree
    iTree* right = nullptr;; // Pointer to right iTree
    int size;
    int usedDimension;
    double splittedAt;
    
    double H(int n); // Harmonic number
    double c(int n); // Avg path length of unsuccessful search in BST
public:
    iTree(vector<vector<double>> _features, int _limitHeight, int _dimension, int _level);
    ~iTree();
    int runTreeAndGetLevel(vector<double> node);
    
};

#endif /* iTree_hpp */
