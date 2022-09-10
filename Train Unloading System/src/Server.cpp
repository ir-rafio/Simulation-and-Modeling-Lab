#include "Server.hpp"
#include "Simulator.hpp"

Server::Server(Simulator* s, double aMean, double sMin, double sMax,
    double cMin, double cMax, double cdMin, double cdMax)
: simulator(s), arrivalMean(aMean), serviceMin(sMin), serviceMax(sMax),
crewMin(cMin), crewMax(cMax), crewDelayMin(cdMin), crewDelayMax(cdMax)
{
    status=0;

    arrivalCount=0;
    qMax=0;
    qArea=0;
    maxDelay=0;
    totalDelay=0;
    totalUtilization=0;
    totalHogout=0;
    lastEventTime=0;
    lastArrivalTime=0;
}

int Server::getArrivalCount() { return arrivalCount; }
int Server::getQMax() { return qMax; }
double Server::getQArea() { return qArea; }
double Server::getMaxDelay() { return maxDelay; }
double Server::getTotalDelay() { return totalDelay; }
double Server::getUtilTime() { return totalUtilization; }
double Server::getHogoutTime() { return totalHogout; }
Queue<Train>* Server::unloadedTrains() { return &served; }

void Server::arrivalHandler()
{
    double now=simulator->now();
    qArea+=queue.size()*(now-lastEventTime);
    qMax=std::max(qMax, (int) queue.size());
    lastEventTime=now;
    arrivalCount++;
    lastArrivalTime=now;
    
    Train train(arrivalCount);
    train.arrivalTime=now;
    // std::cout << "a " << simulator->now() << '\n';

    if(status==0)
    {
        status=1;
        lastUtilTime=now;
        serve(train);
    }
    else queue.enqueue(train);

    simulator->schedule(new Arrival(simulator), RandomNumber::exponential(arrivalMean));
}

void Server::departureHandler()
{
    double now=simulator->now();
    qArea+=queue.size()*(now-lastEventTime);
    lastEventTime=now;
    maxDelay=std::max(maxDelay, now-lastArrivalTime);
    totalDelay+=now-lastArrivalTime;

    if(queue.isEmpty())
    {
        status=0;
        totalUtilization+=now-lastUtilTime;
    }
    else
    {
        Train train=queue.dequeue();
        serve(train);
    }
}

void Server::serve(Train train)
{
    double now=simulator->now();
    train.startOfServiceTime=now;

    double temp=train.arrivalTime, unloadTime=RandomNumber::uniform(serviceMin, serviceMax), hogoutDelay=0, crt;
    while(temp<train.startOfServiceTime)
    {
        if(temp==train.arrivalTime) crt=0;
        else crt=RandomNumber::uniform(crewDelayMin, crewDelayMax);
        temp+=crt;

        if(temp>train.startOfServiceTime) hogoutDelay+=train.startOfServiceTime-temp;

        temp+=RandomNumber::uniform(crewMin, crewMax);
    }

    while(temp<train.startOfServiceTime+unloadTime+hogoutDelay)
    {
        crt=RandomNumber::uniform(crewDelayMin, crewDelayMax);
        temp+=crt;
        hogoutDelay+=crt;

        temp+=RandomNumber::uniform(crewMin, crewMax);
    }

    totalHogout+=hogoutDelay;
    totalUtilization-=hogoutDelay;
    train.departureTime=now+unloadTime+hogoutDelay;
    served.enqueue(train);
    
    // std::cout << "s " << simulator->now() << '\n';
    simulator->schedule(new Departure(simulator), unloadTime+hogoutDelay);
}
