#ifndef SIMULATOR_HPP
#define SIMULATOR_HPP

#include "Inventory.hpp"
#include "Heap.hpp"
#include "Event.hpp"
#include "RandomNumber.hpp"

class Simulator
{
protected:
    /*System*/
    Inventory* inv;

    /*Basic Members*/
    double clock;
    Heap<Event*> eventList;

public:
    /*Constructor and Destructor*/
    Simulator(int, int);
    ~Simulator();

    /*Running Functions*/
    void run();
    void schedule(Event*, double);
    void reset(int, int);
    void terminate();
    
    /*Getter Functions*/
    double now();
    Inventory* getInventory();

    /*Output Functions*/
    double avgOrderingCost();
    double avgHoldingCost();
    double avgShortageCost();
    double avgCost();
};

#endif
