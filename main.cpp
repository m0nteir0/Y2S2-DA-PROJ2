#include <iostream>
#include <ctime>
#include "Data.h"
#include "Interface.h"

int main() {
    Data d = Data();
    d.readToyData("../data/Toy-Graphs/stadiums.csv");
    /*
    Interface i = Interface();
    i.welcomePage();
     */
    /*
    cout << "EXECUTION TIMES:" << endl;
    const clock_t begin_time = clock();
    //d.readToyData("../data/Project2Graphs/Toy-Graphs/tourism.csv");
    //d.readToyData("../data/Project2Graphs/Toy-Graphs/stadiums.csv");
    //d.readFullyConnectedData("../data/Project2Graphs/Extra_Fully_Connected_Graphs/edges_900.csv");
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
    for (int i = 0; i < n; i++) cout << a[i] << ' ';
    cout << endl << endl;
    */

    /*
    cout << "Triangular Approximation\n";
    const clock_t tsp = clock();
    cout << d.tspTriangle() << endl;
    cout << endl <<"Total: " << float( clock () - tsp) /  CLOCKS_PER_SEC <<"s" << endl;
    */


    cout << "Nearest Neighbour\n";
    const clock_t tsp2 = clock();
    vector<Vertex*> path = d.tspNearestNeighbour();
    vector<Vertex*> path2 = path;
    cout << d.getPathDist(path) << endl;
    cout << endl <<"Total: " << float( clock () - tsp2) /  CLOCKS_PER_SEC <<"s" << endl;


    cout << "Nearest Neighbour 2opt\n";
    const clock_t tsp3 = clock();
    cout << d.tsp2opt(path, 1) << endl;
    cout << endl <<"Total: " << float( clock () - tsp3) /  CLOCKS_PER_SEC <<"s" << endl;

    cout << "Nearest Neighbour 3opt\n";
    const clock_t tsp4 = clock();
    cout << d.tsp3opt(path2, 1) << endl;
    cout << endl <<"Total: " << float( clock () - tsp4) /  CLOCKS_PER_SEC <<"s" << endl;
}
