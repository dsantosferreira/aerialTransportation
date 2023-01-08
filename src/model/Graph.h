#ifndef AERIALTRANSPORTATION_GRAPH_H
#define AERIALTRANSPORTATION_GRAPH_H

#include <list>
#include <string>
#include <stack>
#include <set>
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <queue>

#include "Airport.h"
#include "Airline.h"


using namespace std;

typedef unordered_set<Airport, airportHash, airportHash> airportHTable;
typedef vector<pair<list<pair<string, string>>, float>> trips;
typedef pair<list<pair<string, string>>, float> trip;

class Graph {

public:
    struct Edge {
        string destCode;
        float weight;
        string airlineCode;
    };

    struct Node {
        list<Edge> adj;
        bool visited;
        bool inStack;
        int num;
        int low;
        int distance;
        list<pair<pair<string, string>, float>> parents; // First string is the airport; the second is the airline used
    };

    Graph();
    Graph(int num, bool dir = false);
    Graph(int num, airportHTable airports, bool dir = false);
    trips minFlightsBFS(string origin, unordered_set<string> destinations, unordered_set<string> airlines, const int maxAirlines);
    void findPaths(trips &allPaths, string currAirportCode, trip aPath, const int maxAirlines, unordered_set<string> usedAirlines);
    void addEdge(string src, string dest, string airline, airportHTable &airports, float weight = 0);
    void artPointsDfs(string origin, int &idx, stack<string> &beingVisited, const airportHTable &airports, const unordered_set<string> &airlines, vector<Airport> &artPoints);
    vector<Airport> artPoints(const airportHTable &airports, const unordered_set<string> &airlines);
    unordered_map<string, Node> getNodes()const;
    set<string> reachedAirportsBFS(int maxFlights, string original) ;
    vector<Edge> getEdges(string node);
private:
    int n;
    bool hasDir;
    unordered_map<string, Node> nodes;
};

#endif