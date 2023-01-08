#include "Graph.h"
#include "../Database.h"
#include <iostream>
#include <set>

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

unordered_map<string, Graph::Node> Graph::getNodes() const {
    return this->nodes;
}

vector<Airport> Graph::artPoints(const airportHTable &airports, const unordered_set<string> &airlines) {
    vector<Airport> articulationPoints;
    stack<string> beingVisited;
    int order;

    for (auto itr = nodes.begin(); itr != nodes.end(); itr++) {
        itr->second.num = 0;
        itr->second.low = 0;
        itr->second.inStack = false;
    }

    for (auto itr = nodes.begin(); itr != nodes.end(); itr++) {
        order = 1;
        if (nodes[itr->first].num == 0) {
            artPointsDfs(itr->first, order, beingVisited, airports, airlines, articulationPoints);
        }
    }

    return articulationPoints;
}

void Graph::artPointsDfs(string origin, int &idx, stack<string> &beingVisited, const airportHTable &airports, const unordered_set<string> &airlines, vector<Airport> &artPoints) {
    bool isArtPoint = false;
    int children = 0;
    beingVisited.push(origin);
    nodes[origin].num = nodes[origin].low = idx++;
    nodes[origin].inStack = true;

    for (Edge e: nodes[origin].adj) {
        if (airlines.find(e.airlineCode) != airlines.end()) {
            string neighbour = e.destCode;

            if (nodes[neighbour].num == 0) {
                children++;
                artPointsDfs(neighbour, idx, beingVisited, airports, airlines, artPoints);
                nodes[origin].low = min(nodes[neighbour].low, nodes[origin].low);
                if (nodes[neighbour].low >= nodes[origin].num) {
                    isArtPoint = true;
                }
            }
            else if (nodes[neighbour].inStack) {
                nodes[origin].low = min(nodes[origin].low, nodes[neighbour].num);
            }
        }
    }

    nodes[origin].inStack = false;
    beingVisited.pop();

    if ((isArtPoint && !beingVisited.empty()) || (beingVisited.empty() && children > 1))
        artPoints.push_back(*airports.find(Airport(origin, "", "", "", 0, 0)));
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
        if (destinations.find(currAirportCode) != destinations.end() && currAirportCode != origin) {
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

set<string> Graph::reachedAirportsBFS( int maxFlights, string original)  {
    for (auto itr = nodes.begin(); itr != nodes.end(); itr++) {
        itr->second.distance = INT32_MAX;
        itr->second.parents.clear();
        itr->second.visited=false;
    }
    queue<string> q;
    set<string> visited;
    q.push(original);
    nodes[original].distance=0;
    nodes[original].visited=true;
    while( !q.empty()){
        string curr= q.front();
        q.pop();
        for(auto e:nodes[curr].adj){
            string neighbour= e.destCode;
            nodes[neighbour].distance=nodes[curr].distance+1;
            visited.insert(neighbour);
            if(nodes[neighbour].distance<maxFlights and !nodes[neighbour].visited ){
                q.push(neighbour);
                nodes[neighbour].visited=true;
            }
        }
    }
    return visited;
}

int Graph::bfs(string origin,const unordered_set<string>& airlines,const unordered_set<string>& countries,const airportHTable& airports) {
    for (auto itr = nodes.begin(); itr != nodes.end(); itr++) {
        itr->second.distance = 0;
        itr->second.visited = false;
    }
    int result = 0;
    queue<string> q;
    q.push(origin);
    nodes[origin].distance = 0;
    nodes[origin].visited = true;
    while (!q.empty()) {
        string curr = q.front();
        q.pop();
        for (auto e: nodes[curr].adj) {
            string neighbour = e.destCode;

            if (!nodes[neighbour].visited and airlines.find(e.airlineCode) != airlines.end() and
                countries.find(airports.find(e.destCode)->getCountry()) != countries.end()) {
                nodes[neighbour].distance = nodes[curr].distance + 1;
                if (nodes[neighbour].distance > result) result = nodes[neighbour].distance;
                q.push(neighbour);
                nodes[neighbour].visited = true;
            }
        }
    }
    return result;
}

vector<Graph::Edge> Graph::getEdges(string node) {
    vector<Graph::Edge> airports;

    for(auto e: nodes[node].adj){
        airports.push_back(e);
    }
    return airports;

}