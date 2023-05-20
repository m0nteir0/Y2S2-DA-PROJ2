#include <iostream>
#include <ctime>
#include "Data.h"

int main() {
    std::cout << "Hello, World!" << std::endl;
    Data d = Data();
    cout << "EXECUTION TIMES:" << endl;
    const clock_t begin_time = clock();
     d.readToyData("../data/Project2Graphs/Toy-Graphs/tourism.csv");
    //d.readToyData("../data/Project2Graphs/Toy-Graphs/shipping.csv");
    // d.readRealData("../data/Project2Graphs/Real-World-Graphs/graph1");
    cout << endl <<"Total: " << float( clock () - begin_time ) /  CLOCKS_PER_SEC <<"s" << endl;
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
    }
     */
    cout << d.tspTriangle()<< endl;
}
