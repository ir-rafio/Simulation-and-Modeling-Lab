#include "Train.hpp"

Train::Train(): id(-1), arrivalTime(-1), startOfServiceTime(-1), departureTime(-1) {}

Train::Train(int _id): id(_id), arrivalTime(-1), startOfServiceTime(-1), departureTime(-1) {}

double Train::getArrivalTime() { return arrivalTime; }
double Train::getStartOfServiceTime() { return startOfServiceTime; }
double Train::getDepartureTime() { return departureTime; }

double Train::queueDelay() { return startOfServiceTime-arrivalTime; }
double Train::serviceDelay() { return departureTime-startOfServiceTime; }
double Train::totalWaitingTime() { return departureTime-arrivalTime; }
