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
    Server* server[3];
    Queue<Job> queue;
    friend class Server;

    /*Basic Members*/
    double clock;
    Heap<Event*> eventList;

    /*Statistical Variables*/
    int arrivalCount, qMax;
    double qArea;
    double maxDelay, totalDelay;

public:
    /*Constructor and Destructor*/
    Simulator(double, double);
    ~Simulator();

    /*Running Functions*/
    void run();
    void schedule(Event*, double);
    void reset(double, double);
    
    /*Getter Functions*/
    double now();
    Server* getServer();

    /*Output Functions*/
    double avgDelay();
    double getMaxDelay();
    int maxQLength();
    double avgQLength();
    double utilizationRatio();
};

#endif
