#ifndef CNG_HPP
#define CNG_HPP

#include <bits/stdc++.h>
#include "Passenger.hpp"
class Simulator;
class Terminal;

class CNG
{
protected:
    int id;
    Simulator *simulator;
    Terminal *terminal;
    std::vector<Passenger*> seat;

    int meanCost, perPassengerEarning, threshold;
    double tripDurationMean;

    int passengerCount, tripCount;
    double totalCost;

public:
    CNG(Terminal*, double, int);
    ~CNG();
    
    bool free();
    void addPassenger(Passenger*);
    void startTrip();
    void departureHandler();

    int profit();
    double fuelEfficiency();

    void write();
};

#endif
