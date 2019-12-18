#include "Section.h"
#include<string>
using namespace std;


Section::Section( string courseName, string instructorName) {
	course = courseName;
	instructor = instructorName;
	
};
//an empty section to represent an open slot in a schedule
Section::Section() {
	course = "";
	instructor = "";
};
/*
void Section::shuffleType(int type) {
	days = {};
	switch (type) {
	case(1): {
		days = { 0,2,4 };
	}
			 break;
	case(2): {
		days = { 0,2 };
	}
			 break;
	case(3): {
		days = { 1,3 };
	}
			 break;
	case(4): {
		days.push_back(0);
	}
			 break;
	case(5): {
		days.push_back(1);
	}
			 break;
	case(6): {
		days.push_back(2);
	}
			 break;
	case(7): {
		days.push_back(3);
	}
			 break;
	case(8): {
		days.push_back(4);
	}
			 break;
	default: {
		throw new InvalidTypeException();
	}
	}
};*/
string Section::getCourse() {
	return course;
};
string Section::getInstructor() {
	return instructor;
};
/*
vector<int> Section::getDays() {
	return days;
};*/