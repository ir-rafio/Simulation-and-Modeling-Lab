#ifndef SERVER_HPP
#define SERVER_HPP

#include <bits/stdc++.h>
#include "Job.hpp"
#include "RandomNumber.hpp"

class Simulator;

class Server
{
protected:
    /*Simulator*/
    Simulator *simulator;
    friend class Simulator;

    /*Input Variables*/
    double arrivalMean, serviceMean;
    
    /*State Variables*/
    bool status;
    std::deque<Job> deque;

    /*Statistical Variables*/
    int arrivalCount, qMax;
    double qArea;
    double lastEventTime, lastArrivalTime, lastUtilTime, maxDelay, totalDelay, totalUtilization;

    /*Utility Functions*/
    void serve(Job);

public:
    /*Constructor and Destructor*/
    Server(Simulator*, double, double);

    /*Getter Functions*/
    int getArrivalCount();
    int getQMax();
    int getQSize();
    double getQArea();
    double getMaxDelay();
    double getTotalDelay();
    double getUtilTime();
    
    /*Event Handlers*/
    void arrivalHandler();
    void departureHandler();
};

#endif
