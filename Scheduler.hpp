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
	std::deque<Job> currentJobs;
	bool isCompleted;

	static int timePassed;
	static bool areCompleted;
};

