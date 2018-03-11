#pragma once
#include "Scheduler.hpp"
class RRScheduler :
	public Scheduler
{
public:
	RRScheduler(std::string name, int stepSize);
	~RRScheduler();


	void arrive(Job job);
	std::string update();
	std::string handleCompletion();

	int mStepSize;
	int mCurrentStep;
	int mCurrentJob;
	int mMarkJobForCompletion;
};

