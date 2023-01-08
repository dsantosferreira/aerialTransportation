#include "Graph.h"
#include "../Database.h"

/**
 * Graph default constructor
 */
Graph::Graph() {}

/**
 * @brief Builds an edge on the graph
 * @param src origin airport
 * @param dest destination airport
 * @param airline airlines used on the flight
 * @param weight distance travelled by the flight
 */
void Graph::addEdge(string src, string dest, string airline, float weight) {
    if (nodes.find(src) == nodes.end() || nodes.find(dest) == nodes.end()) return;
    nodes[src].adj.push_back({dest, weight, airline});
    if (!hasDir) nodes[dest].adj.push_back({src, weight, airline});
}

/**
 * Graph constructor (it only builds the nodes)
 * @param num number of nodes on the graph
 * @param airports hash table of airports
 * @param dir whether the graph is directed or not
 */
Graph::Graph(int num, airportHTable airports, bool dir) : n(num), hasDir(dir) {
    for (Airport airport: airports) {
        nodes.insert({airport.getCode(), Node()});
    }
}

/**
 * @return nodes of the graph
 */
unordered_map<string, Graph::Node> Graph::getNodes() const {
    return this->nodes;
}

/**
 * @brief Runs the articulation points dfs and returns all the articulation points
 * @param airports hash table of airports
 * @param airlines has table of airlines
 * @see Graph::artPointsDfs(string origin, int &idx, stack<string> &beingVisited, const airportHTable &airports, const unordered_set<string> &airlines, vector<Airport> &artPoints)
 * @return vector of all the articulation points
 * Complexity: O(V + E) being V the number of vertices of the graph and E the number of edges of the graph
 */
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

/**
 * Functions that calculates of the articulation points of the graph.
 * We considered as articulation points the nodes that, when removed from the graph, increase the amount of weakly connected components of the graph, since we ran the algorithm with an undirected graph
 * @brief Depth-First Search to find all the articulation points of the graph
 * @param origin origin airport
 * @param idx order on which the currently visited node is being visited
 * @param beingVisited stack of nodes that are still being visited
 * @param airports hash table of airports
 * @param airlines hash table of airlines
 * @param artPoints vector of articulation points
 * Complexity: O(V + E) being V the number of vertices of the graph and E the number of edges of the graph
 */
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

/**
 * @brief Breadth-First Search to find all the minimal trips from airports from origin to airports from destinations
 * @param origins airports where the trips can start
 * @param destinations airports where the trips can end
 * @param airlines airlines that are permitted
 * @param maxAirlines maximum of different airlines permitted
 * @see Graph::findPaths(trips &allPaths, string currAirportCode, trip aPath, const int maxAirlines, unordered_set<string> usedAirlines)
 * @return vector of all the minimal trips
 * Complexity: O(V + E + O(findPaths)) being V the number of vertices of the graph and E the number of edges of the graph
 */
trips Graph::minFlightsBFS(unordered_set<string> origins, unordered_set<string> destinations, unordered_set<string> airlines, const int maxAirlines) {
    // Reset all nodes
    for (auto itr = nodes.begin(); itr != nodes.end(); itr++) {
        itr->second.distance = INT32_MAX;
        itr->second.parents.clear();
    }

    int minDist; // Distance of the first destination to the origin airport
    trips allPaths;  // Minimal paths from origin to destinations
    queue<string> toVisit; // airports to visit

    for (string origin: origins) {
        toVisit.push(origin);
        nodes[origin].distance = 0;
    }

    while (!toVisit.empty()) {
        string currAirportCode = toVisit.front();
        Node currNode = nodes[currAirportCode];

        // Found the first destination
        if (destinations.find(currAirportCode) != destinations.end() && origins.find(currAirportCode) == origins.end()) {
            minDist = currNode.distance; // Sets the minimal number of flights to get to the destination

            // Continues to see if there are other destinations at the same distance adding relevant airports to the paths
            while (!toVisit.empty() && nodes[toVisit.front()].distance == minDist) {
                if (destinations.find(currAirportCode) != destinations.end())
                    findPaths(allPaths, currAirportCode, trip(), maxAirlines, unordered_set<string>());
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
                    nodes[neighbour].parents.push_back({{currAirportCode, edge.airlineCode}, edge.weight});
                    toVisit.push(neighbour);
                }
                else if (nodes[neighbour].distance == currNode.distance + 1)
                    nodes[neighbour].parents.push_back({{currAirportCode, edge.airlineCode}, edge.weight});
            }
        }
        toVisit.pop();
    }

    return allPaths;
}

