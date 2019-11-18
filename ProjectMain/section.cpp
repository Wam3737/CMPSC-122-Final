#include "Section.h"
#include<string>
using namespace std;

/*    Type 1: mwf
	  Type 2: mw
	  Type 3: tr
	  Type 4: m
	  Type 5: tues
	  Type 6: w
	  Type 7: thurs
	  Type 8: f
	  using numbers to define this will make generating random schedules easier*/
Section::Section(int type, string courseName, string instructorName) {
	course = courseName;
	instructor = instructorName;
	switch (type) {
	case(1): {
		days = {0,2,4};
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
};

void Section::shuffleType(int type) {
	days = {};

};