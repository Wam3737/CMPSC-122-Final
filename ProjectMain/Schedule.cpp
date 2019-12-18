#include "Schedule.h"
#include<string>
#include<array>
#include<vector>
#include<time.h>
#include<random>
using namespace std;
//given a class list, creates a random schedule of meetings for said list
Schedule::Schedule(vector<Section> classes) {
	this->classes = classes;
	for (int Q = 0; Q < classes.size(); ++Q) {

		if (profSched.find(classes.at(Q).getInstructor()) == profSched.end()) {
			array<array<Section, 13>, 5> s;
			for (int i = 0; i < 5; ++i) {
				for (int j = 0; j < 13; ++j) {
					if (j != 4) {
						s[i][j] = Section();
					}
					else {
						s[i][j] = Section("COMMON HOUR", "COMMON HOUR");
					}
				}
			}
			profSched.insert({ classes.at(Q).getInstructor(), s });
		}
	}
	//noticed a lot of repetition when using rand() so switched to usign a random_device instead
	random_device r;
	//keeps track of taken starting times
	bool takenSlot[5][13];
	for (int i = 0; i < 5; ++i) {
		for (int j = 0; j < 13; ++j) {
			if (j == 4) {
				takenSlot[i][j] = true;
			}
			else {
				takenSlot[i][j] = false;
			}
		}
	}
	for (int Q = 0; Q < classes.size(); ++Q) {
		auto it = profSched.find(classes[Q].getInstructor());
		
			int species = r() % 5 + 1;
			bool timeFound = false;
			do {
				switch (species) {
				case(1): {
					//determines day
					int days = r() % 5;
					int time = r() % 11;
					bool roomAvailable = !takenSlot[days][time];
					bool validSlot = it->second[days][time].getCourse() == "" && it->second[days][time + 1].getCourse() == "" && it->second[days][time + 2].getCourse() == "";
					int stopLoop = 0;
					while ((!roomAvailable || !validSlot) && stopLoop < 15) {

						days = r() % 5;
						time = r() % 11;
						roomAvailable = !takenSlot[days][time];
						validSlot = it->second[days][time].getCourse() == "" && it->second[days][time + 1].getCourse() == "" && it->second[days][time + 2].getCourse() == "";
						++stopLoop;
					}
					if (validSlot && roomAvailable) {
						takenSlot[days][time] = true;
						
						it->second[days][time] = classes.at(Q);
						it->second[days][time + 1] = classes.at(Q);
						it->second[days][time + 2] = classes.at(Q);
					
						timeFound = true;
					}

				}break;
				case(2): {
					//determines mw or tr
					int type = r() % 2;
					int days[2];
					if (type == 0) {
						days[0] = 0;
						days[1] = 2;
					}
					else {
						days[0] = 1;
						days[1] = 3;
					}
					
					int time = r() % 11;
					bool roomAvailable = !takenSlot[days[0]][time]  && !takenSlot[days[1]][time];
					int stopLoop = 0;
					bool validSlot = it->second[days[0]][time].getCourse() == "" && it->second[days[1]][time].getCourse() == "" && it->second[days[0]][time + 1].getCourse() == "" && it->second[days[1]][time + 1].getCourse() == "";
					while ( ( !roomAvailable || !validSlot) && stopLoop < 15) {
						time = r() % 11;
						if (time != 0 || time != 2 || time == 4 || time != 5 || time != 7 || time != 9 || time != 11) {
							++time;
						}
						roomAvailable = !takenSlot[days[0]][time] && !takenSlot[days[1]][time];
						validSlot = it->second[days[0]][time].getCourse() == "" && it->second[days[1]][time].getCourse() == "" && it->second[days[0]][time + 1].getCourse() == "" && it->second[days[1]][time + 1].getCourse() == "";
					
						++stopLoop;
					}
					if (validSlot && roomAvailable) {
						timeFound = true;
						
						for (int i = 0; i < 2; ++i) {
							takenSlot[days[i]][time] = true;
							
							it->second[days[i]][time] = classes.at(Q);
							it->second[days[i]][time + 1] = classes.at(Q);
						}
					}



				}break;
				case(3): {
					int days[3] = { 0,2,4 };

					int time = r() % 13;
					bool validSlot = it->second[days[0]][time].getCourse() == "" && it->second[days[1]][time].getCourse() == "" && it->second[days[2]][time].getCourse() == "";
					int stopLoop = 0;
					bool roomAvailable = !takenSlot[days[0]][time] && !takenSlot[days[1]][time] && !takenSlot[days[2]][time];
					while ((!roomAvailable || !validSlot) && stopLoop < 15) {

						time = r() % 13;
						roomAvailable =!takenSlot[days[0]][time] && !takenSlot[days[1]][time] && !takenSlot[days[2]][time];
						validSlot = it->second[days[0]][time].getCourse() == "" && it->second[days[1]][time].getCourse() == "" && it->second[days[2]][time].getCourse() == "";
						++stopLoop;
					}
					if (validSlot ) {
						
						for (int i = 0; i < 3; ++i) {
							takenSlot[days[i]][time] = true;
							it->second[days[i]][time] = classes.at(Q);
						}
						timeFound = true;
					}
				} break;

				}
				species = r() % 3 + 1;
			} while (!timeFound);
			

		}
	};
 
