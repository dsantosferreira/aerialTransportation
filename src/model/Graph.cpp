#include "Graph.h"
#include <iostream>

Graph::Graph() {}

Graph::Graph(int num, bool dir) : n(num), hasDir(dir)
{
}

void Graph::addEdge(string src, string dest, string airline, int weight)
{
    if (nodes.find(src) == nodes.end() || nodes.find(dest) == nodes.end())
        return;
    nodes[src].adj.push_back({dest, weight, airline});
    if (!hasDir)
        nodes[dest].adj.push_back({src, weight, airline});
}

Graph::Graph(int num, airportHTable airports, bool dir) : n(num), hasDir(dir)
{
    for (Airport airport : airports)
    {
        nodes.insert({airport.getCode(), Node()});
    }
}

unordered_map<string, Graph::Node> Graph::getNodes() const
{
    return this->nodes;
}

vector<list<pair<string, string>>> Graph::minAirportFlightsBFS(string origin, string destination)
{

    // Reset all nodes
    for (auto itr = nodes.begin(); itr != nodes.end(); itr++)
    {
        itr->second.distance = INT32_MAX;
        itr->second.parents.clear();
    }

    vector<list<pair<string, string>>> allPaths;
    queue<string> toVisit;
    toVisit.push(origin);
    nodes[origin].distance = 0;

    while (!toVisit.empty())
    {
        string currAirportCode = toVisit.front();
        Node currNode = nodes[currAirportCode];

        if (currAirportCode == destination)
        {
            findPaths(allPaths, currAirportCode, list<pair<string, string>>());
            break;
        }

        for (Edge edge : currNode.adj)
        {
            string neighbour = edge.destCode;

            if (nodes[neighbour].distance > currNode.distance + 1)
            {
                nodes[neighbour].distance = currNode.distance + 1;
                nodes[neighbour].parents.push_back({currAirportCode, edge.airlineCode});
                toVisit.push(neighbour);
            }
            else if (nodes[neighbour].distance == currNode.distance + 1)
                nodes[neighbour].parents.push_back({currAirportCode, edge.airlineCode});
        }
        toVisit.pop();
    }

    return allPaths;
}

int Graph::minCityFlightsBFS(string origin, string cityDest, airportHTable &airports)
{
    // Reset all nodes
    for (auto itr = nodes.begin(); itr != nodes.end(); itr++)
    {
        itr->second.visited = false;
        itr->second.distance = 0;
    }

    queue<string> toVisit;
    toVisit.push(origin);
    nodes[origin].visited = true;

    while (!toVisit.empty())
    {
        string currAirportCode = toVisit.front();
        Node currNode = nodes[currAirportCode];

        if (airports.find(Airport(currAirportCode, "", "", "", 0, 0))->getCity() == cityDest)
            return currNode.distance;

        for (Edge edge : currNode.adj)
        {
            if (!nodes[edge.destCode].visited)
            {
                toVisit.push(edge.destCode);
                nodes[edge.destCode].visited = true;
                nodes[edge.destCode].distance = nodes[currAirportCode].distance + 1;
            }
        }
        toVisit.pop();
    }

    return -1;
}

int Graph::minDistanceFlightsBFS(string origin, Coordinate center, float radius, airportHTable &airports)
{
    // Reset all nodes
    for (auto itr = nodes.begin(); itr != nodes.end(); itr++)
    {
        itr->second.visited = false;
        itr->second.distance = 0;
    }

    queue<string> toVisit;
    toVisit.push(origin);
    nodes[origin].visited = true;

    while (!toVisit.empty())
    {
        string currAirportCode = toVisit.front();
        Node currNode = nodes[currAirportCode];
        Coordinate currPosition = airports.find(Airport(currAirportCode, "", "", "", 0, 0))->getCoordinate();

        if (currPosition.distance(center) <= radius)
            return currNode.distance;

        for (Edge edge : currNode.adj)
        {
            if (!nodes[edge.destCode].visited)
            {
                toVisit.push(edge.destCode);
                nodes[edge.destCode].visited = true;
                nodes[edge.destCode].distance = nodes[currAirportCode].distance + 1;
            }
        }
        toVisit.pop();
    }

    return -1;
}

void Graph::findPaths(vector<list<pair<string, string>>> &allPaths, string currAirportCode, list<pair<string, string>> aPath)
{
    if (nodes[currAirportCode].parents.empty())
    {
        Node a = nodes[currAirportCode];
        aPath.insert(aPath.begin(), {currAirportCode, ""});
        allPaths.push_back(aPath);
    }
    else
    {
        Node a = nodes[currAirportCode];
        for (pair<string, string> parent : nodes[currAirportCode].parents)
        {
            aPath.insert(aPath.begin(), {currAirportCode, parent.second});
            findPaths(allPaths, parent.first, aPath);
            aPath.erase(aPath.begin());
        }
    }
}