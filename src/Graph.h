#ifndef AERIALTRANSPORTATION_GRAPH_H
#define AERIALTRANSPORTATION_GRAPH_H

#include <list>
#include <vector>
#include <string>

using namespace std;

class Graph {
    struct Edge {
        int dest;
        int weight;
        string airlineCode;
    };

    struct Node {
        list<Edge> adj;
        bool visited;
        int distance;
    };

    int n;
    bool hasDir;
    vector<Node> nodes;

public:
    Graph(int nodes, bool dir = false);
    void addEdge(int src, int dest, int weight = 1);
};

#endif
