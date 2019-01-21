//
//  iForest.hpp
//  assignment1
//
//  Created by James on 2019/1/18.
//  Copyright © 2019 James. All rights reserved.
//

#ifndef iForest_hpp
#define iForest_hpp

#include <iostream>
#include <set>
#include <vector>
#include <map>
#include "iTree.hpp"

using namespace std;

class iForest {
private:
    vector<vector<double>> features;
    vector<double> anomalyScores;
    vector<int> featureIds;
    set<double> anomalyRank;
    
    int nSample = 20;
    int nTrees = 10;
    int n;
    int dimension;
    int limitedTreeHeight;
    vector<iTree*> iTrees;
    int maxTreeDepth;
    
    double H(int n); // Harmonic number
    double c(int n); // Avg path length of unsuccessful search in BST
    double getPathLength(iTree* root, vector<double> node);
    double getAnomalyScore(vector<double> _data);
    
    map<double, int> mapAScoreIds;
    
public:
    iForest(vector<vector<double>> _features, int _nTrees, int _nSample, int _n, int _dimension, vector<int> _featureIds);
    ~iForest();
    void createTrees();
    void findAnomalies(int k);
};
#endif /* iForest_hpp */
