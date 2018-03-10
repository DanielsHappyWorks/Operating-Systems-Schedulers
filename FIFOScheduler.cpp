#include "FIFOScheduler.hpp"



FIFOScheduler::FIFOScheduler(std::string name) : Scheduler(name)
{
}


FIFOScheduler::~FIFOScheduler()
{
}

void FIFOScheduler::arrive(Job job) {
	currentJobs.push_back(job);
}

std::string FIFOScheduler::update() {
	if (!currentJobs.empty()) {
		return currentJobs.front().process();
	}
	return "";
}

std::string FIFOScheduler::handleCompletion() {
	if (!currentJobs.empty()) {
		std::string job = currentJobs.front().isCompleted();
		if (!job.empty()) {
			currentJobs.pop_front();
			return job;
		}
	}
	return "";
}