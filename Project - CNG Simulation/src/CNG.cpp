#include "CNG.hpp"
#include "Simulator.hpp"
#include "Terminal.hpp"
#include "Passenger.hpp"
#include "Event.hpp"
#include "RandomNumber.hpp"

CNG::CNG(Simulator* s, Terminal* t, double duration, int threshold_):
id(s->countCNG()), simulator(s), terminal(t),
tripDurationMean(duration), threshold(threshold_)
{
    terminal->CNGarrivalHandler(this);

    perTripCost=8;
    perPassengerEarning=10;
    passengerCount=0;
    tripCount=0;
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

    // std::cout << "\tID: " << id << '\n';

    terminal->CNGdepartureHandler(this);
    terminal=terminal->getDestination();
    simulator->schedule(new Departure(this), RandomNumber::exponential(tripDurationMean));
}

void CNG::departureHandler()
{
    int i=0, n=seat.size();
    passengerCount+=n;
    tripCount++;
    
    // std::cout << "STAGE1\n";
    for(i=0; i<n; i++)
    {
        seat[i]->setDepartureTime(simulator->now());
        // std::cout << "STAGE1.5\n";
        seat[i]->write();

        // std::cout << "STAGE1.6\n";
        delete seat[i];
    }

    // std::cout << "STAGE2\n";
    seat.clear();

    // std::cout << "STAGE3\n";
    terminal->CNGarrivalHandler(this);
    // std::cout << "STAGE4\n";
}

int CNG::profit() { return passengerCount*perPassengerEarning-tripCount*perTripCost; }
double CNG::fuelEfficiency() { return 1.0/5*passengerCount/tripCount; }
int CNG::getID() { return id; }

void CNG::write()
{
    simulator->CNGstream << id << ',' << threshold << ',' << passengerCount << ',' << tripCount << ',';
    simulator->CNGstream << profit() << ',' << fuelEfficiency() << '\n';
}