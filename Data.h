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
public:
    Graph &getG();


    bool readToyData(string filename);
    bool readFullyConnectedData(string filename);
    bool readRealData(string folder);

    bool readRealNodes(string filename);
    bool readRealEdges(string filename);

    void tspBTAux(unsigned int n, int path[], int currentPath[],
                  double curr, double &best, unsigned int curr_n);
    double tspBT(unsigned int n, int path[]);


    static double haversine(double lat1, double lon1, double lat2, double lon2);
    vector<Vertex*> getPreorderWalk();
    double tspTriangle();

    vector<Vertex*> tspNearestNeighbour();
    double getPathDist(vector<Vertex*> path);
    vector<Vertex*> swap2opt(vector<Vertex*> path, int i, int j);
    double tsp2opt(vector<Vertex*> path);
};



#endif //DA_PROJECT2_DATA_H
