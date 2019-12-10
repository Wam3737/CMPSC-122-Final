#pragma once
#ifndef MEETING_H
#define MEETING_H
#include<vector>
using namespace std;
class InvalidTypeException {};
class Meeting {
private:
	//times will be stored in 24hr time 8am->8 9pm->21 etc
	int startTime;
	int endTime;
	
	/*to store whether the meeting is mwf, mw, tr, or one day a week
	for example,a mwf section would store 0, 2, 4, a tr section would store 1, 3 and so on*/
	vector<int> days;
public:
	int getStart();
	int getEnd();
	vector<int> getDays();
	//end will automatically be set depending on how long the meeting should be
	virtual void setStart(int start) =0;
	

};
#endif
