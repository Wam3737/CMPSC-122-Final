#pragma once
#ifndef SCHEDULE_H
#define SCHEDULE_H
#include "Section.h"
#include<string>
#include<array>
using namespace std;
class Schedule {
private:
	// 5 days a week, 12 1 hour chunks a day
	Section week[5][12];
public: 
	Schedule()
};
#endif
