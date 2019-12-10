#pragma once
#ifndef SCHEDULE_H
#define SCHEDULE_H
#include "Section.h"
#include "Meeting.h"
#include<string>
#include<array>
#include<vector>
#include<time.h>
using namespace std;
class Schedule {
private:
	vector<Section> classes;
	vector<Meeting*> meetings;
	
public: 
	Schedule(vector<Section> classes, vector<Meeting*> meetings);
	
	//swaps meetings of the 2 schedules at a random point in the list. undefined behavior if 2 schedules with different class lists are used
	void spliceSchedule(Schedule &s1, Schedule &s2);
};
#endif
