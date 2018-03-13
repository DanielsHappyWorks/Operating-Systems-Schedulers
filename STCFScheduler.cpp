#include "STCFScheduler.hpp"


STCFScheduler::STCFScheduler(std::string name) :Scheduler(name)
{
}


STCFScheduler::~STCFScheduler()
{
}

bool STCFJobComprator(Job left, Job right) {
	return left.mDuration < right.mDuration;
}

void STCFScheduler::arrive(Job job) {
	Scheduler::arrive(job);
	if (!currentJobs.empty() && currentJobs.size() > 1) {
		sort(currentJobs.begin(), currentJobs.end(), &STCFJobComprator);
	}
}

std::string STCFScheduler::update() {
	return Scheduler::update();
}

std::string STCFScheduler::handleCompletion() {
	return Scheduler::handleCompletion();
}