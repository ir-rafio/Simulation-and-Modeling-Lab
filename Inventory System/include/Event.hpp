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

class Evaluation: public Event
{
public:
    Evaluation(Simulator*);
    void handle();
};

class Supply: public Event
{
protected:
    /*Extra Members*/
    int amount;
    
public:
    Supply(Simulator*, int);
    void handle();
};

class Demand: public Event
{
public:
    Demand(Simulator*);
    void handle();
};

class Termination: public Event
{
public:
    Termination(Simulator*);
    void handle();
};

#endif
