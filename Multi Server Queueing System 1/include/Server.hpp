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
    Queue<Job>* queue;
    Queue<Job> served;

    /*Statistical Variables*/
    double lastEventTime, lastArrivalTime, lastUtilTime, totalUtilization;

    /*Utility Functions*/
    void serve(Job);

public:
    /*Constructor and Destructor*/
    Server(Simulator*, double, double);

    /*Getter Functions*/
    Queue<Job>* jobsDone();
    double getUtilTime();
    bool free();
    
    /*Event Handlers*/
    void arrivalHandler();
    void departureHandler();
};

#endif