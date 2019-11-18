#pragma once
#ifndef SECTION_H
#define SECTION_H
#include<vector>
#include<string>
using namespace std;
class InvalidTypeException{};
class Section {
private:
	//course code e.g. cmpsc122.01
	string course;
	string instructor;
	/*to store whether the section is mwf, mw, tr, or one day a week
	for example,a mwf section would store 0, 2, 4, a tr section would store 1, 3 and so on*/
	vector<int> days;
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
	Section(int type, string courseName, string instructorName);
	void shuffleType(int type);

	
};
#endif