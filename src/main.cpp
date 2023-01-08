#include <iostream>
#include "Program.h"

using namespace std;

int main() {




    Program p = Program();
    p.run();

    /* Testing graph print
    Graph graph = p.database.getFlightsGraph();
    vector<list<pair<string, string>>> trips = graph.minAirportFlightsBFS("OPO", "PEK");

    for (auto trip: trips) {
        cout << "A flight:" << endl;
        for (auto airport = trip.begin(); airport != --trip.end(); airport++) {
            cout << '\t' << airport->first << " --- " + (++airport)->second + " ---> " << airport->first << endl;
            airport--;
        }
        cout << endl;
    }*/

    return 0;
}
