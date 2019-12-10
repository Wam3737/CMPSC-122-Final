#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<time.h>
#include"Meeting.h"
#include"OneDay.h"
#include"TwoDays.h"
#include"ThreeDays.h"
#include"Schedule.h"
#include"section.h"

using namespace std;
int main() {
	const int POPULATION_SIZE = 100;
	const int ELITE_SIZE = 20;
	const int MAX_ITERATIONS = 1000;
	const int STABLE_ITERATIONS = 5;
	
	ifstream in;
	in.open("sections.txt");
	vector<Section> sections;
	string code;
	string instructor;
	while (in >> code >> instructor) {
		cout << code;
		sections.push_back(Section(code, instructor));
		
	}
	in.close();
	int x = 0;
	srand(time(NULL));
	vector<Schedule> population;
	for (int i = 0; i < POPULATION_SIZE; ++i) {
		//creating a copy of the section list to pass to the schedule constructor
		vector<Section> classes = sections;
		vector<Meeting*> meetings;
		for (int j = 0; j < sections.size(); ++j) {
			int meetingType = 1; //rand() % 3 + 1;
			cout << meetingType;
			//determines start time
			int time = rand() % 13 + 8;
			cout << time;
			switch (meetingType) {
			case 1: {
				//decides which day of the week
				int day = rand() & 5;
				++x;
				Meeting *m = new OneDay(day, time);
				meetings.push_back(m);
				cout << "REE";
			}
				break;
			
			
			};
		}
		
	}
	
	system("pause");
	return 0;
};
