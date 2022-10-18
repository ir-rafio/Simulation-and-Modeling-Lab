#include "Event.hpp"
#include "Simulator.hpp"
#include "Server.hpp"

Event::Event() {}
void Event::setTime(const double _time) { time=_time; }
bool Event::earlier(Event* e1, Event* e2) { return e1->time <= e2->time; }

Arrival::Arrival(Simulator *s): simulator(s) {}
void Arrival::handle() { simulator->getServer()->arrivalHandler(); }

Departure::Departure(Server *s): server(s) {}
void Departure::handle() { server->departureHandler(); }
