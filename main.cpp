//
//  main.cpp
//  assignment1
//
//  Created by James on 2019/1/16.
//  Copyright © 2019 James. All rights reserved.
//

#include <iostream>
#include <fstream>
#include "iForest.hpp"
#include <string>
#include <sstream>

#define MaxSubSample 256
#define MinTree 100

using namespace std;

int main(int argc, const char * argv[]) {
    vector<vector<double>> features;
    vector<int> featureIds;
    int nTree = MinTree;
    int nSample = MaxSubSample;
    int k = 0;
    int nSize = 0;
    int nCount = 0;
    bool readByFile = false;

    // read by input
    try {
        string stdinput;
        while ( cin >> stdinput ) {
            if (stdinput[0] == '<') {
                readByFile = true;
                features.clear();
                featureIds.clear();
                nCount = 0;
                break;
            } else {
                if (nCount == 0) {
                    k = stoi(stdinput);
                } else {
                    stringstream inputStream(stdinput);
                    string element = "";
                    vector<double> feature;
                    while(getline(inputStream,element,',')){
                        feature.push_back(stod(element));
                    }
                    features.push_back(feature);
                }
                featureIds.push_back(nCount);
                nCount++;
            }
        }
        
    }
    catch( const std::invalid_argument& e ) {
        return 0;
    }
    // read by file
    try {
        if(readByFile) {
            string path;
            cin >> path; //"testData/test.dat";
            ifstream fin;
            
            fin.open(path);
            if(!fin){
//                throw "Found no file";
                return 0;
            } else {
                string line;
                while(getline(fin,line,'\n')){
                    if (nCount == 0) {
                        k = stoi(line);
                    } else {
                        stringstream linestream(line);
                        string element = "";
                        vector<double> feature;
                        while(getline(linestream,element,',')){
                            feature.push_back(stod(element));
                        }
                        features.push_back(feature);
                    }
                    featureIds.push_back(nCount);
                    nCount++;
                }
            }
            fin.close();
        }
    }
    catch( const std::invalid_argument& e ) {
        return 0;
    }
    featureIds.pop_back();
    nSize = nCount-1;
    // check vector
    
    int nAttributes = 0;
    if (nSize <= 0) {
//        throw "No data.";
        return 0;
    } else if (nSize < k) {
        //        throw "k error.";
        return 0;
    } else {
        double preSize = 0;
        for (int j = 0; j < nSize; j++) {
            double size = features[j].size();
            if (size == 0) {
//                throw "No attributes.";
                return 0;
            }
            if (preSize == 0) {
                 preSize = size;
            } else {
                if (preSize!=size) {
//                    throw "Amount of attributes no equal.";
                    return 0;
                }
            }
        }
        nAttributes = (int) preSize;
    }
    // create isolation forest
    iForest forest(features, nTree, nSample, nSize, nAttributes, featureIds);
    forest.createTrees();
    forest.findAnomalies(k);
//    system("pause");
}
