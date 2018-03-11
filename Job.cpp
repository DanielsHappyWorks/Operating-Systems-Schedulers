#include "Job.hpp"

Job::Job() {
}

Job::Job(std::string name, int arrival, int duration) : mName(name), mArrival(arrival), mDuration(duration), mCompletion(0), mIsCompleted(false)
{
}

Job::~Job(){
}

std::string Job::process() {
	//process job
	if (!mIsCompleted) {
		mCompletion++;
		if (mDuration == mCompletion) {
			mIsCompleted = true;
		}
		return mName;
	}
	return "";
}

std::string Job::isCompleted() {
	if (mIsCompleted) {
		return mName;
	}
	return "";
}