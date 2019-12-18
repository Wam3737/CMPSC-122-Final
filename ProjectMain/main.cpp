#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<time.h>
#include"Schedule.h"
#include"Section.h"
#include"Optimizer.h"
#include"Rule.h"
#include<array>
#include<set>
#include<map>
#include<random>
using namespace std;
int main() {
	const int POPULATION_SIZE = 100;
	const int ELITE_SIZE = 10;
	const int MAX_ITERATIONS = 1000;
	const int STABLE_ITERATIONS= 5;
	ifstream in;
	in.open("sections.txt");
	vector<Section> sections;
	string code;
	string instructor;
	
	while (in >> code >> instructor) {
		
		sections.push_back(Section(code, instructor));
		
	}
	in.close();
	set<string> instructors;
	for (int i = 0; i < sections.size(); ++i) {
		instructors.insert(sections.at(i).getInstructor());
	}
	vector<Schedule> population;
	Optimizer test = Optimizer();
	int iterations = 0;
	int stableIterations = 0;
	random_device r;
	for (int i = 0; i < POPULATION_SIZE; ++i) {
		//add a random schedule to the population
		population.push_back(Schedule(sections));
		test.sortByFittest(population);

	}
	
	cout << "Initial Fitness: " << population[0].getFitness() << endl;
	while (iterations < MAX_ITERATIONS && stableIterations < STABLE_ITERATIONS) {
		vector<Schedule> nextGeneration;
		++iterations;


		for (int i = 0; i < POPULATION_SIZE / 2; ++i) {
			Schedule parent1 = population.at(rand() % ELITE_SIZE);
			Schedule parent2 = population.at(rand() % ELITE_SIZE);
			//a random schedule is created, and if it's better than one of the parents it will take the place of that parent during corssover (a mutation of some sort)
			Schedule randomParent(sections);
			if (randomParent < parent2) {
				//keeping the splits closer to the middle gave better results on average than random splits
				vector<Schedule> children = parent1.spliceSchedulesV2(randomParent, r() % (instructors.size() / 2) + (instructors.size() / 4));

				for (int j = 0; j < children.size(); ++j) {
					nextGeneration.push_back(children.at(j));
				}

			}
			else if (randomParent < parent1) {
				//keeping the splits closer to the middle gave better results on average than random splits
				vector<Schedule> children = parent2.spliceSchedulesV2(randomParent, r() % (instructors.size() / 2) + (instructors.size() / 4));

				for (int j = 0; j < children.size(); ++j) {
					nextGeneration.push_back(children.at(j));
				}
			}
			else {
				//keeping the splits closer to the middle gave better results on average than random splits
				vector<Schedule> children = parent1.spliceSchedulesV2(parent2, r() % (instructors.size()/2) + (instructors.size() /4));

				for (int j = 0; j < children.size(); ++j) {
					nextGeneration.push_back(children.at(j));
				}
			}
		}
		test.sortByFittest(nextGeneration);
		//if there's no improvment in fitness, stableIterations is incremented
		if (population.at(0).getFitness() < nextGeneration.at(0).getFitness() || population.at(0).getFitness() == nextGeneration.at(0).getFitness()) {
			++stableIterations;
		}
		else {
			stableIterations = 0;
		}

		int parentFitness = 0;
		int childFitness = -250;
		//if the next generation's elite is significantly worse on average, we keep the parent generation
		for (int i = 0; i < ELITE_SIZE; ++i) {
			parentFitness += population.at(i).getFitness();
			childFitness += nextGeneration.at(i).getFitness();
		}
		if (childFitness<parentFitness) {
		population = nextGeneration;
		}
		
		
	}
	
	

	
	
	population[0].displaySchedule();
	cout << endl<< "Final Fitness: " << population[0].getFitness() <<endl;
	system("pause");
	return 0;
};
