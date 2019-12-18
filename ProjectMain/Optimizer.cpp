#include "Optimizer.h"
using namespace std;
Optimizer::Optimizer() {
	//this rule only needs used with spliceSchedules, spliceSchedulesV2 doesn't effect credit hours
	//rules.push_back(new CreditDisparity());
	rules.push_back(new LongDays());
	rules.push_back(new LateNightsEarlyMornings());
	rules.push_back(new TooManyNights());
	rules.push_back(new BackToBack());
	rules.push_back(new CrowdedCommon());
	rules.push_back(new TooManyClasses());
	rules.push_back(new LongClasses());
};
int Optimizer::setTotalFitness(Schedule &schedule) {
	int fitness = 0;
	for (int i = 0; i < rules.size(); ++i) {
		fitness += rules.at(i)->getFitness(schedule);
	}
	schedule.fitness = fitness;
	return fitness;
};
//sorts population from most to least fit
void Optimizer::sortByFittest(vector<Schedule> &population) {

	for (int i = 0; i < population.size(); ++i) {
		setTotalFitness(population.at(i));
	}
	sort(population.begin(), population.end());

};