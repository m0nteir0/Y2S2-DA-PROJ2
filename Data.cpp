//
// Created by Guilherme Monteiro on 01/05/2023.
//

#include "Data.h"

bool Data::readToyData(string filename) {
    ifstream input(filename);
    if (input.is_open()) {
        string l;
        getline(input, l);
        while (getline(input, l)) {
            stringstream iss(l);


        }
        input.close();
        return true;
    } else {
        cout << "Unable to open file";
        return false;
    }
}

void Data::tspBTAux(unsigned int n, unsigned int path[], unsigned int currentPath[],
         unsigned int curr, unsigned int &best, unsigned int curr_n) {
    if (curr_n == n) {               //visited all nodes
        bool canReturn = false;
        for (Edge* e : g.findVertex(currentPath[curr_n - 1])->getAdj()){
            if (e->getDest()->getId() == 0){
                curr += e->getWeight();
                canReturn = true;
            }
        }

        if (canReturn && curr < best) {
            best = curr;
            std::copy(currentPath, currentPath + n, path);
        }
        return;
    }

    if (curr >= best) return;

    for (Edge* e : g.findVertex(currentPath[curr_n - 1])->getAdj()){
        if (!e->getDest()->isVisited()){
            currentPath[curr_n] = e->getDest()->getId();
            e->getDest()->setVisited(true);

            tspBTAux(n, path, currentPath, curr + e->getWeight(), best, curr_n + 1);

            e->getDest()->setVisited(false);
        }
    }
}

unsigned int Data::tspBT(unsigned int n, unsigned int path[]) {
    unsigned int currentPath[n];
    currentPath[0] = 0;
    unsigned int best = std::numeric_limits<unsigned int>::max();

    tspBTAux(n, path, currentPath ,0, best, 1);

    return best;
}