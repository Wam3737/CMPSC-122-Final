#pragma once
#ifndef SECTION_H
#define SECTION_H
#include<vector>
#include<string>
using namespace std;
class Section {
private:
	/*time will be stored in minutes, classes may begin as early as 8am (represented as 0) and classes can go no later than 9pm(represented as 780)*/
	int start;
	int end;
	const int EARLIEST_START;
	const int LATEST_END;
	const int COMMON_HR_START;
	const int COMMON_HR_END;
	//to store whether the section is mwf, mw, tr, or one day a week
	vector<string> days;
public:
	/*Type 1: mwf
	  Type 2: mw
	  Type 3: tr
	  Type 4: one day a week*/
	Section(int type, int startTime, int endTime);
	void setStart(int startTime);
	
};
#endif