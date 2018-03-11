#include "Scheduler.hpp"

int Scheduler::timePassed = 1;
bool Scheduler::areCompleted = false;

Scheduler::Scheduler(std::string name) :name(name), isCompleted(false)
{
}

Scheduler::~Scheduler()
{
}

void Scheduler::arrive(Job job) {
	currentJobs.push_back(job);
	isCompleted = false;
}

std::string Scheduler::update() {
	if (!currentJobs.empty()) {
		return currentJobs.front().process();
	}
	return "";
}

std::string Scheduler::handleCompletion() {
	if (!currentJobs.empty()) {
		std::string job = currentJobs.front().isCompleted();
		if (!job.empty()) {
			currentJobs.pop_front();
			return job;
		}
	}
	else {
		isCompleted = true;
	}
	return "";
}