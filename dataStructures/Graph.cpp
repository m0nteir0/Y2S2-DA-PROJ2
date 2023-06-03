// By: Gonçalo Leão

#include "Graph.h"
#include "../algorithms/Data.h"

//=================================== PROVIDED TO US ======================================================
int Graph::getNumVertex() const {
    return vertexSet.size();
}

std::unordered_map<int, Vertex*> Graph::getVertexSet() const {
    return vertexSet;
}

/*
 *  Adds a vertex with a given content or info (in) to a graph (this).
 *  Returns true if successful, and false if a vertex with that content already exists.
 */
bool Graph::addVertex(const int &id) {
    return vertexSet.insert({id, new Vertex(id)}).second;
}

bool Graph::addVertex(const int &id, double latitude, double longitude) {
    return vertexSet.insert({id, new Vertex(id, latitude, longitude)}).second;
}

/*
 * Adds an edge to a graph (this), given the contents of the source and
 * destination vertices and the edge weight (w).
 * Returns true if successful, and false if the source or destination vertex does not exist.
 */
bool Graph::addEdge(const int &sourc, const int &dest, double w) {
    auto v1 = vertexSet.find(sourc);
    auto v2 = vertexSet.find(dest);
    if (v1 == vertexSet.end() || v2 == vertexSet.end())
        return false;
    (*v1).second->addEdge((*v2).second, w);
    return true;
}

bool Graph::addBidirectionalEdge(const int &sourc, const int &dest, double w) {
    auto v1 = vertexSet.find(sourc);
    auto v2 = vertexSet.find(dest);
    if (v1 == vertexSet.end() || v2 == vertexSet.end())
        return false;
    auto e1 = (*v1).second->addEdge((*v2).second, w);
    auto e2 = (*v2).second->addEdge((*v1).second, w);
    e1->setReverse(e2);
    e2->setReverse(e1);
    return true;
}

void deleteMatrix(int **m, int n) {
    if (m != nullptr) {
        for (int i = 0; i < n; i++)
            if (m[i] != nullptr)
                delete [] m[i];
        delete [] m;
    }
}

void deleteMatrix(double **m, int n) {
    if (m != nullptr) {
        for (int i = 0; i < n; i++)
            if (m[i] != nullptr)
                delete [] m[i];
        delete [] m;
    }
}

Graph::~Graph() {
    deleteMatrix(distMatrix, vertexSet.size());
    deleteMatrix(pathMatrix, vertexSet.size());
}

void Graph::clearGraph() {
    for (auto &v : vertexSet)
        delete v.second;
    vertexSet.clear();
}

//================== FOR OUR ALGORITHMS =======================================


/**
 * @brief Constructs a minimum spanning tree using Prim's algorithm and returns its total weight.
 *
 * The function constructs a minimum spanning tree of the graph using Prim's algorithm.
 * Iteratively selects the vertex with the minimum distance from the priority queue and marks it as visited.
 * For each unvisited vertex, it checks if there is a direct edge from the selected vertex to that vertex.
 * If such an edge exists, it updates the distance and path information of the vertex if the new distance is smaller.
 * If there is no direct edge, uses the Haversine formula.
 * If the new distance is smaller than the previous distance, the vertex is inserted or updated in the priority queue accordingly.
 * Finally, the function establishes the reverse path connections between vertices in the minimum spanning tree.
 *
 * COMPLEXITY: O(E * log(V)), where V is the number of vertices in the graph and E the number of edges.
 * O( (E+V) * log(V)) ?
 *
 * @return The total weight of the minimum spanning tree.
 */
