#include "Graph.h"
#include <iostream>

Graph::Graph() {}

Graph::Graph(int num, bool dir) : n(num), hasDir(dir) {
}

void Graph::addEdge(string src, string dest, string airline, int weight) {
    if (nodes.find(src) == nodes.end() || nodes.find(dest) == nodes.end()) return;
    nodes[src].adj.push_back({dest, weight, airline});
    if (!hasDir) nodes[dest].adj.push_back({src, weight, airline});
}

Graph::Graph(int num, airportHTable airports, bool dir) : n(num), hasDir(dir) {
    for (Airport airport: airports) {
        nodes.insert({airport.getCode(), Node()});
    }
}

vector<list<pair<string, string>>> Graph::minFlightsBFS(string origin, unordered_set<string> destinations, unordered_set<string> airlines) {
    // Reset all nodes
    for (auto itr = nodes.begin(); itr != nodes.end(); itr++) {
        itr->second.distance = INT32_MAX;
        itr->second.parents.clear();
    }

    int minDist; // Distance of the first destination to the origin airport
    vector<list<pair<string, string>>> allPaths;  // Minimal paths from origin to destinations
    queue<string> toVisit; // airports to visit
    toVisit.push(origin);
    nodes[origin].distance = 0;

    while (!toVisit.empty()) {
        string currAirportCode = toVisit.front();
        Node currNode = nodes[currAirportCode];

        // Found the first destination
        if (destinations.find(currAirportCode) != destinations.end()) {
            minDist = currNode.distance; // Sets the minimal number of flights to get to the destination

            // Continues to see if there are other destinations at the same distance adding relevant airports to the paths
            while (!toVisit.empty() && nodes[toVisit.front()].distance == minDist) {
                if (destinations.find(currAirportCode) != destinations.end())
                    findPaths(allPaths, currAirportCode, list<pair<string, string>>());
                toVisit.pop();
                currAirportCode = toVisit.front();
            }
            break;
        }

        for (Edge edge: currNode.adj) {
            string neighbour = edge.destCode;

            // Checks the airline of the flight
            if (airlines.find(edge.airlineCode) != airlines.end()) {
                if (nodes[neighbour].distance > currNode.distance + 1) {
                    nodes[neighbour].distance = currNode.distance + 1;
                    nodes[neighbour].parents.push_back({currAirportCode, edge.airlineCode});
                    toVisit.push(neighbour);
                }
                else if (nodes[neighbour].distance == currNode.distance + 1)
                    nodes[neighbour].parents.push_back({currAirportCode, edge.airlineCode});
            }
        }
        toVisit.pop();
    }

    return allPaths;
}

void Graph::findPaths(vector<list<pair<string, string>>> &allPaths, string currAirportCode, list<pair<string, string>> aPath) {
    if (nodes[currAirportCode].parents.empty()) {
        Node a = nodes[currAirportCode];
        aPath.insert(aPath.begin(), {currAirportCode, ""});
        allPaths.push_back(aPath);
    }
    else {
        Node a = nodes[currAirportCode];
        for (pair<string, string> parent: nodes[currAirportCode].parents) {
            aPath.insert(aPath.begin(), {currAirportCode, parent.second});
            findPaths(allPaths, parent.first, aPath);
            aPath.erase(aPath.begin());
        }
    }
}