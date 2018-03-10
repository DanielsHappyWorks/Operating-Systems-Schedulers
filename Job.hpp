#pragma once
#include <string>

class Job
{
public:
	Job();
	Job(std::string name, int arrival, int duration);
	~Job();
	std::string process();
	std::string isCompleted();

	std::string mName;
	int mArrival;
	int mDuration;
	int mCompletion;
	bool mIsCompleted;
};

