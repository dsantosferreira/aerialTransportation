#ifndef AERIALTRANSPORTATION_ORGANIZER_H
#define AERIALTRANSPORTATION_ORGANIZER_H
#include <iostream>
#include <string>
#include <vector>
#include <functional>
#include "../model/Graph.h"

using namespace std;

class Organizer
{
protected:
    /** @var buttons with the different options to organize the data*/
    vector<string> buttons;

public:
    Organizer();
    void draw() const;
};

#endif // AERIALTRANSPORTATION_ORGANIZER_H
