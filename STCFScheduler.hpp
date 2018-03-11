#pragma once
#include "Scheduler.hpp"
#include <algorithm>

class STCFScheduler :
	public Scheduler
{
public:
	STCFScheduler(std::string name);
	~STCFScheduler();

	void arrive(Job job);
	std::string update();
	std::string handleCompletion();
};

