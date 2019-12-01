#pragma once
#ifndef THREEDAYS_H
#define THREEDAYS_H
#include "Meeting.h"
#include <time.h>
class ThreeDays: public Meeting {
private:
	//times will be stored in 24hr time 8am->8 9pm->21 etc
	int startTime;
	int endTime;
	//mwf
	vector<int> days = { 0,2,4 };
public:
	//if start is 12, it'll be set to 11 or 13 randomly rather than throwing an exception
	ThreeDays(int start) {
		setStart(start);
	};
	//if start is 12, it'll be set to 11 or 13 randomly rather than throwing an exception
	void setStart(int start) {
		if (start != 12) {
			startTime = start;
			endTime = start + 1;
		}
		else {
			srand(time(NULL));
			int x = rand() % 100;
			if (x % 2 == 0) {
				startTime = 11;
				endTime = 12;
			}
			else {
				startTime = 13;
				endTime = 14;
			}
		}
	};


};
#endif