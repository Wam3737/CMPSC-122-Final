#pragma once
#ifndef TWODAYS_H
#define TWODAYS_H
#include "Meeting.h"
class TwoDays : public Meeting {
private:
	//times will be stored in 24hr time 8am->8 9pm->21 etc
	int startTime;
	int endTime;
	//mwf
	vector<int> days;
public:
	//Type 1: mw Type 2: tr if type is invalid, Type 1 is default. Start times will be mapped to the closest allowed start time(favors early times)
	TwoDays(int type, int start) {
		if (type == 2) {
			days = { 1,3 };
		}
		else {
			days = { 0,2 };
		}
		setStart(start);

	};
	void setStart(int start) {
		
		if (start < 10) {
			startTime = 8;
		}
		else if (start <= 12) {
			startTime = 10;
		}
		else if (start <= 14) {
			startTime = 13;
		}
		else if (start <= 16) {
			startTime = 15;
		}
		else if (start <= 18) {
			startTime = 17;
		}
		else {
			startTime = 19;
		}
		endTime = startTime + 2;

	}
};
#endif