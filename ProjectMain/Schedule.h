#pragma once
#ifndef SCHEDULE_H
#define SCHEDULE_H
#include "Section.h"

#include<string>
#include<array>
#include<vector>
#include<time.h>
#include<map>
#include<set>
#include<iostream>
using namespace std;
class InvalidArgumentException {};
class Schedule {
	
private:
	//only the optimizer is allowed to alter the fitness of a schedule
	friend class Optimizer;
	int fitness;
	map <string, array<array<Section, 13>, 5>> profSched;
	vector<Section> classes;
	//constructor used within spliceSchedules
	Schedule(map <string, array<array<Section, 13>, 5>> profSched, vector<Section> classes);
	
public:
	
	//creates a random schedule for a class list based on scheduling rules
	Schedule(vector<Section> classes);
	
	/*splices two schedules at a given day and time. 
	should only be used on schedules that share the same class list
	Day range: [0,4] Time range: [0,12]
	returns 2 children schedules
	This way of splicing schedules did very little to improve fitness, as it usually resulted in credit disparities
	*/
	vector<Schedule> spliceSchedules(Schedule s2, int day, int time);
	//profSplit should be a number between 1 and the number of instructors in the schedule
	//this splice gives each child schedules for some instructors from one parent, and some from the other parent
	vector<Schedule> spliceSchedulesV2(Schedule s2, int profSplit);
	//prints schedule to console, empty sections are not printed
	void displaySchedule();
	//returns the actual data structure of the schedule for the fitness function to parse
	map <string, array<array<Section, 13>, 5>> getData();
	int getFitness();
	//returns the list of classes associated with the schedule
	vector<Section> getClasses();
	//compares schedules by fitness
	bool operator<(Schedule s1);
};
#endif