double Graph::prim() {

    MutablePriorityQueue<Vertex> q;

    for(auto &v : vertexSet){
        v.second->setDist(INF);
        v.second->setVisited(false);
        v.second->setPath(nullptr);
        v.second->clearReversePath();
    }

    vertexSet[0]->setDist(0);
    q.insert(vertexSet[0]);

    double sum = 0;
    while(!q.empty()){
        auto u = q.extractMin();
        u->setVisited(true);

        for (auto &vertex : vertexSet) {
            if (vertex.second->getId() != u->getId() && !vertex.second->isVisited()) {
                double dist = -1;
                for (auto &e: u->getAdj()) {
                    auto v = e->getDest();
                    if (v->getId() == vertex.second->getId()) {
                        dist = e->getWeight();
                        break;
                    }
                }
                if (dist == -1) {
                    dist = Data::haversine(u->getLatitude(), u->getLongitude(), vertex.second->getLatitude(), vertex.second->getLongitude());
                }

                if (dist < vertex.second->getDist()) {
                    vertex.second->setPath(u);
                    double oldDist = vertex.second->getDist();
                    vertex.second->setDist(dist);
                    sum += dist;
                    if (oldDist != INF) {
                        sum -= oldDist;
                        q.decreaseKey(vertex.second);
                    } else {
                        q.insert(vertex.second);
                    }
                }
            }
        }
    }

    for (auto& v : vertexSet) {
        if (v.second->getPath() != nullptr)
            v.second->getPath()->addReversePath(v.second);
    }

    return sum;
}

/**
 * @brief Constructs a minimum spanning tree using Prim's algorithm.
 *
 * The function constructs a minimum spanning tree of the graph using Prim's algorithm.
 * Iteratively selects the vertex with the minimum distance from the priority queue and marks it as visited.
 * For each unvisited vertex, it checks if there is a direct edge from the selected vertex to that vertex.
 * If such an edge exists, it updates the distance and path information of the vertex if the new distance is smaller.
 * If there is no direct edge, uses the Haversine formula.
 * If the new distance is smaller than the previous distance, the vertex is inserted or updated in the priority queue accordingly.
 * Finally, the function establishes the reverse path connections between vertices in the minimum spanning tree.
 *
 * COMPLEXITY: O(E * log(V)), where V is the number of vertices in the graph and E the number of edges.
 * O( (E+V) * log(V)) ?
 */
/*
void Graph::prim() {

    MutablePriorityQueue<Vertex> q;

    for(auto &v : vertexSet){
        v.second->setDist(INF);
        v.second->setVisited(false);
        v.second->setPath(nullptr);
        v.second->clearReversePath();
    }

    vertexSet[0]->setDist(0);
    q.insert(vertexSet[0]);

    while(!q.empty()){
        auto u = q.extractMin();
        u->setVisited(true);

        for (auto &vertex : vertexSet) {
            if (vertex.second->getId() != u->getId() && !vertex.second->isVisited()) {
                double dist = -1;
                for (auto &e: u->getAdj()) {
                    auto v = e->getDest();
                    if (v->getId() == vertex.second->getId()) {
                        dist = e->getWeight();
                        break;
                    }
                }
                if (dist == -1) {
                    dist = Data::haversine(u->getLatitude(), u->getLongitude(), vertex.second->getLatitude(), vertex.second->getLongitude());
                }

                if (dist < vertex.second->getDist()) {
                    vertex.second->setPath(u);
                    double oldDist = vertex.second->getDist();
                    vertex.second->setDist(dist);

                    if (oldDist != INF) {
                        q.decreaseKey(vertex.second);
                    } else {
                        q.insert(vertex.second);
                    }
                }
            }
        }
    }

    for (auto& v : vertexSet) {
        if (v.second->getPath() != nullptr)
            v.second->getPath()->addReversePath(v.second);
    }

}
*/
/**
 * @brief Performs a Depth-First Search traversal on the minimum spanning tree rooted at the specified source vertex.
 * This function recursively traverses the minimum spanning tree in a depth-first manner starting from the given source vertex.
 * It marks each visited vertex as visited and adds it to the resulting vector in the order of the traversal.
 * For each vertex in the reverse path of the current vertex, it recursively calls the dfsPrim function if the vertex has not been visited.
 *
 * COMPLEXITY: O(V), where V is the number of vertices
 *
 * @param source Vertex pointer that represents the source vertex from which the traversal starts.
 * @param res A vector of Vertex pointers to store the resulting traversal path.
 *
 */
void Graph::dfsPrim(Vertex* source, vector<Vertex*>& res) {
    source->setVisited(true);
    res.push_back(source);
    for (Vertex* dest : source->getReversePath())
        if (!dest->isVisited())
            dfsPrim(dest, res);
}
