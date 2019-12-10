#pragma once
#ifndef SECTION_H
#define SECTION_H
#include<vector>
#include<string>
using namespace std;

class Section {
private:
	//course code e.g. cmpsc122.01
	string course;
	string instructor;
	
public:
	/*Type 1: mwf
	  Type 2: mw
	  Type 3: tr
	  Type 4: m
	  Type 5: tues
	  Type 6: w
	  Type 7: thurs
	  Type 8: f
	  using numbers to define this will make generating random schedules easier*/
	Section(string courseName, string instructorName);
	//creates an empty section. empty sections indicate a free slot in the schedule
	Section();
	
	string getCourse();
	
	string getInstructor();
	/*
	vector<int> getDays();
	void shuffleType(int type);
	*/
	
};
#endif