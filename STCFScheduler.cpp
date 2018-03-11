#include "STCFScheduler.hpp"


STCFScheduler::STCFScheduler(std::string name) :Scheduler(name)
{
}


STCFScheduler::~STCFScheduler()
{
}

bool STCFJobComprator(Job left, Job right) {
	if (left.mDuration == right.mDuration) {
		return true;
	}
	return left.mDuration < right.mDuration;
}

void STCFScheduler::arrive(Job job) {
	Scheduler::arrive(job);
	sort(currentJobs.begin(), currentJobs.end(), &STCFJobComprator);
}

std::string STCFScheduler::update() {
	return Scheduler::update();
}

std::string STCFScheduler::handleCompletion() {
	return Scheduler::handleCompletion();
}