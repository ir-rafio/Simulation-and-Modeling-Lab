#include "Simulator.hpp"

Simulator::Simulator(double arrivalMean, double serviceMin, double serviceMax,
    double crewMin, double crewMax, double crewDelayMin, double crewDelayMax): eventList(Heap<Event*>(Event::earlier))
{
    server=nullptr;
    reset(arrivalMean, serviceMin, serviceMax, crewMin, crewMax, crewDelayMin, crewDelayMax);
}

Simulator::~Simulator()
{
    while(!eventList.isEmpty()) delete (eventList.pop());
    if(server) delete server;
}

void Simulator::reset(double arrivalMean, double serviceMin, double serviceMax,
    double crewMin, double crewMax, double crewDelayMin, double crewDelayMax)
{
    while(!eventList.isEmpty()) delete eventList.pop();
    if(server) delete server;
    
    server=new Server(this, arrivalMean, serviceMin, serviceMax, crewMin, crewMax, crewDelayMin, crewDelayMax);
    clock=0;

    schedule(new Arrival(this), RandomNumber::exponential(arrivalMean));
    schedule(new Termination(this), 720);
}

void Simulator::terminate()
{
    while(!eventList.isEmpty()) delete (eventList.pop());
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
double Simulator::hogoutRatio() { return server->getHogoutTime()/clock; }
