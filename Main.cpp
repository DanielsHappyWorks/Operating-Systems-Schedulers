#include "Job.hpp"
#include "FIFOScheduler.hpp"
#include "SJFScheduler.hpp"
#include "STCFScheduler.hpp"
#include "RRScheduler.hpp"
#include <map>
#include <set>
#include <vector>
#include <iostream>

std::map<int, std::vector<Job>> inputData;
std::vector<Scheduler*> schedulers;
std::set<std::string> allJobNames;

void processInput() {
	std::string name;
	int arrivalTime;
	int durantion;

	while (std::cin) {
		std::cin >> name >>  arrivalTime >> durantion;
		inputData[arrivalTime].push_back(Job(name, arrivalTime, durantion));
		allJobNames.emplace(name);
	}
	
	/*DEBUG INPUT
	inputData[10].push_back(Job("A", 10, 18));
	inputData[29].push_back(Job("B", 29, 2));
	inputData[3].push_back(Job("C", 3, 100));
	inputData[4].push_back(Job("D", 4, 43));
	inputData[1].push_back(Job("Unknown", 1, 92)); */
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
	for (int i = 0; i<schedulers.size(); i++)
	{
		std::cout << "\t" << schedulers[i]->name << "\t";
	}
	std::cout << std::endl;

	bool isInputDataExhausted = false;
	while (!Scheduler::areCompleted || isInputDataExhausted) {
		//add process to queue if has arrived
		if (!inputData[Scheduler::timePassed].empty()) {
			for (int i = 0; i<inputData[Scheduler::timePassed].size(); i++)
			{
				for (int j = 0; j < schedulers.size(); j++)
				{
					schedulers[j]->arrive(inputData[Scheduler::timePassed][i]);
				}
				std::cout << "* ARRIVED: " << inputData[Scheduler::timePassed][i].mName << std::endl;
				allJobNames.emplace(inputData[Scheduler::timePassed][i].mName);
			}
			inputData.erase(Scheduler::timePassed);
		}

		//update process
		int count = 0;
		std::string output;
		for (int i = 0; i<schedulers.size(); i++)
		{
			output = schedulers[i]->update();
			if (!output.empty()) {
				if (count == 0) {
					std::cout << Scheduler::timePassed << " ";
				}
				std::cout << "\t" << output << "\t";
			}
			count++;
		}
		if (!output.empty()) {
			std::cout << std::endl;
		}


		//check if a process has finished
		for (int i = 0; i<schedulers.size(); i++)
		{
			std::string s = schedulers[i]->handleCompletion();
			if (!s.empty()) {
				std::cout << "* COMPLETE: " << s << ":" << schedulers[i]->name << std::endl;
			}
		}

		//check if schedulers are completed
		bool areCompleted = true;
		for (int i = 0; i<schedulers.size(); i++)
		{
			if (!schedulers[i]->isCompleted) {
				areCompleted = false;
				break;
			}
		}
		Scheduler::areCompleted = areCompleted;

		isInputDataExhausted = false;
		//check if all input is used up
		for (int i = 0; i < inputData.size(); i++)
		{
			if (!inputData[i].empty()) {
				isInputDataExhausted = true;
			}
		}

		Scheduler::timePassed++;
	}
	std::cout << "= SIMULATION COMPLETE" << std::endl << std::endl;
}

void outputTrunoverPerJobStat() {
	//Turnaround Time Per-Job Statistics
	std::cout << "#\tJOB\t";
	for (int i = 0; i<schedulers.size(); i++)
	{
		std::cout << schedulers[i]->name << "\t";
	}
	std::cout << std::endl;

	std::set<std::string>::iterator it;
	for (it = allJobNames.begin(); it != allJobNames.end(); it++) {
		std::cout << "T\t";
		std::cout << *it << "\t";
		for (int i = 0; i<schedulers.size(); i++)
		{
			std::cout << schedulers[i]->turnoverTimes[*it] << "\t";
		}
		std::cout << std::endl;
	}
	std::cout << "= INDIVIDUAL STATS COMPLETE" << std::endl << std::endl;
}

void outputResponsePerJobStat() {
	//Response Time Per-Job Statistics
	std::cout << "#\tJOB\t";
	for (int i = 0; i<schedulers.size(); i++)
	{
		std::cout << schedulers[i]->name << "\t";
	}
	std::cout << std::endl;

	std::set<std::string>::iterator it;
	for (it = allJobNames.begin(); it != allJobNames.end(); it++) {
		std::cout << "R\t";
		std::cout << *it << "\t";
		for (int i = 0; i<schedulers.size(); i++)
		{
			std::cout << schedulers[i]->responseTimes[*it] << "\t";
		}
		std::cout << std::endl;
	}
	std::cout << "= INDIVIDUAL STATS COMPLETE" << std::endl << std::endl;
}

void outputAverageStats() {
	std::cout << "# SCHEDULER AVG_TURNAROUND AVG_RESPONSE" << std::endl;
	for (int i = 0; i<schedulers.size(); i++)
	{
		std::cout << "@\t" << schedulers[i]->name << "\t" << schedulers[i]->processTurnoverTimeAverage() << "\t" << schedulers[i]->processResponseTimeAverage() << std::endl;
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
}