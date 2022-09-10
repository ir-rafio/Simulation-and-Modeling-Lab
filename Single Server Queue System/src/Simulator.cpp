#include "Simulator.hpp"

Simulator::Simulator(double arrivalMean, double serviceMean): eventList(Heap<Event*>(Event::earlier))
{
    server=nullptr;
    reset(arrivalMean, serviceMean);
}

Simulator::~Simulator()
{
    while(!eventList.isEmpty()) delete (eventList.pop());
    if(server) delete server;
}

void Simulator::reset(double arrivalMean, double serviceMean)
{
    while(!eventList.isEmpty()) delete eventList.pop();
    if(server) delete server;
    
    server=new Server(this, arrivalMean, serviceMean);
    clock=0;

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

Server* Simulator::getServer() { return server; }
double Simulator::now() { return clock; }

double Simulator::maxDelay() {return server->getMaxDelay(); }
double Simulator::avgDelay() {return server->getTotalDelay()/server->getArrivalCount(); }
int Simulator::maxQLength() { return server->getQMax(); }
double Simulator::avgQLength() { return server->getQArea()/clock; }
double Simulator::utilizationRatio() { return server->getUtilTime()/clock; }