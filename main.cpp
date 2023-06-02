#include <iostream>
#include <ctime>
#include "algorithms/Data.h"
#include "algorithms/Interface.h"

int main() {
    Data d = Data();


    Interface i = Interface();
    i.welcomePage();
    d.getG().clearGraph();
    d.readToyData("../data/Toy-Graphs/stadiums.csv");
    //d.readFullyConnectedData("../data/Extra_Fully_Connected_Graphs/edges_25.csv");
    /*
    cout << "EXECUTION TIMES:" << endl;
    const clock_t begin_time = clock();
    //d.readToyData("../data/Project2Graphs/Toy-Graphs/tourism.csv");
    //d.readToyData("../data/Project2Graphs/Toy-Graphs/stadiums.csv");

    //d.readRealData("../data/Project2Graphs/Real-world Graphs/graph1");
    cout << endl <<"Total: " << float( clock () - begin_time ) /  CLOCKS_PER_SEC <<"s" << endl;
    */
     /*
    unsigned int path[5];
    unsigned int dist = d.tspBT(5, path);
    for (int i = 0; i < 5; ++i) {
        cout << path[i] << " ";
    }
    cout << endl << dist << endl;
    */

    cout << endl << endl;
    /*
    cout << d.getG().prim() << endl;
    for (Vertex* v : d.getG().getVertexSet()){
        if (v->getPath() == nullptr) {
            cout << v->getId() << endl;
            continue;
        }
        cout << v->getId() << " ------ " << v->getPath()->getId() << endl;
    }*/
    /*
    cout << "BACKTRACKING\n";
    unsigned int n = d.getG().getNumVertex();
    int a[n];
    cout << d.tspBT(n,a)<< endl;
    cout << "Path: ";
    for (int i = 0; i < n; i++) cout << a[i] << ' ';
    cout << endl << endl;
    */
    cout << "Triangular Approximation\n";
    const clock_t tsp = clock();
    vector<Vertex*> path3;
    cout << d.tspTriangle(path3) << endl;
    vector<Vertex*> path4 = path3; //copy constructor
    // cout <<"Total: " << float( clock () - tsp) /  CLOCKS_PER_SEC <<"s" << endl;
    cout << "Path: ";
    for (int i = 0; i < path3.size() - 1; i++) {
        cout << path3[i]->getId() << " -> ";
    }
    cout << path3.back()->getId() << endl;
    cout << endl ;

    cout << "Triangular Approximation 2opt\n";
    const clock_t tsp5 = clock();
    cout << d.tsp2opt(path3, 1) << endl;
    // cout <<"Total: " << float( clock () - tsp5) /  CLOCKS_PER_SEC <<"s" << endl;
    cout << "Path: ";
    for (int i = 0; i < path3.size() - 1; i++) {
        cout << path3[i]->getId() << " -> ";
    }
    cout << path3.back()->getId() << endl;
    cout << endl;

    cout << "Triangular Approximation 3opt\n";
    const clock_t tsp6 = clock();
    //cout << (path3==path4) << endl;
    cout << d.tsp3opt(path4, 1) << endl;
    // cout <<"Total: " << float( clock () - tsp6) /  CLOCKS_PER_SEC <<"s" << endl;
    cout << "Path: ";
    for (int i = 0; i < path4.size() - 1; i++) {
        cout << path4[i]->getId() << " -> ";
    }
    cout << path4.back()->getId() << endl;
    cout << endl ;

    cout << "Nearest Neighbour\n";
    const clock_t tsp2 = clock();
    vector<Vertex*> path = d.tspNearestNeighbour();
    vector<Vertex*> path2 = path;
    cout << d.getPathDist(path) << endl;
    cout <<"Total: " << float( clock () - tsp2) /  CLOCKS_PER_SEC <<"s" << endl;
    cout << "Path: ";
    for (int i = 0; i < path.size() - 1; i++) {
        cout << path[i]->getId() << " -> ";
    }
    cout << path.back()->getId() << endl;
    cout << endl ;


    cout << "Nearest Neighbour 2opt\n";
    const clock_t tsp3 = clock();
    cout << d.tsp2opt(path, 1) << endl;
    cout <<"Total: " << float( clock () - tsp3) /  CLOCKS_PER_SEC <<"s" << endl;
    cout << "Path: ";
    for (int i = 0; i < path.size() - 1; i++) {
        cout << path[i]->getId() << " -> ";
    }
    cout << path.back()->getId() << endl;
    cout << endl ;

    cout << "Nearest Neighbour 3opt\n";
    const clock_t tsp4 = clock();
    cout << d.tsp3opt(path2, 1) << endl;
    cout << "Total: " << float( clock () - tsp4) /  CLOCKS_PER_SEC <<"s" << endl;
    cout << "Path: ";
    for (int i = 0; i < path2.size() - 1; i++) {
        cout << path2[i]->getId() << " -> ";
    }
    cout << path2.back()->getId() << endl;
    cout << endl ;
}