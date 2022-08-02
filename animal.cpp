#include "animal.h"
#include <QDebug>

Animal::Animal(Type t, Coord c) {
    type = t;
    coord = c;
}

QString Animal::toString() {
    if(type == Type::fox) {
        return "F";
    }else if(type == Type::rabbit) {
        return "R";
    }else {
        return " ";
    }
}

Type Animal::getType() {
    return type;
}

void Animal::setType(Type t) {
    type = t;
}

Coord Animal::getCoord() {
    return coord;
}

void Animal::setCoord(int x, int y) {
    coord.setCol(y);
    coord.setRow(x);
}

void Animal::setCoord(Coord c) {
       coord =  c;
}

//rabbit functions
int Animal::getProbBirthLapin() {
    return ProbBirthLapin;
}
int Animal::getMinFreeBirthLapin() {
    return MinFreeBirthLapin;
}

//fox functions
int Animal::getFoodInit() {
    return FoodInit;
}
int Animal::getFoodLapin() {
    return FoodLapin;
}
int Animal::getFoodReprod() {
    return FoodReprod;
}
int Animal::getMaxFood() {
    return MaxFood;
}
int Animal::getProbBirthRenard() {
    return ProbBirthRenard;
}
