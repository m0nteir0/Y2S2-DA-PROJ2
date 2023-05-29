// By: Gonçalo Leão

#include "Graph.h"
#include "Data.h"

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

//================== T4.2 =======================================
 /*
  * - para cada vertice percorrer todos os vertices do grafo
- verificar se existe uma edge a ligar, senão calcular distancia com haversine
- prosseguir normalmente com o algoritmo
  */



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

void Graph::dfsPrim(Vertex* source, vector<Vertex*>& res) {
    source->setVisited(true);
    res.push_back(source);
    for (Vertex* dest : source->getReversePath())
        if (!dest->isVisited())
            dfsPrim(dest, res);
}
