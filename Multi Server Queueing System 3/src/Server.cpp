#include "Server.hpp"
#include "Simulator.hpp"

Server::Server(Simulator* s, double _arrivalMean, double _serviceMean): arrivalMean(_arrivalMean), serviceMean(_serviceMean), simulator(s)
{
    status=0;

    arrivalCount=0;
    qMax=0;
    qArea=0;
    maxDelay=0;
    totalDelay=0;
    totalUtilization=0;
    lastEventTime=0;
    lastArrivalTime=0;
}

int Server::getArrivalCount() { return arrivalCount; }
int Server::getQMax() { return qMax; }
int Server::getQSize() { return deque.size(); }
double Server::getQArea() { return qArea; }
double Server::getMaxDelay() { return maxDelay; }
double Server::getTotalDelay() { return totalDelay; }
double Server::getUtilTime() { return totalUtilization; }

void Server::arrivalHandler()
{
    double now=simulator->now();
    qArea+=deque.size()*(now-lastEventTime);
    qMax=std::max(qMax, (int) deque.size());
        // std::cout << deque.size() << ' ' << qMax << ' ' << qArea << '\n';
    lastEventTime=now;
    arrivalCount++;
    lastArrivalTime=now;
    
    Job job(arrivalCount);
    job.arrivalTime=now;
    // std::cout << simulator->now() << ',' << 'a' << ',' << job.id << ',' << status << ',' << deque.size() << '\n';

    if(status==0)
    {
        status=1;
        lastUtilTime=now;
        serve(job);
    }
    else deque.push_back(job);

    if(arrivalCount<100) simulator->schedule(new Arrival(simulator), RandomNumber::exponential(arrivalMean));
}

void Server::departureHandler()
{
    double now=simulator->now();
    qArea+=deque.size()*(now-lastEventTime);
    qMax=std::max(qMax, (int) deque.size());
        // std::cout << deque.size() << ' ' << qMax << ' ' << qArea << '\n';
    lastEventTime=now;
    maxDelay=std::max(maxDelay, now-lastArrivalTime);
    totalDelay+=now-lastArrivalTime;

    // std::cout << simulator->now() << ',' << 'd' << ',' << served.back().id << ',' << status << ',' << deque.size() << '\n';

    if(deque.empty())
    {
        status=0;
        totalUtilization+=now-lastUtilTime;
    }
    else
    {
        Job job=deque.front(); deque.pop_front();
        serve(job);
        simulator->moveBetweenLines();
    }
}

void Server::serve(Job job)
{
    double now=simulator->now(), serviceTime=RandomNumber::exponential(serviceMean);
    job.startOfServiceTime=now;
    job.departureTime=now+serviceTime;

    simulator->schedule(new Departure(this), serviceTime);
    // std::cout << simulator->now() << ',' << 's' << ',' << job.id << ',' << status << ',' << deque.size() << '\n';
}
