#include "Event.hpp"
#include "Simulator.hpp"

Event::Event(Simulator *s): simulator(s) {}
void Event::setTime(const double _time) { time=_time; }
bool Event::earlier(Event* e1, Event* e2) { return e1->time <= e2->time; }

Arrival::Arrival(Simulator *s): Event(s) {}
void Arrival::handle() { simulator->getServer()->arrivalHandler(); }

Departure::Departure(Simulator *s): Event(s) {}
void Departure::handle() { simulator->getServer()->departureHandler(); }