/**
 * Recursively finds all the paths from a destination airport to all the origin airports that have minimal paths to it.
 * The paths are found with the information of the parents of each node until an origin airport is reached (an airport that has no parents)
 * @brief Finds all minimal paths between a destination airport and the origin airports
 * @param allPaths vector that stores all the paths
 * @param currAirportCode airport we are currently in
 * @param aPath storage of a path
 * @param maxAirlines maximum number of different airlines used permitted
 * @param usedAirlines airlines used in aPath
 * Complexity O(N) being N the summation of the number of parents of each node
 */
void Graph::findPaths(trips &allPaths, string currAirportCode, trip aPath, const int maxAirlines, unordered_set<string> usedAirlines) {
    if (nodes[currAirportCode].parents.empty()) {
        Node a = nodes[currAirportCode];
        aPath.first.insert(aPath.first.begin(), {currAirportCode, ""});
        allPaths.push_back(aPath);
    }
    else {
        Node a = nodes[currAirportCode];
        for (auto parent: nodes[currAirportCode].parents) {
            unordered_set<string> newUsedAirlines = usedAirlines;
            newUsedAirlines.insert(parent.first.second);

            if (newUsedAirlines.size() > maxAirlines)
                return;

            aPath.first.insert(aPath.first.begin(), {currAirportCode, parent.first.second});
            aPath.second += parent.second;
            findPaths(allPaths, parent.first.first, aPath, maxAirlines, newUsedAirlines);
            aPath.first.erase(aPath.first.begin());
            aPath.second -= parent.second;
        }
    }
}

/**
 * @brief Breadth-First Search to find all the airports reachable from a specific airport with 'maxFlights' flights
 * @param maxFlights maximum number of flights permitted
 * @param original starting point (a specific airport code)
 * @return set with all the airports codes reached
 * Complexity: O(V + E*log(Vc)) being V the number of vertices in the graph, E de number of edges and Vc the number of currently visited airports
 */
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

/**
 * @brief returns all the airports adjacent to the airport provided as input
 * @param node node we want to get the edges of
 * @return vector with the edges of the graph
 * Complexity: O(N) being N the size of the adj list
 */
vector<Graph::Edge> Graph::getEdges(string node) {
    vector<Graph::Edge> airports;

    for (auto e: nodes[node].adj) {
        airports.push_back(e);
    }
    return airports;
}

/**
 * @brief Breadth-First Search to calculate the diameter(max distance reached) starting at the airport provided as input
 * @param origin airport code to use as start point
 * @param airline airline that should be used
 * @param country country where the airport has to be located
 * @param airports all airports
 * @return diameter
 * Complexity: O(V + E) being V the number of vertices in the graph and E de number of edges
 */
int Graph::diameterBfs(string origin, string airline, string country, const airportHTable& airports) {
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
            if (!nodes[neighbour].visited and (e.airlineCode == airline or airline == "") and (airports.find(neighbour)->getCountry() == country or country == "")) {

                nodes[neighbour].distance = nodes[curr].distance + 1;
                if (nodes[neighbour].distance > result) result = nodes[neighbour].distance;
                q.push(neighbour);
                nodes[neighbour].visited = true;
            }
        }
    }
    return result;
}
