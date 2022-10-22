#include "Simulator.hpp"

Simulator::Simulator(double arrivalMean, double serviceMean): eventList(Heap<Event*>(Event::earlier))
{
    int i;
    for(i=0; i<3; i++) server[i]=nullptr;
    reset(arrivalMean, serviceMean);
}

Simulator::~Simulator()
{
    int i;
    while(!eventList.isEmpty()) delete (eventList.pop());
    for(i=0; i<3; i++) if(server[i]) delete server[i];
}

void Simulator::reset(double arrivalMean, double serviceMean)
{
    int i;
    while(!eventList.isEmpty()) delete eventList.pop();
    for(i=0; i<3; i++) if(server[i]) delete server[i];
    
    for(i=0; i<3; i++) server[i]=new Server(this, arrivalMean, serviceMean);
    clock=0;

    schedule(new Arrival(this), RandomNumber::exponential(arrivalMean));
}

void Simulator::moveBetweenLines()
{
    int i, j=0, k=0, temp;

    for(i=0; i<3; i++)
    {
        if(server[i]->deque.size()<server[j]->deque.size()) j=i;
        if(server[i]->deque.size()>server[k]->deque.size()) k=i;
    }

    if(server[k]->deque.size()>server[j]->deque.size())
    {
        Job job=server[k]->deque.back(); server[k]->deque.pop_back();
        server[j]->deque.push_back(job);      
    }
}

void Simulator::run()
{
    Event *event;

    while(!eventList.isEmpty())
    {
        event=eventList.pop();
        clock=event->time;
        event->handle();
        if(event) delete event;
    }
}

void Simulator::schedule(Event *event, double interval)
{
    event->setTime(clock+interval);
    eventList.push(event);
}

Server* Simulator::getServer()
{
    int i, j, m=INT_MAX, temp;

    for(i=0; i<3; i++) 
    {
        temp=server[i]->getQSize();

        if(temp<m)
        {
            j=i;
            m=temp;
        }
    }

    return server[j];
}

double Simulator::now() { return clock; }

double Simulator::maxDelay()
{
    return std::max(server[0]->getMaxDelay(), std::max(server[1]->getMaxDelay(), server[2]->getMaxDelay()));
}

double Simulator::avgDelay()
{
    return (server[0]->getTotalDelay()+server[1]->getTotalDelay()+server[2]->getTotalDelay())/
    (server[0]->getArrivalCount()+server[1]->getArrivalCount()+server[2]->getArrivalCount());
}

int Simulator::maxQLength()
{
    // std::cout << server[0]->getQMax() << ' ' << server[1]->getQMax() << ' ' << server[2]->getQMax() << '\n';
    // std::cout << '\t' << server[0]->getQArea() << ' ' << server[1]->getQArea() << ' ' << server[2]->getQArea() << '\n';
    return std::max(server[0]->getQMax(), std::max(server[1]->getQMax(), server[2]->getQMax()));
}

double Simulator::avgQLength()
{
    return (server[0]->getQArea()+server[1]->getQArea()+server[2]->getQArea())/(clock*3);
}

double Simulator::utilizationRatio()
{
    return (server[0]->getUtilTime()+server[1]->getUtilTime()+server[2]->getUtilTime())/(clock*3);
}