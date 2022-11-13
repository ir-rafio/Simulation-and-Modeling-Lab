#include "Server.hpp"
#include "Simulator.hpp"

Server::Server(Simulator* s, double _arrivalMean, double _serviceMean): arrivalMean(_arrivalMean), serviceMean(_serviceMean), simulator(s)
{
    status=0;

    arrivalCount=0;
    maxDelay=0;
    totalDelay=0;
    totalUtilization=0;
    lastArrivalTime=0;
}

int Server::getArrivalCount() { return arrivalCount; }
int Server::getQSize() { return queue.size(); }
// int Server::getQMax() { return qMax; }
// double Server::getQArea() { return qArea; }
double Server::getMaxDelay() { return maxDelay; }
double Server::getTotalDelay() { return totalDelay; }
double Server::getUtilTime() { return totalUtilization; }

void Server::arrivalHandler()
{
    double now=simulator->now();
    arrivalCount++;
    lastArrivalTime=now;
    simulator->updateQStat();
    
    Job job(arrivalCount);
    job.arrivalTime=now;
    // std::cout << simulator->now() << ',' << 'a' << ',' << job.id << ',' << status << ',' << queue.size() << '\n';

    if(status==0)
    {
        status=1;
        lastUtilTime=now;
        serve(job);
    }
    else queue.push_back(job);

    if(arrivalCount<100) simulator->schedule(new Arrival(simulator), RandomNumber::exponential(arrivalMean));
}

void Server::departureHandler()
{
    double now=simulator->now();
    maxDelay=std::max(maxDelay, now-lastArrivalTime);
    totalDelay+=now-lastArrivalTime;
    simulator->updateQStat();

    // std::cout << simulator->now() << ',' << 'd' << ',' << served.back().id << ',' << status << ',' << queue.size() << '\n';

    if(queue.empty())
    {
        status=0;
        totalUtilization+=now-lastUtilTime;
    }
    else
    {
        Job job=queue.back(); queue.pop_back();
        serve(job);
    }

    moveBetweenLines();
}

void Server::moveBetweenLines()
{
    int i, j=0;
    double now=simulator->now();

    Server* longServer=simulator->longServer();

    if(longServer->getQSize()>getQSize()+1)
    {
        Job job=longServer->queue.back(); longServer->queue.pop_back();
        // longServer->arrivalCount--;

        arrivalHandler();
    }
}

void Server::serve(Job job)
{
    double now=simulator->now(), serviceTime=RandomNumber::exponential(serviceMean);
    job.startOfServiceTime=now;
    job.departureTime=now+serviceTime;

    simulator->schedule(new Departure(this), serviceTime);
    // std::cout << simulator->now() << ',' << 's' << ',' << job.id << ',' << status << ',' << queue.size() << '\n';
}
