#pragma once
#ifndef ONEDAY_H
#define ONEDAY_H
#include"Meeting.h"
class InvalidDayException {};
class OneDay:public Meeting {
private:
	//times will be stored in 24hr time 8am->8 9pm->21 etc
	int startTime;
	int endTime;
	//mtwrf
	/*to store whether the meeting is mwf, mw, tr, or one day a week
	for example,a mwf section would store 0, 2, 4, a tr section would store 1, 3 and so on*/
	vector<int> days;
public:
	//int day determines which day the meeting will be on 0=m 1=t 2=w and so on
	OneDay(int day, int start) {
		if (day >= 0 && day <= 4) {
			days.push_back(day);
		}
		else {
			throw new InvalidDayException;
		}
		setStart(start);
	};
	//if start is 12 it'll be set to 13 instead start can be 18 at the latest
	void setStart(int start) {
		if (start < 8) {
			startTime = 8;
		}
		else if (start < 12) {
			startTime = 9;
		}
		else if (start == 12) {
			startTime = 13;
		}
		else if (start > 18) {
			startTime = 18;
		} else{
			startTime = start;
		}
		endTime = startTime + 3;
	};

};
#endif