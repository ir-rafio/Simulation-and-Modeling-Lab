#ifndef SIMULATOR_HPP
#define SIMULATOR_HPP

#include "Heap.hpp"
#include "Event.hpp"
#include "Server.hpp"
#include "RandomNumber.hpp"

class Simulator
{
protected:
    /*System*/
    Server* server;

    /*Basic Members*/
    double clock;
    Heap<Event*> eventList;

public:
    /*Constructor and Destructor*/
    Simulator(double, double, double, double, double, double, double);
    ~Simulator();

    /*Running Functions*/
    void run();
    void schedule(Event*, double);
    void reset(double, double, double, double, double, double, double);
    void terminate();
    
    /*Getter Functions*/
    double now();
    Server* getServer();

    /*Output Functions*/
    double maxDelay();
    double avgDelay();
    int maxQLength();
    double avgQLength();
    double utilizationRatio();
    double hogoutRatio();
};

#endif
