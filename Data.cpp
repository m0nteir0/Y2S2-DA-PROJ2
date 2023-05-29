#include "Data.h"
#include <math.h>

bool Data::readToyData(string filename) {
    ifstream input(filename);
    if (input.is_open()) {
        string l;
        getline(input, l); // consumes label
        vector<string> fields;
        int orig, dest;
        float dist;
        string field;
        while (getline(input, l)) {
            stringstream iss(l);
            while (getline(iss, field, ',')) {
                fields.push_back(field);
            }
            orig = stoi(fields[0]);
            dest = stoi(fields[1]);
            dist = stof(fields[2]);
            fields.clear();

            g.addVertex(orig);
            g.addVertex(dest);
            g.addBidirectionalEdge(orig, dest, dist);
        }
        input.close();
        return true;
    } else {
        cout << "Unable to open file";
        return false;
    }
}

bool Data::readFullyConnectedData(string filename) {
    ifstream input(filename);
    if (input.is_open()) {
        string l;
        vector<string> fields;
        int orig, dest;
        float dist;
        string field;
        while (getline(input, l)) {
            stringstream iss(l);
            while (getline(iss, field, ',')) {
                fields.push_back(field);
            }
            orig = stoi(fields[0]);
            dest = stoi(fields[1]);
            dist = stof(fields[2]);
            fields.clear();

            g.addVertex(orig);
            g.addVertex(dest);
            g.addBidirectionalEdge(orig, dest, dist);
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

        int id;
        size_t first_comma, last_comma;
        double lat, lon;

        while (getline(input, l)) {
            first_comma = l.find_first_of(',');
            last_comma = l.find_last_of(',');

            id = stoi(l.substr(0, first_comma));
            lon = stod(l.substr(first_comma + 1, last_comma - first_comma - 1));
            lat = stod(l.substr(last_comma + 1, l.size() - last_comma));

            g.addVertex(id, lat, lon);
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

        int orig, dest;
        size_t first_comma, last_comma;
        double dist;

        while (getline(input, l)) {
            first_comma = l.find_first_of(',');
            last_comma = l.find_last_of(',');

            orig = stoi(l.substr(0, first_comma));
            dest = stoi(l.substr(first_comma + 1, last_comma - first_comma - 1));
            dist = stod(l.substr(last_comma + 1, l.size() - last_comma));

            g.addBidirectionalEdge(orig, dest, dist);
        }
        input.close();
        return true;
    } else {
        cout << "Unable to open file";
        return false;
    }
}

void Data::tspBTAux(unsigned int n, int path[], int currentPath[],
         double curr, double &best, unsigned int curr_n) {
    if (curr_n == n) {               //visited all nodes
        bool canReturn = false;
        for (Edge* e : g.getVertexSet()[currentPath[curr_n - 1]]->getAdj()){
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

    for (Edge* e : g.getVertexSet()[currentPath[curr_n - 1]]->getAdj()){
        if (!e->getDest()->isVisited()){
            currentPath[curr_n] = e->getDest()->getId();
            e->getDest()->setVisited(true);

            tspBTAux(n, path, currentPath, curr + e->getWeight(), best, curr_n + 1);

            e->getDest()->setVisited(false);
        }
    }
}

double Data::tspBT(unsigned int n, int path[]) {
    for (auto& v : g.getVertexSet())
        v.second->setVisited(false);
    int currentPath[n];
    currentPath[0] = 0;
    g.getVertexSet()[0]->setVisited(true);
    double best = std::numeric_limits<double>::max();

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
    for (auto& v : g.getVertexSet())
        v.second->setVisited(false);

    vector<Vertex*> preorderWalk;

    g.dfsPrim(g.getVertexSet()[0], preorderWalk);

    return preorderWalk;
}

double Data::tspTriangle(vector<Vertex*> &path) {
    double cost = 0;

    g.prim();

    path = getPreorderWalk();
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
                                               path[i+1]->getLatitude(), path[i+1]->getLongitude());

        cost += dist;
    }

    return cost;
}

vector<Vertex*> Data::tspNearestNeighbour() {
    for (auto& v : g.getVertexSet())
        v.second->setVisited(false);

    vector<Vertex*> path;
    path.push_back(g.getVertexSet()[0]);
    g.getVertexSet()[0]->setVisited(true);

    while (path.size() < g.getVertexSet().size()) {
        double minDist = INF;
        Vertex* minV = nullptr;

        for (Edge* e : path.back()->getAdj()) {
            if (!e->getDest()->isVisited() && e->getWeight() < minDist) {
                minDist = e->getWeight();
                minV = e->getDest();
                e->getDest()->setPath(path.back());
            }
        }

        if (minV == nullptr) {
            cout << "The graph is not complete...\n";
            break;
        }

        minV->setVisited(true);
        path.push_back(minV);
    }

    path.push_back(g.getVertexSet()[0]);

    for (Vertex* v : path)
        cout << v->getId() << ' ';
    cout << endl;

    return path;
}


/*i want an algorithm for TSP using Nearest Neighbour and 2-opt
 * 1. start at a vertex 0
 * 2. find the nearest vertex
 * 3. find the nearest vertex to the nearest vertex
 * 4. repeat until all vertices are visited
 * 5. apply 2-opt
 * 6. repeat until no improvement
 * */
double Data::getPathDist(vector<Vertex *> path) {
    double dist = 0;

    for (int i = 0; i < path.size() - 1; i++) {
        for (Edge* e : path[i]->getAdj()) {
            if (e->getDest() == path[i + 1]) {
                dist += e->getWeight();
                break;
            }
        }
    }
    return dist;
}

vector<Vertex *> Data::swap2opt(vector<Vertex *> path, int start, int end) {
    vector<Vertex*> swapped_path;

    for (int i = 0; i <= start; i++)
        swapped_path.push_back(path[i]);

    for (int i = end; i > start; i--)
        swapped_path.push_back(path[i]);

    for (int i = end + 1; i < path.size(); i++)
        swapped_path.push_back(path[i]);

    return swapped_path;
}

double Data::tsp2opt(vector<Vertex*> path) {
    bool improved = true;
    double path_dist = INF;
    int iterations = 0;

    while (improved && iterations++ < 1) {
        improved = false;
        path_dist = getPathDist(path);

        for (int i = 1; i <= path.size() - 3; i++) {            //start and end node can't be swapped
            for (int j = i + 1; j <= path.size() - 2; j++) {
                vector<Vertex*> temp_path = swap2opt(path, i, j);
                double temp_dist = getPathDist(temp_path);

                if (temp_dist < path_dist) {
                    path = temp_path;
                    path_dist = temp_dist;
                    improved = true;
                }
            }
        }

    }

    return path_dist;
}

