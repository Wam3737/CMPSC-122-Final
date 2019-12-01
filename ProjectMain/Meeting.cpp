#include "Meeting.h"
using namespace std;
int Meeting::getStart() {
	return startTime;
}
int Meeting::getEnd() {
	return endTime;
};
vector<int> Meeting::getDays() {
	return days;
};