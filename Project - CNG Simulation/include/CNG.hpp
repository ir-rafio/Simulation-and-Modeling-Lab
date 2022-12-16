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

    int perTripCost, perPassengerEarning, threshold;
    double tripDurationMean;

    int passengerCount, tripCount;

public:
    CNG(Simulator*, Terminal*, double, int);
    
    bool free();
    void addPassenger(Passenger*);
    void startTrip();
    void departureHandler();

    int profit();
    double fuelEfficiency();
    int getID();

    void write();
};

#endif
