#ifndef JOB_HPP
#define JOB_HPP

class Server;

class Job
{
protected:
    int id;
    double arrivalTime, startOfServiceTime, departureTime;
    friend class Server;

public:
    Job();
    Job(int);

    double getArrivalTime();
    double getStartOfServiceTime();
    double getDepartureTime();
    
    double queueDelay();
    double serviceDelay();
    double totalWaitingTime();
};

#endif
