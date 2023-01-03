#include "Airline.h"

Airline::Airline(string code, string name, string callSign, string country) {
    this->code = code;
    this->name = name;
    this->callSign = callSign;
    this->country = country;
}

string Airline::getCode() const {
    return code;
}

string Airline::getName() const {
    return name;
}
void Airline:: print() const{
        cout<<this->getCode()<<"       | "<<this->getName();
        for(int i=0; i<66-this->getName().length();i++)cout<<" ";
}