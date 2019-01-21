//
//  iForest.cpp
//  assignment1
//
//  Created by James on 2019/1/18.
//  Copyright © 2019 James. All rights reserved.
//

#include "iForest.hpp"
#include <set>
#include <vector>
#include <random>

iForest::iForest(vector<vector<double>> _features, int _nTrees, int _nSample, int _n, int _dimension, vector<int> _featureIds){
    n = _n;
    features = _features;
    featureIds = _featureIds;
    if (n/20>_nTrees) {
        nTrees = n/20;
    } else {
        nTrees = _nTrees;
    }
    if (n/10 <_nSample) {
        if(n/10 <= 0) {
            nSample = n/2;
        } else {
            nSample = n/10;
        }
    } else {
        nSample = _nSample;
    }
    dimension = _dimension;
    maxTreeDepth = log2(_nSample);
}
iForest::~iForest(){
    
}

void iForest::createTrees() {
    for (int i = 0; i<nTrees;i++) {
        random_shuffle(featureIds.begin(),featureIds.end());
        int * idHead = &featureIds[0];
        vector<vector<double>> sampleFeatures;
        // check
        for( int j = 0; j < nSample; j++) {
            vector<double> temp;
            int tem = *(idHead+j);
            temp = features[tem];
            sampleFeatures.push_back(temp);
        }

        iTree *newTree = new iTree(sampleFeatures, maxTreeDepth, dimension, 1);
        iTrees.push_back(newTree);
    }
   
}

double iForest::H(int n) {
    return  (log(n) + 0.5772156649); // Euler's constant
}

double iForest::c(int n) {
    return (2*H(n - 1) - (2*(n - 1)/n));
}

double iForest::getAnomalyScore(vector<double> node) {
    double totalPathLength = 0;
    double avgPathLength = 0;
    
    for(int i = 0; i < nTrees; i++) {
        double expPathLength = iTrees[i]->runTreeAndGetLevel(node);
        totalPathLength += expPathLength;
    }
    avgPathLength = totalPathLength/nTrees; // = E(h(x))
    double normAvgPathLength = avgPathLength/c(nSample);
    double anomalyScore = pow(0.5, normAvgPathLength);
    return anomalyScore;
}

void iForest::findAnomalies(int k) {
    int anomalyCounter = 0;
    for(int i = 0;i<features.size();i++) {
        double score = getAnomalyScore(features[i]);
        mapAScoreIds[score] = i;
        anomalyRank.insert(score);
        if(score>0.5){
            anomalyCounter++;
        }
    }
    set<double>::iterator it;
    it = anomalyRank.end();
    for(int j = 0; j<k;j++) {
        --it;
        vector<double> data;
        data = features[mapAScoreIds[*it]];
        for(int l = 0; l<data.size(); l++) {
            cout<<data[l];
            if(l !=data.size()-1) {
                cout<<",";
            }
        }
        cout<<endl;        
    }
}
