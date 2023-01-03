#ifndef AERIALTRANSPORTATION_GRAPH_H
#define AERIALTRANSPORTATION_GRAPH_H

#include <list>
#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include "Airport.h"

using namespace std;

typedef unordered_set<Airport, airportHash, airportHash> airportHTable;


class Graph {

public:
    struct Edge {
        string destCode;
        int weight;
        string airlineCode;
    };

    struct Node {
        list<Edge> adj;
        bool visited;
        int distance;
    };
    Graph();
    Graph(int num, bool dir = false);
    Graph(int num, airportHTable airports, bool dir = false);
    int minAirportFlightsBFS(string origin, string destination);
    int minCityFlightsBFS(string origin, string cityDest, airportHTable& airports);
    void addEdge(string src, string dest, string airline, int weight = 0);
    unordered_map<string, Node> getNodes()const;
private:
    int n;
    bool hasDir;
    unordered_map<string, Node> nodes;
};

#endif