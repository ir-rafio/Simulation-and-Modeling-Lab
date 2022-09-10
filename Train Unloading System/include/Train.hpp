#ifndef TRAIN_HPP
#define TRAIN_HPP

class Server;

class Train
{
protected:
    int id;
    double arrivalTime, startOfServiceTime, departureTime;
    friend class Server;

public:
    Train();
    Train(int);

    double getArrivalTime();
    double getStartOfServiceTime();
    double getDepartureTime();
    
    double queueDelay();
    double serviceDelay();
    double totalWaitingTime();
};

#endif
