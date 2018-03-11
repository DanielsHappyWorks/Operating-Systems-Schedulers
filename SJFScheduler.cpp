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

bool stortestJobComprator(Job left, Job right) {
	if (left.mDuration == right.mDuration) {
		return true;
	}
	return left.mDuration < right.mDuration;
}

std::string SJFScheduler::handleCompletion() {
	std::string output = Scheduler::handleCompletion();
	if (!output.empty()) {
		sort(currentJobs.begin(),currentJobs.end(), &stortestJobComprator);
		return output;
	}
	return "";
}