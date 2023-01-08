#ifndef AERIALTRANSPORTATION_GRAPH_H
#define AERIALTRANSPORTATION_GRAPH_H

#include <list>
#include <string>
#include <stack>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <queue>

#include "Airport.h"
#include "Airline.h"


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
        bool inStack;
        int num;
        int low;
        int distance;
        list<pair<string, string>> parents; // First string is the airport; the second is the airline used
    };

    Graph();
    Graph(int num, bool dir = false);
    Graph(int num, airportHTable airports, bool dir = false);
    vector<list<pair<string, string>>> minFlightsBFS(string origin, unordered_set<string> destinations, unordered_set<string> airlines);
    void findPaths(vector<list<pair<string, string>>> &allPaths, string currAirportCode, list<pair<string, string>> aPath);
    void addEdge(string src, string dest, string airline, int weight = 0);
    void artPointsDfs(string origin, int &idx, stack<string> &beingVisited, const airportHTable &airports, const unordered_set<string> &airlines, vector<Airport> &artPoints);
    vector<Airport> artPoints(const airportHTable &airports, const unordered_set<string> &airlines);
    unordered_map<string, Node> getNodes()const;
    set<string> reachedAirportsBFS(int maxFlights, string original ) ;
    vector<Edge> getEdges(string node);
    int bfs(string origin, const unordered_set<string> &airlines, const unordered_set<string> &countries, const airportHTable &airports);

private:
    int n;
    bool hasDir;
    unordered_map<string, Node> nodes;
};

#endif