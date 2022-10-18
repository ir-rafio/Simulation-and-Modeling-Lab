#include "Simulator.hpp"

Simulator::Simulator(double arrivalMean, double serviceMean): eventList(Heap<Event*>(Event::earlier))
{
    int i;
    for(i=0; i<3; i++) server[i]=nullptr;
    reset(arrivalMean, serviceMean);
}

Simulator::~Simulator()
{
    int i;
    while(!eventList.isEmpty()) delete (eventList.pop());
    for(i=0; i<3; i++) if(server[i]) delete server[i];
}

void Simulator::reset(double arrivalMean, double serviceMean)
{
    int i;
    while(!eventList.isEmpty()) delete eventList.pop();
    for(i=0; i<3; i++) if(server[i]) delete server[i];
    
    for(i=0; i<3; i++) server[i]=new Server(this, arrivalMean, serviceMean);
    clock=0;

    arrivalCount=0;
    qMax=0;
    qArea=0;
    maxDelay=0;
    totalDelay=0;

    schedule(new Arrival(this), RandomNumber::exponential(arrivalMean));
}

void Simulator::run()
{
    Event *event;

    while(!eventList.isEmpty())
    {
        event=eventList.pop();
        clock=event->time;
        event->handle();
        if(event) delete event;
    }
}

void Simulator::schedule(Event *event, double interval)
{
    event->setTime(clock+interval);
    eventList.push(event);
}

Server* Simulator::getServer()
{
    int i;

    for(i=0; i<3; i++) if(server[i]->free()) return server[i];

    return server[0];
}

double Simulator::now() { return clock; }

double Simulator::avgDelay()
{
    return totalDelay/arrivalCount;
}

double Simulator::getMaxDelay()
{
    return maxDelay;
}

int Simulator::maxQLength()
{
    return qMax;
}

double Simulator::avgQLength()
{
    return qArea/clock;
}

double Simulator::utilizationRatio()
{
    return (server[0]->getUtilTime()+server[1]->getUtilTime()+server[2]->getUtilTime())/(clock*3);
}