#pragma once
#include "Job.hpp"
#include <deque>
#include <map>

class Scheduler
{
public:
	Scheduler(std::string name);
	~Scheduler();
	float processResponseTimeAverage();
	float processTurnoverTimeAverage();

	virtual void arrive(Job job);
	virtual std::string update();
	virtual std::string handleCompletion();

	std::string name;
	std::deque<Job> currentJobs;
	std::map<std::string, int> turnoverTimes;
	std::map<std::string, int> responseTimes;
	bool isCompleted;


	static int timePassed;
	static bool areCompleted;
};

