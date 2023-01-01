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

int Graph::minAirportFlightsBFS(string origin, string destination) {
    // Reset all nodes
    for (auto itr = nodes.begin(); itr != nodes.end(); itr++) {
        itr->second.visited = false;
        itr->second.distance = 0;
    }

    queue<string> toVisit;
    toVisit.push(origin);
    nodes[origin].visited = true;

    while (!toVisit.empty()) {
        string currAirportCode = toVisit.front();
        Node currNode = nodes[currAirportCode];

        if (currAirportCode == destination)
            return currNode.distance;

        for (Edge edge: currNode.adj) {
            if (!nodes[edge.destCode].visited) {
                toVisit.push(edge.destCode);
                nodes[edge.destCode].visited = true;
                nodes[edge.destCode].distance = nodes[currAirportCode].distance + 1;
            }
        }
        toVisit.pop();
    }

    return -1;
}

int Graph::minCityFlightsBFS(string origin, string cityDest, airportHTable &airports) {
    // Reset all nodes
    for (auto itr = nodes.begin(); itr != nodes.end(); itr++) {
        itr->second.visited = false;
        itr->second.distance = 0;
    }

    queue<string> toVisit;
    toVisit.push(origin);
    nodes[origin].visited = true;

    while (!toVisit.empty()) {
        string currAirportCode = toVisit.front();
        Node currNode = nodes[currAirportCode];

        if (airports.find(Airport(currAirportCode, "", "", "", 0, 0))->getCity() == cityDest)
            return currNode.distance;

        for (Edge edge: currNode.adj) {
            if (!nodes[edge.destCode].visited) {
                toVisit.push(edge.destCode);
                nodes[edge.destCode].visited = true;
                nodes[edge.destCode].distance = nodes[currAirportCode].distance + 1;
            }
        }
        toVisit.pop();
    }

    return -1;
}