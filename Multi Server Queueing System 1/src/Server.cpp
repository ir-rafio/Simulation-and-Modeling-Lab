#include "Server.hpp"
#include "Simulator.hpp"

Server::Server(Simulator* s, double _arrivalMean, double _serviceMean): arrivalMean(_arrivalMean), serviceMean(_serviceMean), simulator(s)
{
    queue=&(s->queue);
    status=0;

    totalUtilization=0;
    lastArrivalTime=0;
    lastUtilTime=0;
}

// Queue<Job>* Server::jobsDone() { return &served; }
bool Server::free() { return !status; }
double Server::getUtilTime() { return totalUtilization; }

void Server::arrivalHandler()
{
    double now=simulator->now();
    simulator->arrivalCount++;
    lastArrivalTime=now;
    simulator->updateQStat();
        // simulator->trace << queue->size() << ' ' << simulator->qMax << ' ' << simulator->qArea << '\n';
    
    Job job(simulator->arrivalCount);
    job.arrivalTime=now;
        // simulator->trace << simulator->now() << ',' << 'a' << ',' << job.id << ',' << status << ',' << queue->size() << '\n';

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
    simulator->maxDelay=std::max(simulator->maxDelay, now-lastArrivalTime);
    simulator->totalDelay+=now-lastArrivalTime;
    simulator->updateQStat();
        // simulator->trace << queue->size() << ' ' << simulator->qMax << ' ' << simulator->qArea << '\n';
        // simulator->trace << lastArrivalTime << ' ' << now-lastArrivalTime << ' ' << simulator->maxDelay << ' ' << simulator->totalDelay << '\n';
        // simulator->trace << simulator->now() << ',' << 'd' << ',' << served.back().id << ',' << status << ',' << queue->size() << '\n';

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
        // simulator->trace << simulator->now() << ',' << 's' << ',' << job.id << ',' << status << ',' << queue->size() << '\n';
}