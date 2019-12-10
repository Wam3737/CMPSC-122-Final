#pragma once
#ifndef RULE_H
#define RULE_H
#include "Schedule.h"
using namespace std;
class Rule {
public:
	virtual int getFitness(Schedule schedule) = 0;
};


#endif