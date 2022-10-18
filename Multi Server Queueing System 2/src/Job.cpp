#include "Job.hpp"

Job::Job(): id(-1), arrivalTime(-1), startOfServiceTime(-1), departureTime(-1) {}

Job::Job(int _id): id(_id), arrivalTime(-1), startOfServiceTime(-1), departureTime(-1) {}

double Job::getArrivalTime() { return arrivalTime; }
double Job::getStartOfServiceTime() { return startOfServiceTime; }
double Job::getDepartureTime() { return departureTime; }

double Job::queueDelay() { return startOfServiceTime-arrivalTime; }
double Job::serviceDelay() { return departureTime-startOfServiceTime; }
double Job::totalWaitingTime() { return departureTime-arrivalTime; }
