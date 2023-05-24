#include "Data.h"
#include <math.h>

bool Data::readToyData(string filename) {
    ifstream input(filename);
    if (input.is_open()) {
        string l;
        getline(input, l); // consumes label

        int orig, dest;
        size_t first_comma, last_comma;
        double distance;

        while (getline(input, l)) {
            first_comma = l.find_first_of(',');
            last_comma = l.find_last_of(',');

            orig = stoi(l.substr(0, first_comma));
            dest = stoi(l.substr(first_comma + 1, last_comma - first_comma - 1));
            distance = stod(l.substr(last_comma + 1, l.size() - last_comma));

            g.addVertex(orig);
            g.addVertex(dest);
            g.addBidirectionalEdge(orig, dest, distance);
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

double Data::tspTriangle() {
    double cost = 0;

    g.prim();

    vector<Vertex*> path = getPreorderWalk();
    for (Vertex* v : path)
        cout << v->getId() << ' ';
    cout << endl;
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