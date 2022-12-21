#include "CNG.hpp"
#include "Simulator.hpp"
#include "Terminal.hpp"
#include "Passenger.hpp"
#include "Event.hpp"
#include "RandomNumber.hpp"

CNG::CNG(Terminal* t, double duration, int threshold_):
terminal(t), simulator(t->getSimulator()), id(t->getSimulator()->countCNG()),
tripDurationMean(duration), threshold(threshold_)
{
    terminal->CNGarrivalHandler(this);

    meanCost=6;
    totalCost=0;
    perPassengerEarning=10;
    passengerCount=0;
    tripCount=0;
}

CNG::~CNG()
{
    int i, n=seat.size();
    for(i=0; i<n; i++) delete seat[i];
}
    
bool CNG::free() { return seat.size()<5; }

void CNG::addPassenger(Passenger* p)
{
    p->setBoardingTime(simulator->now());
    p->setCNGid(id);
    seat.push_back(p);

    if(seat.size()==threshold) simulator->schedule(new TripStart(this), 0.1);
}

void CNG::startTrip()
{
    int i=0, n=seat.size();    
    for(i=0; i<n; i++) seat[i]->setTripStartTime(simulator->now());

    terminal->CNGdepartureHandler(this);
    terminal=terminal->getDestination();
    simulator->schedule(new Departure(this), RandomNumber::exponential(tripDurationMean));
}

void CNG::departureHandler()
{
    int i, n=seat.size();
    passengerCount+=n;
    tripCount++;
    totalCost+=RandomNumber::normal(meanCost, 0.25);
    
    for(i=0; i<n; i++)
    {
        seat[i]->setDepartureTime(simulator->now());
        seat[i]->write();

        delete seat[i];
    }

    seat.clear();

    terminal->CNGarrivalHandler(this);
}

int CNG::profit() { return passengerCount*perPassengerEarning-totalCost; }
double CNG::fuelEfficiency() { return 1.0/5*passengerCount/tripCount; }

void CNG::write()
{
    simulator->CNGstream << id << ',' << threshold << ',' << passengerCount << ',' << tripCount << ',';
    simulator->CNGstream << profit() << ',' << fuelEfficiency() << '\n';
}