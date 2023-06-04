// By: Gonçalo Leão

#ifndef DA_TP_CLASSES_VERTEX_EDGE
#define DA_TP_CLASSES_VERTEX_EDGE

#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <algorithm>
#include "MutablePriorityQueue.h"

class Edge;

#define INF std::numeric_limits<double>::max()

/************************* Vertex  **************************/

class Vertex {
public:
    Vertex(int id);
    Vertex(int id, double latitude, double longitude);
    friend class MutablePriorityQueue<Vertex>;


    bool operator<(Vertex & vertex) const; // // required by MutablePriorityQueue

    int getId() const;
    std::vector<Edge *> getAdj() const;
    bool isVisited() const;
    double getDist() const;
    Vertex *getPath() const;
    std::vector<Edge *> getIncoming() const;

    void setId(int info);
    void setVisited(bool visited);
    void setDist(double dist);
    void setPath(Vertex *path);
    Edge * addEdge(Vertex *dest, double w);
    bool removeEdge(int destID);
    void removeOutgoingEdges();

    double getLongitude() const;
    double getLatitude() const;
    void setLatitude(double latitude);
    void setLongitude(double longitude);

    void clearReversePath();
    void addReversePath(Vertex* v);

    const std::vector<Vertex *> &getReversePath() const;

protected:
    int id;                // identifier
    std::vector<Edge *> adj;  // outgoing edges

    double longitude;
    double latitude;

    // auxiliary fields
    bool visited = false; // used by DFS, BFS, Prim ...
    double dist = 0;
    Vertex *path = nullptr;
    std::vector<Vertex*> reversePath;

    std::vector<Edge *> incoming; // incoming edges

    int queueIndex = 0; 		// required by MutablePriorityQueue and UFDS

    void deleteEdge(Edge *edge);
};

/********************** Edge  ****************************/

class Edge {
public:
    Edge(Vertex *orig, Vertex *dest, double w);

    Vertex * getDest() const;
    double getWeight() const;
    Vertex * getOrig() const;
    Edge *getReverse() const;

    void setReverse(Edge *reverse);
protected:
    Vertex * dest; // destination vertex
    double weight; // edge weight, can also be used for capacity

    // used for bidirectional edges
    Vertex *orig;
    Edge *reverse = nullptr;
};

#endif /* DA_TP_CLASSES_VERTEX_EDGE */