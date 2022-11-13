#ifndef SERVER_HPP
#define SERVER_HPP

#include <bits/stdc++.h>
#include "Queue.hpp"
#include "Job.hpp"
#include "RandomNumber.hpp"

class Simulator;

class Server
{
protected:
    /*Simulator*/
    Simulator *simulator;

    /*Input Variables*/
    double arrivalMean, serviceMean;
    
    /*State Variables*/
    bool status;
    Queue<Job> queue;

    /*Statistical Variables*/
    int arrivalCount;
    double lastArrivalTime, lastUtilTime, maxDelay, totalDelay, totalUtilization;

    /*Utility Functions*/
    void serve(Job);

public:
    /*Constructor and Destructor*/
    Server(Simulator*, double, double);

    /*Getter Functions*/
    int getArrivalCount();
    int getQSize();
    // int getQMax();
    // double getQArea();
    double getMaxDelay();
    double getTotalDelay();
    double getUtilTime();
    
    /*Event Handlers*/
    void arrivalHandler();
    void departureHandler();
};

#endif
