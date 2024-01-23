#include "Person.h"
#include <iostream>
#include <cmath>
#include <sstream>
#include <string>
using namespace std;


//Person::Person(string inputString) : Person() {  
//    if (inputString.size() == 8) {
//        turn = (inputString.at(0) - 48) * 10;
//        turn += inputString.at(1) - 48;
//        currentFloor = inputString.at(3) - 48;
//        targetFloor = inputString.at(5) - 48;
//        angerLevel = inputString.at(7) - 48;
//    }
//    else {
//        turn = inputString.at(0) - 48;
//        currentFloor = inputString.at(2) - 48;
//        targetFloor = inputString.at(4) - 48;
//        angerLevel = inputString.at(6) - 48;
//
//   }
//}

Person::Person(string inputString) : Person() {
    char f = 'f', t = 't', a = 'a';
    stringstream tempStream(inputString);
    tempStream >> turn;
    tempStream >> f >> currentFloor;
    tempStream >> t >> targetFloor;
    tempStream >> a >> angerLevel;
}

bool Person::tick(int currentTime) {
    if (currentTime % 5 == 0) {
        ++angerLevel;
    }
    if (angerLevel == MAX_ANGER) {
        return true;
    }
    else {
        return false;
    }
}

void Person::print(ostream &outs) {    
    outs << "f" << currentFloor << "t" << targetFloor << "a" << angerLevel;
}

//////////////////////////////////////////////////////


Person::Person() {
    turn = 0;
    currentFloor = 0;
    targetFloor = 0;
    angerLevel = 0;
}

int Person::getTurn() const {
    return turn;
}

int Person::getCurrentFloor() const {    
    return currentFloor;
}

int Person::getTargetFloor() const {    
    return targetFloor;
}

int Person::getAngerLevel() const {    
    return angerLevel;
}

ostream& operator<< (ostream& outs, Person p)
{
    p.print(outs);
    return outs;
}
