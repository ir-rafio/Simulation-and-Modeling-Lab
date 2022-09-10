#ifndef SERVER_HPP
#define SERVER_HPP

#include <bits/stdc++.h>
#include "Queue.hpp"
#include "Train.hpp"
#include "RandomNumber.hpp"

class Simulator;

class Server
{
protected:
    /*Simulator*/
    Simulator *simulator;

    /*Input Variables*/
    double arrivalMean, serviceMin, serviceMax, crewMin, crewMax, crewDelayMin, crewDelayMax;
    
    /*State Variables*/
    bool status;
    Queue<Train> queue, served;

    /*Statistical Variables*/
    int arrivalCount, qMax;
    double qArea;
    double lastEventTime, lastArrivalTime, lastUtilTime, maxDelay, totalDelay, totalUtilization, totalHogout;

    /*Utility Functions*/
    void serve(Train);

public:
    /*Constructor and Destructor*/
    Server(Simulator*, double, double, double, double, double, double, double);

    /*Getter Functions*/
    int getArrivalCount();
    int getQMax();
    double getQArea();
    double getMaxDelay();
    double getTotalDelay();
    double getUtilTime();
    double getHogoutTime();
    Queue<Train>* unloadedTrains();
    
    /*Event Handlers*/
    void arrivalHandler();
    void departureHandler();
};

#endif
