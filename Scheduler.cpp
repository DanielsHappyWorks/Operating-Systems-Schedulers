#include "Scheduler.hpp"

int Scheduler::timePassed = 1;

Scheduler::Scheduler(std::string name) :name(name)
{
}

Scheduler::~Scheduler()
{
}

void Scheduler::arrive(Job job) {

}

std::string Scheduler::update() {
	return "";
}

std::string Scheduler::handleCompletion() {
	return "";
}
