#pragma once
#include "Scheduler.hpp"
#include <deque>
class FIFOScheduler :
	public Scheduler
{
public:
	FIFOScheduler(std::string name);
	~FIFOScheduler();

	void arrive(Job job);
	std::string update();
	std::string handleCompletion();

	std::deque<Job> currentJobs;
};

