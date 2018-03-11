#pragma once
#include "Job.hpp"
#include <deque>

class Scheduler
{
public:
	Scheduler(std::string name);
	~Scheduler();

	virtual void arrive(Job job);
	virtual std::string update();
	virtual std::string handleCompletion();

	std::string name;
	static int timePassed;
	std::deque<Job> currentJobs;
};

