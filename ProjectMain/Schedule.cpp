#include "Schedule.h"
#include<string>
#include<array>
#include<vector>
#include<time.h>
using namespace std;
Schedule::Schedule(vector<Section> classes, vector<Meeting*> meetings) {
	this->classes = classes;
	this->meetings = meetings;
};
