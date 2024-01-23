#include <cmath>
#include <sstream>
#include <stdio.h>      
#include <stdlib.h>
#include "Move.h"

using namespace std;

Move::Move(string commandString) : Move() {
    if (commandString == "") {
        isPass = true;
    }
    else if(commandString == "q" || commandString == "Q") {
        isQuit = true;
    }
    else if(commandString == "s" || commandString == "S") {
        isSave = true;
    }
    else if (commandString.size() == 4) {
        elevatorId = commandString.at(1) - 48;
        targetFloor = commandString.at(3) - 48;
    }
    else {
        elevatorId = commandString.at(1) - 48;
        isPickup = true;
    }
    
}

bool Move::isValidMove(Elevator elevators[NUM_ELEVATORS]) const {
    if (isPassMove() || isQuitMove() || isSaveMove()) {
        return true;
    }
    else if (0 <= elevatorId 
        && elevatorId < NUM_ELEVATORS
        && !elevators[elevatorId].isServicing()) {
        if (isPickupMove()) {
            return true;
        }
        else if (0 <= targetFloor
            && targetFloor < NUM_FLOORS
            && targetFloor != elevators[elevatorId].getCurrentFloor()) {
            return true;
        }
        else {
            return false;
        }
    }
    else {
        return false;
    }
}

void Move::setPeopleToPickup(const string& pickupList, const int currentFloor, const Floor& pickupFloor) {
    numPeopleToPickup = 0;
    totalSatisfaction = 0;
    targetFloor = currentFloor;
    Floor copyPickupFloor = pickupFloor;
    for (int i = 0; i < pickupList.size(); ++i) {
        int personIndice = pickupList.at(i) - 48;
        peopleToPickup[i] = pickupList.at(i) - 48;
        totalSatisfaction += (MAX_ANGER - copyPickupFloor.getPersonByIndex(personIndice).getAngerLevel());
        ++numPeopleToPickup;

        if (abs(targetFloor - currentFloor) < abs(copyPickupFloor.getPersonByIndex(personIndice).getTargetFloor() - currentFloor)) {
            targetFloor = copyPickupFloor.getPersonByIndex(personIndice).getTargetFloor();
        }
    }
}

//////////////////////////////////////////////////////


Move::Move() {
    elevatorId = -1;
    targetFloor = -1;
    numPeopleToPickup = 0;
    totalSatisfaction = 0;
	isPass = false;
    isPickup = false;
    isSave = false;
    isQuit = false;
}

bool Move::isPickupMove() const {
    return isPickup;
}

bool Move::isPassMove() const {
	return isPass;
}

bool Move::isSaveMove() const {
	return isSave;
}

bool Move::isQuitMove() const {
	return isQuit;
}

int Move::getElevatorId() const {
    return elevatorId;
}

int Move::getTargetFloor() const {
    return targetFloor;
}

int Move::getNumPeopleToPickup() const {
    return numPeopleToPickup;
}

int Move::getTotalSatisfaction() const {
    return totalSatisfaction;
}

void Move::setTargetFloor(int inTargetFloor) {
    targetFloor = inTargetFloor;
}

void Move::copyListOfPeopleToPickup(int newList[MAX_PEOPLE_PER_FLOOR]) const {
    for (int i = 0; i < numPeopleToPickup; ++i) {
        newList[i] = peopleToPickup[i];
    }
}
