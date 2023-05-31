#include "Data.h"
#include <math.h>


Graph &Data::getG() {
    return g;
}

/*============================= READ FUNCTIONS =============================*/

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

/*============================= ALGORITHMIC FUNCTIONS =============================*/

//------------ T2.1 -------------- */

/**
 * @brief Auxiliar function to solve the Travelling Salesperson Problem (TSP) using a Backtracking algorithm.
 *
 * This function finds the shortest path that visits all nodes in the graph, starting from node 0 and returning to it.
 * It uses a Backtracking algorithm to explore all possible paths and keeps track of the best path found.
 *
 * COMPLEXITY: O(V!)
 *
 * @param n The number of nodes in the graph.
 * @param path An array to store the resulting path.
 * @param currentPath An array to store the current path being explored.
 * @param curr The current cost of the path being explored.
 * @param best The best cost found so far.
 * @param curr_n The current number of nodes visited in the path.
 */
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

/**
 * @brief Solves the Travelling Salesperson Problem (TSP) using a Backtracking algorithm.
 *
 * This function finds the shortest path that visits all nodes in the graph, starting from node 0 and returning to it.
 * It uses a Backtracking algorithm by calling the auxiliary function tspBTAux.
 * Explores all possible paths and returns the cost of the best path found.
 * It's only useful for small graphs, because of its time complexity.
 *
 * COMPLEXITY: O(V!)
 *
 * @param n The number of nodes in the graph.
 * @param path An array to store the resulting path.
 * @return The cost of the best path found.
 */
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

//-----------------T2.2-----------------//

/**
 * @brief Calculates distance between two nodes using the Haversine formula with the values of each latitude and longitude.
 *
 * COMPLEXITY: O(1)
 *
 * @param lat1 latitude of the first node
 * @param lon1 longitude of the first node
 * @param lat2 latitude of the second node
 * @param lon2 longitude of the second node
 * @return distance between the two nodes
 */
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

/**
 * @brief Get the Preorder Walk of the Graph.
 *
 * This function returns a vector of vertices representing the preorder walk of the graph. The preorder walk is obtained by performing a Depth-First Search (DFS) traversal starting from the first vertex of the graph.
 *
 * COMPLEXITY: O(V)
 *
 * @return path A vector of vertices representing the preorder walk of the graph.
 */
vector<Vertex*> Data::getPreorderWalk() {
    for (auto& v : g.getVertexSet())
        v.second->setVisited(false);

    vector<Vertex*> preorderWalk;

    g.dfsPrim(g.getVertexSet()[0], preorderWalk);

    return preorderWalk;
}

/**
 * @brief Calculates the cost of the TSP path using the Triangle Inequality heuristic.
 *
 * It first constructs a minimum spanning tree of the graph using Prim's algorithm.
 * Then, it generates a preorder walk of the minimum spanning tree and appends the starting vertex to form a closed path.
 * Finally, it calculates the total cost of the path by summing the weights of the edges.
 * If a direct edge exists between two adjacent vertices in the path, the weight of that edge is used.
 * Otherwise, the Haversine formula is used to calculate the distance between the vertices based on their coordinates.
 *
 * COMPLEXITY: O(V+E) / COMPLEXITY do prim?
 *
 * @param path A vector of Vertex pointers to store the resulting path.
 * @return The cost of the path.
 */
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

//-----------------T2.3-----------------//

/**
 * @brief Calculates the cost of the Travelling Salesperson Problem (TSP) path using the Nearest Neighbour heuristic.
 *
 * Starts with vertex 0 as the starting point and repeatedly selects the nearest unvisited vertex to extend the current path.
 * This process continues until all vertices have been visited, and then the path is closed by returning to the initial vertex.
 * The resulting path may not always be the optimal solution, but it provides a reasonably good approximation.
 *
 * COMPLEXITY: O(V^2)
 *
 * @return A vector of Vertex pointers representing the TSP path generated by the Nearest Neighbour heuristic.
 *         The path starts and ends at the same vertex, forming a closed loop.
 *         If the graph is not complete (some vertices are not connected), an empty path is returned.
 */
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
            return {};
        }

        minV->setVisited(true);
        path.push_back(minV);
    }

    path.push_back(g.getVertexSet()[0]);
    return path;
}

/**
 * @brief Calculates the sum of the weights of the edges in a path.
 *
 * COMPLEXITY: O(V)
 *
 * @param path A vector of Vertex pointers representing the path.
 * @return The sum of the weights of the edges in the path.
 */
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

/**
 * @brief Swaps a portion of the given path using the 2-opt technique.
 *
 * COMPLEXITY: O(V), where V is the number of vertices
 *
 * @param path The original path to be modified.
 * @param start The starting index of the portion to be swapped.
 * @param end The ending index of the portion to be swapped.
 * @return The modified path with the specified portion swapped.
 */
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

/**
 * @brief Applies the 2-opt algorithm to improve the given TSP path.
 *
 * The 2-opt algorithm is an iterative algorithm that attempts to improve an existing path by swapping two edges.
 * It does this by trying to find two edges that, if swapped, would result in a shorter path.
 * If such edges are found, the swap is performed and the process is repeated until no further improvements can be made.
 * The algorithm is guaranteed to terminate, and it is also guaranteed to never produce a path longer than the original.
 * However, it is not guaranteed to produce the shortest possible path.
 *
 * COMPLEXITY: O(V^2 + E), where V is the number of vertices
 *
 * @param path The TSP path to be optimized.
 * @param maxIterations The maximum number of iterations to perform.
 * @return The optimized TSP path's total distance.
 */
