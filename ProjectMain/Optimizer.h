#pragma once
#ifndef OPTIMIZER_H
#define OPTIMIZER_H
#include"Schedule.h"
#include"Rule.h"
#include<vector>
#include<algorithm>
using namespace std;
class Optimizer {
private:
	
	//stores all subclasses of rule
	vector<Rule*> rules;
public:
	Optimizer();
	//sets fitness of a schedule and returns it
	int setTotalFitness(Schedule &schedule);
	//sorts a collection of schedules by fitness in place
	void sortByFittest(vector<Schedule> &population);
	
};
#endif