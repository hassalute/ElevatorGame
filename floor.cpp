#include "Floor.h"
#include <algorithm>
using namespace std;

int Floor::tick(int currentTime) {
	int countExploded = 0;
	bool exploded;
	int arr[MAX_PEOPLE_PER_FLOOR];
	int count = 0;
	for (int i = 0; i < numPeople; ++i) {
		exploded = people[i].tick(currentTime);
		if (exploded) {
			++countExploded;
			arr[count] = i;
			++count;
		}
	}
	removePeople(arr, countExploded);

    return countExploded;
}

void Floor::addPerson(Person newPerson, int request) {
	if (numPeople < MAX_PEOPLE_PER_FLOOR) {
		people[numPeople] = newPerson;
		++numPeople;
	}
	if (request > 0) {
		setHasUpRequest(true);
	}
	else {
		setHasDownRequest(true);
	}
}

void Floor::removePeople(const int indicesToRemove[MAX_PEOPLE_PER_FLOOR], int numPeopleToRemove) {
	int count = 0;
	int modIndices[MAX_PEOPLE_PER_FLOOR];
	copy(indicesToRemove, indicesToRemove + numPeopleToRemove, modIndices);
	sort(modIndices,modIndices+numPeopleToRemove);
	if (numPeople == 0) {
		return;
	}
	for (int i = 0; i < numPeopleToRemove; ++i) {
		for (int j = modIndices[i] - count; j < numPeople - count - 1; ++j) {
			people[j] = people[j + 1];
		}
		++count;
	}
	numPeople -= count;
	resetRequests();
}

void Floor::resetRequests() {
	int countUp = 0;
	int countDown = 0;
	if (numPeople == 0) {
		setHasUpRequest(false);
		setHasDownRequest(false);
		return;
	}
	for (int i = 0; i < numPeople; ++i) {
		if ((people[i].getTargetFloor() - people[i].getCurrentFloor()) > 0) {
			++countUp;
		}
		else if ((people[0].getTargetFloor() - people[0].getCurrentFloor()) < 0) {
			++countDown;
		}
	}
	if (countUp == numPeople) {
		setHasUpRequest(true);
		setHasDownRequest(false);
	}
	else if (countDown == numPeople) {
		setHasUpRequest(false);
		setHasDownRequest(true);
	}
	else {
		setHasUpRequest(true);
		setHasDownRequest(true);
	}
}

//////////////////////////////////////////////////////

Floor::Floor() {
    hasDownRequest = false;
    hasUpRequest = false;
    numPeople = 0;
}

void Floor::prettyPrintFloorLine1(ostream& outs) const {
	string up = "U";
	outs << (hasUpRequest ? up : " ") << " ";
	for (int i = 0; i < numPeople; ++i){
		outs << people[i].getAngerLevel();
		outs << ((people[i].getAngerLevel() < MAX_ANGER) ? "   " : "  ");
	}
	outs << endl;
}

void Floor::prettyPrintFloorLine2(ostream& outs) const {
	string down = "D";
	outs << (hasDownRequest ? down : " ") << " ";
	for (int i = 0; i < numPeople; ++i) {
		outs << "o   ";
	}
	outs << endl;
}

void Floor::printFloorPickupMenu(ostream& outs) const {
	cout << endl;
	outs << "Select People to Load by Index" << endl;
	outs << "All people must be going in same direction!";
	/*  O   O
	// -|- -|-
	//  |   |
	// / \ / \  */
	outs << endl << "              ";
	for (int i = 0; i < numPeople; ++i) {
		outs << " O   ";
	}
	outs << endl << "              ";
	for (int i = 0; i < numPeople; ++i) {
		outs << "-|-  ";
	}
	outs << endl << "              ";
	for (int i = 0; i < numPeople; ++i) {
		outs << " |   ";
	}
	outs << endl << "              ";
	for (int i = 0; i < numPeople; ++i) {
		outs << "/ \\  ";
	}
	outs << endl << "INDEX:        ";
	for (int i = 0; i < numPeople; ++i) {
		outs << " " << i << "   ";
	}
	outs << endl << "ANGER:        ";
	for (int i = 0; i < numPeople; ++i) {
		outs << " " << people[i].getAngerLevel() << "   ";
	}
	outs << endl << "TARGET FLOOR: ";
	for (int i = 0; i < numPeople; ++i) {
		outs << " " << people[i].getTargetFloor() << "   ";
	}
}

void Floor::setHasUpRequest(bool hasRequest) {
    hasUpRequest = hasRequest;
}

bool Floor::getHasUpRequest() const {
	return hasUpRequest;
}

void Floor::setHasDownRequest(bool hasRequest) {
    hasDownRequest = hasRequest;
}

bool Floor::getHasDownRequest() const {
	return hasDownRequest;
}

int Floor::getNumPeople() const {
    return numPeople;
}

Person Floor::getPersonByIndex(int index) const {
    return people[index];
}
