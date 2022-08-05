#include "animal.h"
#include <QDebug>

Animal::Animal(Type t, int id, Coord c) {
    age = 0;
    type = t;
    coord = c;
    Id = id;
    FoodInit = 5;
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

int Animal::getId() {
    return Id;
}

void Animal::setId(int i) {
    Id = i ;
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
void Animal::setFoodInit(int f) {
    FoodInit = f;
    if(FoodInit > MaxFood) {
        FoodInit = MaxFood;
        return;
    }
    if(FoodInit < 0) {
        FoodInit = 0;
        return;
    }
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

int Animal::getAge() {
    return age;
}
void Animal::setAge(int a) {
    age = a;
}

int Animal::getMaxAge() {
    return maxAge;
}
