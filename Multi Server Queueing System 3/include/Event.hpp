#ifndef EVENT_HPP
#define EVENT_HPP

class Simulator;
class Server;

class Event
{
protected:
    /*Basic Members*/
    double time;
    friend class Simulator;
    friend class Server;

    /*Setter Functions*/
    void setTime(double _time);
    
    /*Abstract Event Handler*/
    virtual void handle()=0;

public:
    /*Constructor and Destructor*/
    Event();

    /*Comparator*/
    static bool earlier(Event* e1, Event* e2);
};

class Arrival: public Event
{
protected:
    Simulator *simulator;
public:
    Arrival(Simulator*);
    void handle();
};

class Departure: public Event
{
protected:
    Server *server;
public:
    Departure(Server*);
    void handle();
};

#endif
