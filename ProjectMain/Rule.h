#pragma once
#ifndef RULE_H
#define RULE_H
#include "Schedule.h"
#include "Meeting.h"
#include<vector>
#include<set>
#include<map>
#include<string>
using namespace std;
class Rule {
public:
	virtual int getFitness(Schedule schedule) = 0;
};
//adds 3000 if any classes meet for less than 3 hours or more than 4 hours a week
class CreditDisparity : public Rule {
	int getFitness(Schedule schedule) {
		
		bool creditsOff = false;
		vector<Section> classes = schedule.getClasses();
		
		vector<int> creditCount(classes.size());
		map <string, array<array<Section, 13>, 5>> profSched = schedule.getData();
		for (auto it = profSched.begin(); it != profSched.end(); ++it) {
			for (int i = 0; i < 5; ++i) {
				for (int j = 0; j < 13; ++j) {
					for (int k = 0; k < classes.size(); ++k) {
						if (classes.at(k).getCourse() == it->second[i][j].getCourse()) {
							++(creditCount.at(k));
						}
				}
				}
			}
		}
		int fitness = 0;
		for (int i = 0; i < creditCount.size(); ++i) {
			if (creditCount.at(i)<3 || creditCount.at(i)>4) {
				fitness += 3000;
				
			}
		}
		
		
		return fitness;
	};
};
//adds 100 for every hour past 9 and instructor must be on campus
class LongDays : public Rule {
	int getFitness(Schedule schedule) {
		int extraHours=0;
		map <string, array<array<Section, 13>, 5>> profSched = schedule.getData();
		for (auto it = profSched.begin(); it != profSched.end(); ++it) {
			for (int i = 0; i < 5; ++i) {
				int early = INT_MAX;
				int late = -1;
				
				for (int j = 0; j < 12; ++j) {
					if (it->second[i][j].getCourse() != "") {
						if (j < early) {
							early = j;
						}
						if (j > late) {
							late = j;
						}
				}
				}
				//prevents triggering on a day an instructor is not on campus or not there for at least 9 hours
				if (late != -1 && late-early>=8) {
					//a difference of 0 indicates 1 hour on campus
					extraHours = late - early + 1 - 9;

				}
			}
		}//end of map loop
		return extraHours*100;
	}
};
//adds a 100 for every hour before 11am an instructor has to be on campus after having classon or after 6pm the preceding day
class LateNightsEarlyMornings : public Rule {
	int getFitness(Schedule schedule) {
		int earlyHours=0;
		map <string, array<array<Section, 13>, 5>> profSched = schedule.getData();
		for (auto it = profSched.begin(); it != profSched.end(); ++it) {
			//only have to check up to thursday
			for (int i = 0; i < 4; ++i) {
				
				bool hasNightClass = false;
				//only have to check starting at 6
				for (int j = 9; j < 13; ++j) {
					if (it->second[i][j].getCourse() != "") {
						hasNightClass = true;
						j = 13;
					}
					
				}
				if(hasNightClass){
					if (it->second[i + 1][0].getCourse() != "") {
						earlyHours += 3;
					}
					else if (it->second[i + 1][1].getCourse() != "") {
						earlyHours += 2;
					}
					else if (it->second[i + 1][2].getCourse() != "") {
						earlyHours += 1;
					}
				}
			}




		}//end of map loop
		return earlyHours*100;
	}
};
//adds 50 for every day more than 2 that an instructor has evening class
class TooManyNights: public Rule {
	int getFitness(Schedule schedule) {
		int weight=0;
		map <string, array<array<Section, 13>, 5>> profSched = schedule.getData();
		for (auto it = profSched.begin(); it != profSched.end(); ++it) {
			int count = 0;
			for (int i = 0; i < 5; ++i) {
				bool hasNightClass = false;
				//only have to check starting at 6
				for (int j = 9; j < 13; ++j) {
					if (it->second[i][j].getCourse() != "") {
						++count;
						hasNightClass = true;
						j = 12;
					}

				}
			}
			if (count > 2) {
				weight += (count - 2);

			}
		
		}//end of map loop


		return weight*50;
	};

};
//adds 50 for every instance of an instructor teaching back to back classes
class BackToBack : public Rule {
	int getFitness(Schedule schedule) {
		int count = 0;
		map <string, array<array<Section, 13>, 5>> profSched = schedule.getData();
		for (auto it = profSched.begin(); it != profSched.end(); ++it) {
			for (int i = 0; i < 5; ++i) {
			
				for (int j = 0; j < 12; ++j) {
					if (it->second[i][j].getCourse() != "" && it->second[i][j+1].getCourse() != "") {
						if (it->second[i][j].getCourse() != it->second[i][j + 1].getCourse()) {
							++count;
						}
					}
				}
			}
		}//end of map loop
		return count*50;
	};

};
//adds 50 for every instance of an instructor teaching class directly before and after common hour
class CrowdedCommon : public Rule {
	int getFitness(Schedule schedule) {
		int count=0;
		map <string, array<array<Section, 13>, 5>> profSched = schedule.getData();
		for (auto it = profSched.begin(); it != profSched.end(); ++it) {
			for (int i = 0; i < 5; ++i) {
				if (it->second[i][3].getCourse() != "" && it->second[i][5].getCourse() != "") {
					++count;
				}
			}

		}//end of map loop
		return count * 50;
	};
};
//adds 50 for every instance of an instructor teaching more than 3 classes in a day
class TooManyClasses :public Rule {
	int getFitness(Schedule schedule) {
		int count=0;
		map <string, array<array<Section, 13>, 5>> profSched = schedule.getData();
		for (auto it = profSched.begin(); it != profSched.end(); ++it) {
			for (int i = 0; i < 5; ++i) {
				set<string> classes;
				for (int j = 0; j < 12; ++j) {
					if (it->second[i][j].getCourse() != "") {
						classes.insert(it->second[i][j].getCourse());
					}
				}
				if (classes.size() > 3) {
					++count;
				}
			}

		}//end of map loop
		return count*50;
	};
};
//adds 1000 for every instance of an instructor teaching 2 or more 3 hour sections in a day
class LongClasses : public Rule {
	int getFitness(Schedule schedule) {
		int count=0;
		map <string, array<array<Section, 13>, 5>> profSched = schedule.getData();
		for (auto it = profSched.begin(); it != profSched.end(); ++it) {
			for (int i = 0; i < 5; ++i) {
				bool thrc1 = false;
				for (int j = 0; j < 11; ++j) {
					
					if (it->second[i][j].getCourse() == it->second[i][j + 2].getCourse() && it->second[i][j].getCourse() != "") {
						if (!thrc1) {
							thrc1 = true;
						}
						else {
							++count;
							j = 11;
						}

					}

				}
			}
		}//end of map loop
		return count*1000;
	};
};

#endif