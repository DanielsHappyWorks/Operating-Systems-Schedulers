#include "RRScheduler.hpp"



RRScheduler::RRScheduler(std::string name, int stepSize) : Scheduler(name), mStepSize(stepSize), mCurrentStep(0), mCurrentJob(0), mMarkJobForCompletion(-1)
{
}


RRScheduler::~RRScheduler()
{
}

void RRScheduler::arrive(Job job) {
	Scheduler::arrive(job);
}

std::string RRScheduler::update() {
	std::string jobName = "";
	if (!currentJobs.empty()) {
		if (mCurrentJob >= currentJobs.size()) {
			mCurrentJob = 0;
		}

		currentJobs.at(mCurrentJob).process();
		jobName = currentJobs.at(mCurrentJob).mName;

		if (!jobName.empty() && !responseTimes[jobName]) {
			Job job = currentJobs.front();
			responseTimes[jobName] = (Scheduler::timePassed + 1 - job.mArrival);
		}

		if (!currentJobs.at(mCurrentJob).isCompleted().empty()) {
			mMarkJobForCompletion = mCurrentJob;
			mCurrentJob--;
			mCurrentStep = 1;
		}
		else {
			mMarkJobForCompletion = -1;
		}

		mCurrentStep++;
		if (mCurrentStep >= mStepSize) {
			mCurrentJob++;
			mCurrentStep = 0;
		}
		
		return jobName;
	}
	else {
		mMarkJobForCompletion = -1;
		return jobName;
	}
}

std::string RRScheduler::handleCompletion() {
	if (mMarkJobForCompletion != -1) {
		std::string jobName = currentJobs.at(mMarkJobForCompletion).mName;
		Job job = currentJobs.front();
		turnoverTimes[jobName] = (Scheduler::timePassed + 1 - job.mArrival);
		currentJobs.erase(currentJobs.begin() + mMarkJobForCompletion);
		return jobName;
	}
	if (currentJobs.empty()) {
		isCompleted = true;
	}
	return "";
}