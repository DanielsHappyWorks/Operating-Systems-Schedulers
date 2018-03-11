#pragma once
#include "Job.hpp"
#include "FIFOScheduler.hpp"
#include "SJFScheduler.hpp"
#include "STCFScheduler.hpp"
#include <map>
#include <vector>
#include <iostream>
#include <iomanip>

std::map<int, Job> inputData;
std::vector<Scheduler*> schedulers;

void processInput() {
	inputData[10] = Job("A", 10, 18);
	inputData[29] = Job("B", 29, 2);
	inputData[3] = Job("X", 3, 100);
	inputData[4] = Job("Z", 4, 43);
	inputData[1] = Job("UNKNOWN", 1, 92);
}

void setupSchedulers() {
	schedulers.push_back(new FIFOScheduler("FIFO"));
	schedulers.push_back(new SJFScheduler("SJF"));
	schedulers.push_back(new STCFScheduler("STCF"));
}

int main() {
	processInput();
	setupSchedulers();

	std::cout << "T ";
	for each (Scheduler* scheduler in schedulers)
	{
		std::cout << "\t" << scheduler->name << "\t";
	}
	std::cout << std::endl;

	while (Scheduler::timePassed <= 1000) {
		if (!inputData[Scheduler::timePassed].mName.empty()) {
			for each (Scheduler* scheduler in schedulers)
			{
				scheduler->arrive(inputData[Scheduler::timePassed]);
			}
			std::cout << "* ARRIVED: " << inputData[Scheduler::timePassed].mName << std::endl;
		}

		std::cout << Scheduler::timePassed << " ";
		for each (Scheduler* scheduler in schedulers)
		{
			std::cout << "\t" << scheduler->update() << "\t";
		}
		std::cout << std::endl;

		for each (Scheduler* scheduler in schedulers)
		{
			std::string s = scheduler->handleCompletion();
			if (!s.empty()) {
				std::cout << "* COMPLETE: " << s << ":" << scheduler->name << std::endl;
			}
		}

		Scheduler::timePassed++;
	}

	std::cin.get();
}