#ifndef AERIALTRANSPORTATION_DIRECTFLIGHTSORGANIZER_H
#define AERIALTRANSPORTATION_DIRECTFLIGHTSORGANIZER_H

#include "Organizer.h"
#include "../model/Graph.h"
#include "../Database.h"
#include <functional>

class DirectFlightsOrganizer : public Organizer
{
private:
    /** @var Vector of functions to be used to sort the direct flights*/
    vector<function<bool(Graph::Edge e1, Graph::Edge e2)>> functions;

public:
    DirectFlightsOrganizer(Database database);
    void organize(vector<Graph::Edge> &edges, Database database) const;
};

#endif // AERIALTRANSPORTATION_DIRECTFLIGHTSORGANIZER_H