double Data::tsp2opt(vector<Vertex*> &path, int maxIterations) {
    bool improved = true;
    double path_dist = getPathDist(path);
    int iterations = 0;

    while (improved && iterations++ < maxIterations) {
        improved = false;

        for (int i = 1; i <= path.size() - 3; i++) {    //start and end node can't be swapped
            for (int j = i + 1; j <= path.size() - 2; j++) {
                double temp_dist = path_dist;

                //the path that gets reversed goes from [i+1, j]
                for (Edge* e : path[i]->getAdj()) {
                    if (e->getDest()->getId() == path[j]->getId())
                        temp_dist += e->getWeight();
                    else if (e->getDest()->getId() == path[i+1]->getId())
                        temp_dist -= e->getWeight();
                }

                for (Edge* e : path[j + 1]->getAdj()) {
                    if (e->getDest()->getId() == path[i+1]->getId())
                        temp_dist += e->getWeight();
                    else if (e->getDest()->getId() == path[j]->getId())
                        temp_dist -= e->getWeight();
                }

                if (temp_dist < path_dist) {
                    path = swap2opt(path, i, j);
                    path_dist = temp_dist;
                    improved = true;
                }
            }
        }

    }

    return path_dist;
}

/* extra for t2.3 */

vector<Vertex*> Data::swap3opt(vector<Vertex*> path, int start, int mid, int end) {
    vector<Vertex*> swapped_path;

    for (int i = 0; i <= start; i++)
        swapped_path.push_back(path[i]);

    //TODO check this loop
    for (int i = mid + 1; i <= end; i++)
        swapped_path.push_back(path[i]);

    //TODO check this loop
    for (int i = start + 1; i <= mid; i++)
        swapped_path.push_back(path[i]);

    for (int i = end + 1; i < path.size(); i++)
        swapped_path.push_back(path[i]);

    return swapped_path;
}

double Data::tsp3opt(vector<Vertex*>& path, int maxIterations) {
    bool improved = true;
    double path_dist = getPathDist(path);
    int iterations = 0;


    while (improved && iterations++ < maxIterations) {
        improved = false;

        for (int i = 1; i <= path.size() - 4; i++) {  // start and end node can't be swapped
            for (int j = i + 1; j <= path.size() - 3; j++) {
                for (int k = j + 1; k <= path.size() - 2; k++) {
                    double d1 = path_dist, d2 = path_dist, d3 = path_dist, d4 = path_dist;

                    for (Edge* e : path[i]->getAdj()) {
                        if (e->getDest()->getId() == path[j]->getId()) {
                            d1 += e->getWeight();
                        }
                        else if (e->getDest()->getId() == path[i + 1]->getId()) {
                            d1 -= e->getWeight();
                            d3 -= e->getWeight();
                            d4 -= e->getWeight();
                        } else if (e->getDest()->getId() == path[j + 1]->getId()) {
                            d3 += e->getWeight();
                        }
                        else if (e->getDest()->getId() == path[k]->getId()) {
                            d4 += e->getWeight();
                        }
                    }

                    for (Edge* e : path[i + 1]->getAdj()) {
                        if (e->getDest()->getId() == path[k + 1]->getId()) {
                            d4 += e->getWeight();
                        }
                    }

                    for (Edge* e : path[j]->getAdj()) {
                        if (e->getDest()->getId() == path[j + 1]->getId()) {
                            d1 -= e->getWeight();
                            d2 -= e->getWeight();
                            d3 -= e->getWeight();
                        }
                        else if (e->getDest()->getId() == path[k]->getId()) {
                            d2 += e->getWeight();
                        }
                        else if (e->getDest()->getId() == path[k+1]->getId()) {
                            d3 += e->getWeight();
                        }
                    }

                    for (Edge* e : path[j+1]->getAdj()) {
                        if (e->getDest()->getId() == path[i + 1]->getId()) {
                            d1 += e->getWeight();
                        }
                        else if (e->getDest()->getId() == path[k + 1]->getId()) {
                            d2 += e->getWeight();
                        }
                    }

                    for (Edge* e : path[k]->getAdj()) {
                        if (e->getDest()->getId() == path[k + 1]->getId()) {
                            d2 -= e->getWeight();
                            d3 -= e->getWeight();
                            d4 -= e->getWeight();
                        }
                        else if (e->getDest()->getId() == path[i + 1]->getId()) {
                            d3 += e->getWeight();
                        }
                    }

                    if (d1 < path_dist) {
                        path = swap2opt(path, i, j);
                        path_dist = d1;
                        improved = true;
                    } else if (d2 < path_dist) {
                        path = swap2opt(path, j, k);
                        path_dist = d2;
                        improved = true;
                    } else if (d4 < path_dist) {
                        path = swap2opt(path, i, k);
                        path_dist = d4;
                        improved = true;
                    } else if (d3 < path_dist) {
                        path = swap3opt(path, i, j, k);
                        path_dist = d3;
                        improved = true;
                    }
                }
            }
        }
    }

    return path_dist;
}
