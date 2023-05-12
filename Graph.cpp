// By: Gonçalo Leão

#include "Graph.h"
#include "Data.h"

int Graph::getNumVertex() const {
    return vertexSet.size();
}

std::vector<Vertex *> Graph::getVertexSet() const {
    return vertexSet;
}

/*
 * Auxiliary function to find a vertex with a given content.
 */
Vertex * Graph::findVertex(const int &id) const {
    for (auto v : vertexSet)
        if (v->getId() == id)
            return v;
    return nullptr;
}

/*
 * Finds the index of the vertex with a given content.
 */
int Graph::findVertexIdx(const int &id) const {
    for (unsigned i = 0; i < vertexSet.size(); i++)
        if (vertexSet[i]->getId() == id)
            return i;
    return -1;
}
/*
 *  Adds a vertex with a given content or info (in) to a graph (this).
 *  Returns true if successful, and false if a vertex with that content already exists.
 */
bool Graph::addVertex(const int &id) {
    if (findVertex(id) != nullptr)
        return false;
    vertexSet.push_back(new Vertex(id));
    return true;
}

bool Graph::addVertex(const int &id, float longitude, float latitude) {
    if (findVertex(id) != nullptr)
        return false;
    vertexSet.push_back(new Vertex(id, longitude, latitude));
    return true;
}

/*
 * Adds an edge to a graph (this), given the contents of the source and
 * destination vertices and the edge weight (w).
 * Returns true if successful, and false if the source or destination vertex does not exist.
 */
bool Graph::addEdge(const int &sourc, const int &dest, double w) {
    auto v1 = findVertex(sourc);
    auto v2 = findVertex(dest);
    if (v1 == nullptr || v2 == nullptr)
        return false;
    v1->addEdge(v2, w);
    return true;
}

bool Graph::addBidirectionalEdge(const int &sourc, const int &dest, double w) {
    auto v1 = findVertex(sourc);
    auto v2 = findVertex(dest);
    if (v1 == nullptr || v2 == nullptr)
        return false;
    auto e1 = v1->addEdge(v2, w);
    auto e2 = v2->addEdge(v1, w);
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

//================== T4.2 =======================================
 /*
  * - para cada vertice percorrer todos os vertices do grafo
- verificar se existe uma edge a ligar, senão calcular distancia com haversine
- prosseguir normalmente com o algoritmo
  */

double Graph::prim() {

    MutablePriorityQueue<Vertex> q;

    for(auto &v : vertexSet){
        v->setDist(INF);
        v->setPath(nullptr);
    }

    vertexSet[0]->setDist(0);
    q.insert(vertexSet[0]);

    double sum = 0;

    while(!q.empty()){
        auto u = q.extractMin();
        u->setVisited(true);

        for (auto &vertex : vertexSet) {
            if (vertex->getId() != u->getId()) {
                double dist = -1;
                for (auto &e: u->getAdj()) {
                    auto v = e->getDest();
                    if (v == vertex) {
                        dist = e->getWeight();
                        break;
                    }
                }
                if (dist == -1) {
                    dist = Data::haversine(u->getLatitude(), u->getLongitude(), vertex->getLatitude(), vertex->getLatitude());
                    // may not be necessary
                    addBidirectionalEdge(u->getId(), vertex->getId(), dist);

                }

                if (!vertex->isVisited() && dist < vertex->getDist()) {
                    vertex->setPath(u);
                    sum += dist;
                    auto oldDist = vertex->getDist();
                    vertex->setDist(dist);

                    if (oldDist != INF) {
                        sum -= oldDist;
                        q.decreaseKey(vertex);
                    } else {
                        q.insert(vertex);
                    }
                }
            }
        }
    }

    return sum;
}