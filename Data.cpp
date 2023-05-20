//
// Created by Guilherme Monteiro on 01/05/2023.
//

#include "Data.h"
#include <math.h>

bool Data::readToyData(string filename) {
    ifstream input(filename);
    if (input.is_open()) {
        string l;
        getline(input, l); // consumes label
        vector<string> fields;
        int origem, destino;
        float distancia;
        string field;
        while (getline(input, l)) {
            stringstream iss(l);
            while (getline(iss, field, ',')) {
                fields.push_back(field);
            }
            origem = stoi(fields[0]);
            destino = stoi(fields[1]);
            distancia = stof(fields[2]);
            fields.clear();

            if (vertexes.insert(origem).second) //return false if already exists
                g.addVertex(origem);
            if (vertexes.insert(destino).second)
                g.addVertex(destino);
            g.addBidirectionalEdge(origem, destino, distancia);
        }
        input.close();
        return true;
    } else {
        cout << "Unable to open file";
        return false;
    }
}

bool Data::readRealData(string folder) {
    const clock_t node_time = clock();
    bool nodes = readRealNodes(folder + "/nodes.csv");
    cout << "Nodes: " << float( clock () - node_time ) /  CLOCKS_PER_SEC <<"s" << endl;

    const clock_t edge_time = clock();
    bool edges = readRealEdges(folder + "/edges.csv");
    cout << "Edges: " << float( clock () - edge_time ) /  CLOCKS_PER_SEC <<"s" << endl;

    return nodes && edges;
}

bool Data::readRealNodes(string filename) {
    ifstream input(filename);
    if (input.is_open()) {
        string l;
        getline(input, l); // consumes label
        vector<string> fields;
        int id;
        float lat, lon;
        string field;
        while (getline(input, l)) {
            stringstream iss(l);
            while (getline(iss, field, ',')) {
                fields.push_back(field);
            }
            id = stoi(fields[0]);
            lon = stof(fields[1]);
            lat = stof(fields[2]);
            fields.clear();

            if (vertexes.insert(id).second) //return false if already exists
                g.addVertex(id, lon, lat);
        }
        input.close();
        return true;
    } else {
        cout << "Unable to open file";
        return false;
    }
}

bool Data::readRealEdges(string filename) {
    ifstream input(filename);
    if (input.is_open()) {
        string l;
        getline(input, l); // consumes label
        vector<string> fields;
        fields.reserve(3);
        int origem, destino;
        float distancia;
        string field;
        while (getline(input, l)) {
            stringstream iss(l);

            while (getline(iss, field, ',')) {
                fields.push_back(field);
            }
            origem = stoi(fields[0]);
            destino = stoi(fields[1]);
            distancia = stof(fields[2]);

            /*
            for (int i = 0; std::getline(iss, field, ','); i++) {
                if (i == 0) origem = std::stoi(field);
                else if (i == 1) destino = std::stoi(field);
                else if (i == 2) distancia = std::stof(field);
                fields.push_back(std::move(field));
            }
             */

            fields.clear();

            g.addBidirectionalEdge(origem, destino, distancia);
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

Graph &Data::getG() {
    return g;
}


//-----------------T4.2-----------------//
double Data::haversine(double lat1, double lon1, double lat2, double lon2)
{
    // distance between latitudes and longitudes
    double dLat = (lat2 - lat1) * M_PI / 180.0;
    double dLon = (lon2 - lon1) * M_PI / 180.0;

    // convert to radians
    lat1 = (lat1) * M_PI / 180.0;
    lat2 = (lat2) * M_PI / 180.0;

    // apply formulae
    double a = pow(sin(dLat / 2), 2) +
               pow(sin(dLon / 2), 2) * cos(lat1) * cos(lat2);
    double rad = 6371000;
    double c = 2 * asin(sqrt(a));
    return rad * c;
}

vector<Vertex*> Data::getPreorderWalk() {
    for (Vertex* v : g.getVertexSet())
        v->setVisited(false);

    vector<Vertex*> preorderWalk;

    g.dfsPrim(g.getVertexSet()[0], preorderWalk);

    return preorderWalk;
}

double Data::tspTriangle() {
    double cost = 0;

    g.prim();

    vector<Vertex*> path = getPreorderWalk();
    path.push_back(g.getVertexSet()[0]);

    for (int i = 0; i < path.size() - 1; i++) {
        double dist = -1;
        for (Edge* e : path[i]->getAdj()) {
            if (e->getDest()->getId() == path[i + 1]->getId()) {
                dist = e->getWeight();
                break;
            }
        }

        if (dist == -1) dist = Data::haversine(path[i]->getLatitude(), path[i]->getLongitude(),
                                               path[i+1]->getLatitude(), path[i+1]->getLatitude());

        cost += dist;
    }

    return cost;
}