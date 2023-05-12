//
// Created by Guilherme Monteiro on 01/05/2023.
//

#ifndef DA_PROJECT2_DATA_H
#define DA_PROJECT2_DATA_H

#include <string>
#include <vector>
#include <set>
#include <fstream>
#include <sstream>
#include <iostream>
#include "Graph.h"


using namespace std;

class Data {
private:
    Graph g;
private:
    set<int> vertexes;

public:
    const Graph &getG() const;

    bool readToyData(string filename);
    bool readRealData(string folder);

    bool readRealNodes(string filename);
    bool readRealEdges(string filename);

    void tspBTAux(unsigned int n, unsigned int path[], unsigned int currentPath[],
                  unsigned int curr, unsigned int &best, unsigned int curr_n);
    unsigned int tspBT(unsigned int n, unsigned int path[]);



};


#endif //DA_PROJECT2_DATA_H
