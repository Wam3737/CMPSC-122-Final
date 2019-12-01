#pragma once
#ifndef SCHEDULE_H
#define SCHEDULE_H
#include "Section.h"
#include<string>
#include<array>
#include<vector>
#include<time.h>
using namespace std;
class Schedule {
private:
	Section nullSec = Section();
	Section week[5][13];
	
public: 
	Schedule();
	void addSection(Section sec);
};
#endif
