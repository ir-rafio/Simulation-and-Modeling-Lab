#ifndef INVENTORY_HPP
#define INVENTORY_HPP

// #include <bits/stdc++.h>
#include "RandomNumber.hpp"

class Simulator;

class Inventory
{
protected:
    /*Simulator*/
    Simulator *simulator;

    /*Input Variables*/
    int orderThreshold, capacity;
    int perSetupCost, perItemCost, perHoldingCost, perBacklogCost;
    double demandMean, minLag, maxLag;
    
    /*State Variables*/
    int level;

    /*Statistical Variables*/
    int orderingCost;
    double holdingArea, shortageArea;
    double lastEventTime;

    /*Utility Functions*/
    void order();
    void setLevel(int);

public:
    /*Constructor and Destructor*/
    Inventory(Simulator*, int, int);

    /*Getter Functions*/
    double getOrderingCost();
    double getPerHoldingCost();
    double getHoldingArea();
    double getPerBacklogCost();
    double getShortageArea();

    /*Event Handlers*/
    void evaluationHandler();
    void supplyHandler(int);
    void demandHandler();
    void terminationHandler();
};

#endif
