//
//  iTree.cpp
//  assignment1
//
//  Created by James on 2019/1/18.
//  Copyright © 2019 James. All rights reserved.
//

#include "iTree.hpp"
#include <set>
#include <vector>
#include <iostream>
#include <math.h>

using namespace std;

iTree::iTree(vector<vector<double>> _features, int _limitHeight, int _dimension, int _level) {
//    if (_level == 1) {
//        cout<< "This is the first tree"<<endl;
//    }
//    cout<<" level: "<< _level;
//    cout<<" size: "<< _features.size()<<endl;
    features = _features;
    size = (int) _features.size();
    level = _level;
    limitHeight = _limitHeight;
    usedDimension = rand() % _dimension;

    // check
    if (_level >= _limitHeight || size <=1) {
        return;
    }
    
    // count
    vector<vector<double>> leftFeatures;
    vector<vector<double>> rightFeatures;
    set<double> Q;

    for(int j = 0; j < size; j++) {
        Q.insert(_features[j][usedDimension]);
    }
    if (Q.size()<=1) {
        return;
    }
    double minQ = *Q.begin();
    double maxQ = *Q.rbegin();
    double f = (double)rand() / RAND_MAX;
    double q = minQ+f*(maxQ-minQ);
    splittedAt = q;
    
    for(int j = 0; j < size; j++) {
        if (_features[j][usedDimension] < q) {
            leftFeatures.push_back(_features[j]);
        } else {
            rightFeatures.push_back(_features[j]);
        }
    }
    left = new iTree(leftFeatures,_limitHeight,_dimension,_level + 1);
    right = new iTree(rightFeatures,_limitHeight,_dimension,_level + 1);
}
iTree::~iTree() {
    if(left) {
        left->~iTree();
        delete left;
    }
    if(right) {
        right->~iTree();
        delete right;
    }
}

int iTree::runTreeAndGetLevel(vector<double> node) {

    if(left == nullptr && right == nullptr) {
        if (size > 1) {
            return level+c(size);
        } else {
            return level;
        }
    }
    
    if( node[usedDimension] < splittedAt) {
        return left->runTreeAndGetLevel(node);
    } else {
        return right->runTreeAndGetLevel(node);
    }
    
}

double iTree::H(int n) {
    return  (log(n) + 0.5772156649); // Euler's constant
}

double iTree::c(int n) {
    return (2*H(n - 1) - (2*(n - 1)/n));
}
