#include "Terminal.hpp"
#include "Simulator.hpp"
#include "CNG.hpp"
#include "Passenger.hpp"
#include "Event.hpp"
#include "RandomNumber.hpp"

Terminal::Terminal(Simulator* s, std::string name_, double mean): simulator(s), name(name_), arrivalMean(mean)
{}

void Terminal::setDestination(Terminal* t)
{
    destination=t;
}

Simulator* Terminal::getSimulator() { return simulator; }
Terminal* Terminal::getDestination() { return destination; }
double Terminal::getArrivalMean() { return arrivalMean; }
std::string Terminal::getName() { return name; }

int Terminal::findCNGpos(CNG* c)
{
    int i, n=cng.size();
    for(i=0; i<n; i++) if(cng[i]==c) return i;

    return -1;
}

int Terminal::getFreeCNGpos()
{
    int i, n=cng.size();
    std::vector<int> freeCNG;
    for(i=0; i<n; i++) if(cng[i]->free()) freeCNG.push_back(i);

    n=freeCNG.size();
    if(n<2) return freeCNG.size()-1;
    return freeCNG[RandomNumber::uniformInt(0, n-1)];
}

bool Terminal::boardCNG()
{
    if(queue.empty()) return false;

    int i=getFreeCNGpos();
    if(i<0) return false;

    Passenger *p=queue.front();
    queue.pop();
    cng[i]->addPassenger(p);
    return true;
}

void Terminal::passengerArrivalHandler()
{
    double now=simulator->now();
    if(now>720) return;

    Passenger *p=new Passenger(simulator, this, destination, now);
    queue.push(p);

    boardCNG();
    simulator->schedule(new Arrival(this), RandomNumber::exponential(arrivalMean));
}

void Terminal::CNGarrivalHandler(CNG* c)
{
    // std::cout << "\t\tID: " << c->getID() << '\n';
    // std::cout << "\t\t" << name << '\n';
    // std::cout << "\t\tSize: " << cng.size() << '\n';
    cng.push_back(c);
    
    while(boardCNG());
}

void Terminal::CNGdepartureHandler(CNG* c)
{
    int i=findCNGpos(c), n=cng.size();
    if(i<0) return;
    
    std::swap(cng[i], cng[n-1]);
    cng.pop_back();
}