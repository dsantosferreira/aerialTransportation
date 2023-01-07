#ifndef AERIALTRANSPORTATION_GRAPH_H
#define AERIALTRANSPORTATION_GRAPH_H

#include <list>
#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <set>
#include "Airport.h"
//#include "../Database.h"

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
        list<pair<string, string>> parents; // First string is the airport; the second is the airline used
    };
    Graph();
    Graph(int num, bool dir = false);
    Graph(int num, airportHTable airports, bool dir = false);
    vector<list<pair<string, string>>> minFlightsBFS(string origin, unordered_set<string> destinations, unordered_set<string> airlines);
    void findPaths(vector<list<pair<string, string>>> &allPaths, string currAirportCode, list<pair<string, string>> aPath);
    void addEdge(string src, string dest, string airline, int weight = 0);
    unordered_map<string, Node> getNodes()const;
    set<string> reachedAirportsBFS(int maxFlights, string original ) ;
    void bfs(string origin, unordered_set<string> airlines, unordered_set<string> countries, airportHTable airports);
private:
    int n;
    bool hasDir;
    unordered_map<string, Node> nodes;
};

#endif