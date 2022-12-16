#ifndef SIMULATOR_HPP
#define SIMULATOR_HPP

#include "Heap.hpp"
#include "Event.hpp"
#include "RandomNumber.hpp"
#include "Terminal.hpp"

class Simulator
{
protected:
    int id;
    double clock;
    Heap<Event*> eventList;

    std::vector<CNG*> cng;
    Terminal* terminal[2];
    int passengerCount;

public:
    std::ofstream CNGstream, passengerStream;

    Simulator(int);
    ~Simulator();

    void reset(int);
    void run();
    void schedule(Event*, double);
    void terminate();
    
    double now();
    int countPassenger();
    int countCNG();
};

#endif
