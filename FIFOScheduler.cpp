#include "FIFOScheduler.hpp"



FIFOScheduler::FIFOScheduler(std::string name) : Scheduler(name)
{
}


FIFOScheduler::~FIFOScheduler()
{
}

void FIFOScheduler::arrive(Job job) {
	Scheduler::arrive(job);
}

std::string FIFOScheduler::update() {
	return Scheduler::update();
}

std::string FIFOScheduler::handleCompletion() {
	return Scheduler::handleCompletion();
}