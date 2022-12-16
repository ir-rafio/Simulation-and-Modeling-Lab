#include <bits/stdc++.h>
#include "Event.hpp"
#include "Simulator.hpp"
#include "CNG.hpp"
#include "Terminal.hpp"

Event::Event() {}
void Event::setTime(const double _time) { time=_time; }
void Event::print() { std::cout << time << std::endl; }
bool Event::earlier(Event* e1, Event* e2) { return e1->time < e2->time; }

Arrival::Arrival(Terminal* t): terminal(t) {}
void Arrival::handle() { terminal->passengerArrivalHandler(); }
void Arrival::print() { std::cout << 'a' << ' ' << terminal->getName() << ' '; Event::print(); }

Departure::Departure(CNG *c): cng(c) {}
void Departure::handle() { cng->departureHandler(); }
void Departure::print() { std::cout << 'd' << ' ' ; Event::print(); }

TripStart::TripStart(CNG *c): cng(c) {}
void TripStart::handle() { cng->startTrip(); }
void TripStart::print() { std::cout << 's' << ' ' ; Event::print(); }
