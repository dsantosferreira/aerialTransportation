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
    /** @brief Representation of a flight */
    struct Edge {
        /** @brief code of the destination airport*/
        string destCode;

        /** @brief distance travelled by the flight*/
        float weight;

        /** @brief airline used on the flight*/
        string airlineCode;
    };

    /** @brief Representation of an airport */
    struct Node {
        /** @brief list of flights from that airport*/
        list<Edge> adj;

        /** @brief whether a node has been visited or not*/
        bool visited;

        /** @brief whether a node is in a stack or not*/
        bool inStack;

        /** @brief Order in which the node has been traversed*/
        int num;

        /** @brief Lowest num value of all the nodes the current node can travel to*/
        int low;

        /** @brief Distance from a certain reference node */
        int distance;

        /** @brief Parents of a node. Each parent is associated of its airport code, airline used on the flight and distance of that flight*/
        list<pair<pair<string, string>, float>> parents;
    };

    Graph();
    Graph(int num, airportHTable airports, bool dir = false);
    trips minFlightsBFS(unordered_set<string> origin, unordered_set<string> destinations, unordered_set<string> airlines, const int maxAirlines);
    void findPaths(trips &allPaths, string currAirportCode, trip aPath, const int maxAirlines, unordered_set<string> usedAirlines);
    void addEdge(string src, string dest, string airline, float weight = 0);
    void artPointsDfs(string origin, int &idx, stack<string> &beingVisited, const airportHTable &airports, const unordered_set<string> &airlines, vector<Airport> &artPoints);
    vector<Airport> artPoints(const airportHTable &airports, const unordered_set<string> &airlines);
    unordered_map<string, Node> getNodes()const;
    set<string> reachedAirportsBFS(int maxFlights, string original) ;
    vector<Edge> getEdges(string node);
    int diameterBfs(string origin, string airline, string country, const airportHTable &airports);

private:

    /** @var number of nodes in the graph*/
    int n;

    /** @var is the graph directed*/
    bool hasDir;

    /** @var nodes of the graph */
    unordered_map<string, Node> nodes;
};

#endif