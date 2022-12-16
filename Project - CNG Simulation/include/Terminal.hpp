#ifndef TERMINAL_HPP
#define TERMINAL_HPP

#include <bits/stdc++.h>
#include "CNG.hpp"
class Simulator;

class Terminal
{
protected:
    std::string name;
    Simulator *simulator;
    Terminal *destination;
    double arrivalMean;
    
    std::queue<Passenger*> queue;
    std::vector<CNG*> cng;

public:
    Terminal(Simulator*, std::string, double);

    void setDestination(Terminal*);

    Simulator* getSimulator();
    Terminal* getDestination();
    std::string getName();
    double getArrivalMean();

    void passengerArrivalHandler();
    void CNGarrivalHandler(CNG*);
    void CNGdepartureHandler(CNG*);

    int findCNGpos(CNG* c);
    int getFreeCNGpos();
    bool boardCNG();
};

#endif
