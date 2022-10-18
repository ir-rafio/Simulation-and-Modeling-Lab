#ifndef EVENT_HPP
#define EVENT_HPP

class Simulator;

class Event
{
protected:
    /*Basic Members*/
    double time;
    Simulator *simulator;
    friend class Simulator;

    /*Setter Functions*/
    void setTime(double _time);
    
    /*Abstract Event Handler*/
    virtual void handle()=0;

public:
    /*Constructor and Destructor*/
    Event(Simulator*);

    /*Comparator*/
    static bool earlier(Event* e1, Event* e2);
};

class Arrival: public Event
{
public:
    Arrival(Simulator*);
    void handle();
};

class Departure: public Event
{
public:
    Departure(Simulator*);
    void handle();
};

#endif
