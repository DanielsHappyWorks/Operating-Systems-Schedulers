#include "SJFScheduler.hpp"

SJFScheduler::SJFScheduler(std::string name) :Scheduler(name)
{
}


SJFScheduler::~SJFScheduler()
{
}

void SJFScheduler::arrive(Job job) {
	Scheduler::arrive(job);
}

std::string SJFScheduler::update() {
	return Scheduler::update();
}

bool SJFJobComprator(Job left, Job right) {
	return left.mDuration < right.mDuration;
}

std::string SJFScheduler::handleCompletion() {
	std::string output = Scheduler::handleCompletion();
	if (!output.empty()) {
		if (currentJobs.size() > 1) {
			sort(currentJobs.begin(), currentJobs.end(), &SJFJobComprator);
		}
		return output;
	}
	else {
		isCompleted = true;
	}
	return "";
}