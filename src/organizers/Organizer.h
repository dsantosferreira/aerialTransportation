//
// Created by franciscocardoso on 03-01-2023.
//

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
    vector<string> buttons;

public:
    Organizer();
    void draw() const;
};

#endif // AERIALTRANSPORTATION_ORGANIZER_H
