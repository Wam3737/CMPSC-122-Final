#include "Schedule.h"
#include<string>
#include<array>
#include<vector>
#include<time.h>
using namespace std;
Schedule::Schedule(){
	//initialize array to empty sections
	for (int i = 0; i < 5; ++i) {
		for (int j = 0; j < 13; ++j) {
			if (j != 5) {
				week[i][j] = nullSec;
			}
			else {
				week[i][j] = Section(1, "Common Hour", "");
			}
		}
	}
	/*//monday through friday
	week = new Section**[5];
	for (int i = 0; i < 5; ++i) {
		//12 time slots, starting at 8 and ending at 9
		week[i] = new Section*[12];
		//fill the array with empty sections
		for (int j = 0; j < 12; ++j) {
			week[i][j] =  new Section();
		}
	}*/

	
	
};
void Schedule::addSection(Section sec) {
	vector<int> days = sec.getDays();
	//determines if a section is a 1, 2, or 3 hour section
	int size = days.size();
	//index of an available time slot which fits the given type
	
	
	switch (size) {
	//3 hr section
	case(1):
		//looping through days
		for (int i = 0; i < 5; ++i) {
			//looping through hours
			for (int j = 0; j < 10; ++j) {
				if (week[i][j].getCourse() == "" && week[i][j+1].getCourse() == "" && week[i][j+2].getCourse() == "") {
					week[i][j] = sec;
					week[i][j+1] = sec;
					week[i][j+2] = sec;
					//exit loop if a time slot has been found
					j = 10;
					i = 5;
				}
			}
		}
		break;
	case(2):


			break;
	case(3):
			break;

	}
	/*for (int i = 0; i < days.size(); ++i) {
		for (int j = 0; j < 12; ++j) {
			//index of common hour is 4
			if (j != 4) {

			}
		}
	};*/
	

};
