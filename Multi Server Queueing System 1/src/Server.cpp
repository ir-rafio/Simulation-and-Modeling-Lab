#include "Server.hpp"
#include "Simulator.hpp"

Server::Server(Simulator* s, double _arrivalMean, double _serviceMean): arrivalMean(_arrivalMean), serviceMean(_serviceMean), simulator(s)
{
    queue=&(s->queue);
    status=0;

    totalUtilization=0;
    lastEventTime=0;
    lastArrivalTime=0;
    lastUtilTime=0;
}

Queue<Job>* Server::jobsDone() { return &served; }
bool Server::free() { return !status; }
double Server::getUtilTime() { return totalUtilization; }

void Server::arrivalHandler()
{
    double now=simulator->now();
    simulator->qArea+=queue->size()*(now-lastEventTime);
    simulator->qMax=std::max(simulator->qMax, (int) queue->size());
        // std::cout << queue->size() << ' ' << simulator->qMax << ' ' << simulator->qArea << '\n';
    lastEventTime=now;
    simulator->arrivalCount++;
    lastArrivalTime=now;
    
    Job job(simulator->arrivalCount);
    job.arrivalTime=now;
    // std::cout << simulator->now() << ',' << 'a' << ',' << job.id << ',' << status << ',' << queue->size() << '\n';

    if(status==0)
    {
        status=1;
        lastUtilTime=now;
        serve(job);
    }
    else queue->enqueue(job);

    if(simulator->arrivalCount<100) simulator->schedule(new Arrival(simulator), RandomNumber::exponential(arrivalMean));
}

void Server::departureHandler()
{
    double now=simulator->now();
    simulator->qArea+=queue->size()*(now-lastEventTime);
    simulator->qMax=std::max(simulator->qMax, (int) queue->size());
        // std::cout << queue->size() << ' ' << simulator->qMax << ' ' << simulator->qArea << '\n';
    lastEventTime=now;
    simulator->maxDelay=std::max(simulator->maxDelay, now-lastArrivalTime);
    simulator->totalDelay+=now-lastArrivalTime;

    // std::cout << simulator->now() << ',' << 'd' << ',' << served.back().id << ',' << status << ',' << queue->size() << '\n';

    if(queue->isEmpty())
    {
        status=0;
        totalUtilization+=now-lastUtilTime;
    }
    else
    {
        Job job=queue->dequeue();
        serve(job);
    }
}

void Server::serve(Job job)
{
    double now=simulator->now(), serviceTime=RandomNumber::exponential(serviceMean);
    job.startOfServiceTime=now;
    job.departureTime=now+serviceTime;
    served.enqueue(job);

    simulator->schedule(new Departure(this), serviceTime);
    // std::cout << simulator->now() << ',' << 's' << ',' << job.id << ',' << status << ',' << queue->size() << '\n';
}