Schedule::Schedule(map <string, array<array<Section, 13>, 5>> profSched, vector<Section> classes) {
	this->profSched = profSched;
	this->classes = classes;
};

map <string, array<array<Section, 13>, 5>> Schedule::getData() {
	return profSched;
}
void Schedule::displaySchedule() {
	map<int, string> days;
	days.insert({ 0, "Monday" });
	days.insert({ 1, "Tuesday" });
	days.insert({ 2, "Wednesday" });
	days.insert({ 3, "Thursday" });
	days.insert({ 4, "Friday" });
	map<int, pair<string,string>> time;
	time.insert({ 0,{"8am", "9am"} });
	time.insert({ 1,{"9am", "10am"} });
	time.insert({ 2,{"10am", "11am"} });
	time.insert({ 3,{"11am", "12pm"} });
	time.insert({ 4,{"12pm", "1pm"} });
	time.insert({ 5,{"1pm", "2pm"} });
	time.insert({ 6,{"2pm", "3pm"} });
	time.insert({ 7,{"3pm", "4pm"} });
	time.insert({ 8,{"4pm", "5pm"} });
	time.insert({ 9,{"5pm", "6pm"} });
	time.insert({ 10,{"6pm", "7pm"} });
	time.insert({ 11,{"7pm", "8pm"} });
	time.insert({ 12,{"8pm", "9pm"} });


	for (auto it = profSched.begin(); it != profSched.end(); ++it) {
		cout << endl << endl;
		 cout<< (it->first + "'s Schedule");

		
		
		for (int i = 0; i < 5; ++i) {
			if (i != 0) {
				cout << endl;
			}
			cout <<endl<< days[i];
			
			for (int j = 0; j < 13; ++j) {
				if (it->second[i][j].getCourse() != "") {
					cout << endl << time[j].first << " - " << time[j].second << " ";
					cout << it->second[i][j].getCourse();
				}
				
			}
		}
		
		
	}


};
vector<Schedule> Schedule::spliceSchedules(Schedule s2, int day, int time) {
	map<string, array<array<Section,13>,5>> s1Data = this->getData();
	map <string, array<array <Section, 13>, 5>> s2Data = s2.getData();
	map<string, array<array<Section, 13>, 5>> child1;
	map<string, array<array<Section, 13>, 5>> child2;
	auto it1 = s1Data.begin();
	auto it2 = s2Data.begin();
	while (it1 != s1Data.end() && it2 != s2Data.end()) {
		
				array<array<Section, 13>, 5> arr1;
				array<array<Section, 13>, 5> arr2;
				for (int i = 0; i < day; ++i) {
					for (int j = 0; j < time; ++j) {
						arr1[i][j] = it1->second[i][j];
						arr2[i][j] = it2->second[i][j];
					}
				}
				for (int i = day; i < 5; ++i) {
					for (int j = time; j < 13; ++j) {
						arr1[i][j] = it2->second[i][j];
						arr2[i][j] = it1->second[i][j];
					}
				}
				child1.insert({ it1->first, arr1 });
				child2.insert({ it2->first, arr2 });
				++it1;
				++it2;
		}
	vector<Schedule> children;
	children.push_back(Schedule(child1,this->classes));
	children.push_back(Schedule(child2, this->classes));
	return children;
};
vector<Schedule> Schedule::spliceSchedulesV2(Schedule s2, int profSplit) {
	map<string, array<array<Section, 13>, 5>> s1Data = this->getData();
	map <string, array<array <Section, 13>, 5>> s2Data = s2.getData();
	map<string, array<array<Section, 13>, 5>> child1;
	map<string, array<array<Section, 13>, 5>> child2;
	auto it1 = s1Data.begin();
	auto it2 = s2Data.begin();
	int profCount = 0;
	while (it1 != s1Data.end() && it2 != s2Data.end()) {
		array<array<Section, 13>, 5> arr1;
		array<array<Section, 13>, 5> arr2;
		if (profCount < profSplit) {
			arr1 = it1->second;
			arr2 = it2->second;
		}
		else {
			arr1 = it2->second;
			arr2 = it1->second;
		}
		child1.insert({ it1->first, arr1 });
		child2.insert({ it2->first, arr2 });
		++profCount;
		++it1;
		++it2;
	}

	vector<Schedule> children;
	children.push_back(Schedule(child1, this->classes));
	children.push_back(Schedule(child2, this->classes));
	return children;
};
int Schedule::getFitness() {
	return fitness;
}
//returns the list of classes associated with the schedule
vector<Section> Schedule::getClasses() {
	return classes;
};
bool Schedule::operator<(Schedule s) {
		bool lessThan = false;
	if (this->fitness < s.fitness) {
		lessThan = true;
 }
	return lessThan;
};