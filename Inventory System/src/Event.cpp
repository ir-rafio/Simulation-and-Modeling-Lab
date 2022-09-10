#include "Event.hpp"
#include "Simulator.hpp"

Event::Event(Simulator *s): simulator(s) {}
void Event::setTime(const double _time) { time=_time; }
bool Event::earlier(Event* e1, Event* e2) { return e1->time <= e2->time; }

Evaluation::Evaluation(Simulator *s): Event(s) {}
void Evaluation::handle() { simulator->getInventory()->evaluationHandler(); }

Supply::Supply(Simulator *s, int _amount): Event(s) , amount(_amount) {}
void Supply::handle() { simulator->getInventory()->supplyHandler(amount); }

Demand::Demand(Simulator *s): Event(s) {}
void Demand::handle() { simulator->getInventory()->demandHandler(); }

Termination::Termination(Simulator *s): Event(s) {}
void Termination::handle() { simulator->getInventory()->terminationHandler(); }
