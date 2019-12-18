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
	
	Section(string courseName, string instructorName);
	//creates an empty section. empty sections indicate a free slot in the schedule
	Section();
	
	string getCourse();
	
	string getInstructor();
	
	
};
#endif