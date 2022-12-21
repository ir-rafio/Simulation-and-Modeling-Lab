#ifndef EVENT_HPP
#define EVENT_HPP

#include "CNG.hpp"
#include "Terminal.hpp"
class Simulator;

class Event
{
protected:
    double time;
    friend class Simulator;

    void setTime(double _time);
    
    virtual void handle()=0;

public:
    Event();

    static bool earlier(Event* e1, Event* e2);
};

class Arrival: public Event
{
protected:
    Terminal *terminal;
public:
    Arrival(Terminal*);
    void handle();
};

class TripStart: public Event
{
protected:
    CNG *cng;
public:
    TripStart(CNG*);
    void handle();
};

class Departure: public Event
{
protected:
    CNG *cng;
public:
    Departure(CNG*);
    void handle();
};

#endif
