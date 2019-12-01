#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include"Meeting.h"
#include"OneDay.h"
#include"TwoDays.h"
#include"ThreeDays.h"
#include"Schedule.h"
#include"section.h"
using namespace std;
int main() {
	ifstream in;
	in.open("sections.txt");
	vector<Section> sections;
	string code;
	string instructor;
	while (in >> code >> instructor) {
		sections.push_back(Section(code, instructor));
		cout << code << " " << instructor << endl;
	}
	in.close();
	system("pause");
	return 0;
}