#pragma once
#include "Job.hpp"
#include "FIFOScheduler.hpp"
#include "SJFScheduler.hpp"
#include "STCFScheduler.hpp"
#include "RRScheduler.hpp"
#include <map>
#include <set>
#include <vector>
#include <iostream>

std::map<int, Job> inputData;
std::vector<Scheduler*> schedulers;
std::set<std::string> allJobNames;

void processInput() {
	std::string name;
	int arrivalTime;
	int durantion;

	while (std::cin) {
		std::cin >> name >>  arrivalTime >> durantion;
		inputData[arrivalTime] = Job(name, arrivalTime, durantion);
		allJobNames.emplace(name);
	}

	/* DEBUG INPUT
	inputData[10] = Job("A", 10, 18);
	inputData[29] = Job("B", 29, 2);
	inputData[3] = Job("C", 3, 100);
	inputData[4] = Job("D", 4, 43);
	inputData[1] = Job("E", 29, 92);*/
}

void setupSchedulers() {
	schedulers.push_back(new FIFOScheduler("FIFO"));
	schedulers.push_back(new SJFScheduler("SJF"));
	schedulers.push_back(new STCFScheduler("STCF"));
	schedulers.push_back(new RRScheduler("RR1", 1));
	schedulers.push_back(new RRScheduler("RR2", 2));
}

void outputSimulation() {
	std::cout << "T ";
	for each (Scheduler* scheduler in schedulers)
	{
		std::cout << "\t" << scheduler->name << "\t";
	}
	std::cout << std::endl;

	while (!Scheduler::areCompleted && !inputData.empty()) {
		//add process to queue if has arrived
		if (!inputData[Scheduler::timePassed].mName.empty()) {
			for each (Scheduler* scheduler in schedulers)
			{
				scheduler->arrive(inputData[Scheduler::timePassed]);
			}
			std::cout << "* ARRIVED: " << inputData[Scheduler::timePassed].mName << std::endl;
			inputData.erase(Scheduler::timePassed);
		}

		//update process
		std::cout << Scheduler::timePassed << " ";
		for each (Scheduler* scheduler in schedulers)
		{
			std::cout << "\t" << scheduler->update() << "\t";
		}
		std::cout << std::endl;

		//check if a process has finished
		for each (Scheduler* scheduler in schedulers)
		{
			std::string s = scheduler->handleCompletion();
			if (!s.empty()) {
				std::cout << "* COMPLETE: " << s << ":" << scheduler->name << std::endl;
			}
		}

		//check if schedulers are completed
		bool areCompleted = true;
		for each (Scheduler* scheduler in schedulers)
		{
			if (!scheduler->isCompleted) {
				areCompleted = false;
				break;
			}
		}
		Scheduler::areCompleted = areCompleted;

		Scheduler::timePassed++;
	}
	std::cout << "= SIMULATION COMPLETE" << std::endl;
}

void outputTrunoverPerJobStat() {
	//Turnaround Time Per-Job Statistics
	std::cout << "#\tJOB\t";
	for each (Scheduler* scheduler in schedulers)
	{
		std::cout << scheduler->name << "\t";
	}
	std::cout << std::endl;

	for each (std::string jobName in allJobNames)
	{
		std::cout << "T\t";
		std::cout << jobName << "\t";
		for each (Scheduler* scheduler in schedulers)
		{
			std::cout << scheduler->turnoverTimes[jobName] << "\t";
		}
		std::cout << std::endl;
	}
	std::cout << "= INDIVIDUAL STATS COMPLETE" << std::endl;
}

void outputResponsePerJobStat() {
	//Response Time Per-Job Statistics
	std::cout << "#\tJOB\t";
	for each (Scheduler* scheduler in schedulers)
	{
		std::cout << scheduler->name << "\t";
	}
	std::cout << std::endl;

	for each (std::string jobName in allJobNames)
	{
		std::cout << "R\t";
		std::cout << jobName << "\t";
		for each (Scheduler* scheduler in schedulers)
		{
			std::cout << scheduler->responseTimes[jobName] << "\t";
		}
		std::cout << std::endl;
	}
	std::cout << "= INDIVIDUAL STATS COMPLETE" << std::endl;
}

void outputAverageStats() {
	std::cout << "# SCHEDULER AVG_TURNAROUND AVG_RESPONSE" << std::endl;
	for each (Scheduler* scheduler in schedulers)
	{
		std::cout << "@\t" << scheduler->name << "\t" << scheduler->processTurnoverTimeAverage() << "\t" << scheduler->processResponseTimeAverage() << std::endl;
	}
	std::cout << "= AGGREGATE STATS COMPLETE" << std::endl;
}

int main() {
	processInput();
	setupSchedulers();
	outputSimulation();
	outputTrunoverPerJobStat();
	outputResponsePerJobStat();
	outputAverageStats();
	std::cin.get();
}