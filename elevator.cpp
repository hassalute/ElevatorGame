#include "Elevator.h"
#include <iostream>

using namespace std;

void Elevator::tick(int currentTime) {
    if (currentTime % TICKS_PER_ELEVATOR_MOVE == 0 &&
        servicing == true) {
        if(targetFloor > currentFloor) {
            currentFloor += 1;
        }
        else if (targetFloor < currentFloor) {
            currentFloor -= 1;
        }
        if (currentFloor == targetFloor) {
            servicing = false;
            return;
        }
    }
}

void Elevator::serviceRequest(int floorNum) {
    targetFloor = floorNum;
    servicing = true;
}

//continued from other files
void Elevator::print(ostream &outs) {
    outs << currentFloor;
    if (!servicing){
        outs << "w";
    } else {
        outs << "s" << targetFloor;
    }
}

Elevator::Elevator() {
    currentFloor = 0;
    servicing = false;
	targetFloor = 0;
}

void Elevator::setCurrentFloor(int currentFloorIn) {
    currentFloor = currentFloorIn;
}

bool Elevator::isServicing() const {
	return servicing;
}

int Elevator::getCurrentFloor() const {
    return currentFloor;
}

int Elevator::getTargetFloor() const {
    return targetFloor;
}
