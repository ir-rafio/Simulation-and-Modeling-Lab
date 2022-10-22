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
    friend class Server;

    /*Basic Members*/
    double clock;
    Heap<Event*> eventList;

public:
    /*Constructor and Destructor*/
    Simulator(double, double);
    ~Simulator();

    /*Running Functions*/
    void run();
    void schedule(Event*, double);
    void reset(double, double);
    void moveBetweenLines();
    
    /*Getter Functions*/
    double now();
    Server* getServer();

    /*Output Functions*/
    double maxDelay();
    double avgDelay();
    int maxQLength();
    double avgQLength();
    double utilizationRatio();
};

#endif
