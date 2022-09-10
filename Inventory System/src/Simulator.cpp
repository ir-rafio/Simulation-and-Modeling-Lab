#include "Simulator.hpp"

Simulator::Simulator(int threshold, int cap): eventList(Heap<Event*>(Event::earlier))
{
    inv=nullptr;
    reset(threshold, cap);
}

Simulator::~Simulator()
{
    while(!eventList.isEmpty()) delete (eventList.pop());
    if(inv) delete inv;
}

void Simulator::terminate()
{
    while(!eventList.isEmpty()) delete (eventList.pop());
}

void Simulator::reset(int threshold, int cap)
{
    while(!eventList.isEmpty()) delete eventList.pop();
    if(inv) delete inv;
    
    inv=new Inventory(this, threshold, cap);
    clock=0;

    schedule(new Evaluation(this), 0);
    schedule(new Termination(this), 120);
    schedule(new Demand(this), RandomNumber::exponential(0.1));
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

Inventory* Simulator::getInventory() { return inv; }
double Simulator::now() { return clock; }

double Simulator::avgOrderingCost() {return inv->getOrderingCost()/120; }
double Simulator::avgHoldingCost() {return inv->getHoldingArea()*inv->getPerHoldingCost()/120; }
double Simulator::avgShortageCost() {return inv->getShortageArea()*inv->getPerBacklogCost()/120; }
double Simulator::avgCost() {return avgOrderingCost()+avgHoldingCost()+avgShortageCost(); }
