#include "Inventory.hpp"
#include "Simulator.hpp"

Inventory::Inventory(Simulator* s, int threshold, int cap): orderThreshold(threshold), capacity(cap), simulator(s)
{
    perSetupCost=32;
    perItemCost=3;
    perHoldingCost=1;
    perBacklogCost=5;
    demandMean=0.1;
    minLag=0.5;
    maxLag=1;

    level=cap;
    
    orderingCost=0;
    holdingArea=0;
    shortageArea=0;
    lastEventTime=0;
}

double Inventory::getOrderingCost() { return orderingCost; }
double Inventory::getPerHoldingCost() { return perHoldingCost; }
double Inventory::getHoldingArea() { return holdingArea; }
double Inventory::getPerBacklogCost() { return perBacklogCost; }
double Inventory::getShortageArea() { return shortageArea; }

void Inventory::demandHandler()
{
    int demandSize;

    switch(rand()%6)
    {
        case 0:
        demandSize=1;
        break;

        case 1:
        case 2:
        demandSize=2;
        break;

        case 3:
        case 4:
        demandSize=3;
        break;

        case 5:
        demandSize=4;
        break;
    }

    setLevel(level-demandSize);

    simulator->schedule(new Demand(simulator), RandomNumber::exponential(0.1));
}

void Inventory::evaluationHandler()
{
    if(level<orderThreshold) order();
    
    simulator->schedule(new Evaluation(simulator), 1);
}

void Inventory::supplyHandler(int amount)
{
    setLevel(level+amount);
}

void Inventory::terminationHandler()
{
    setLevel(0);
    simulator->terminate();
}

void Inventory::order()
{
    int amount=capacity-level;
    int cost=perSetupCost+(perItemCost*amount);
    
    orderingCost+=cost;

    simulator->schedule(new Supply(simulator, amount), RandomNumber::uniform(0.5, 1));
}

void Inventory::setLevel(int l)
{
    double now=simulator->now();
    double duration=now-lastEventTime;
    lastEventTime=now;

    if(level<0) shortageArea-=level*duration;
    else holdingArea+=level*duration;

    level=l;
}