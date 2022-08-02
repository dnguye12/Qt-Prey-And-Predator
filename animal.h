#ifndef ANIMAL_H
#define ANIMAL_H

#include "coord.h"
#include <QString>


enum class Type {rabbit, fox, none};

class Animal
{
public:
    Animal(Type t, Coord c);
    QString toString();

    Type getType();
    void setType(Type t);

    Coord getCoord();
    void setCoord(int x, int y);
    void setCoord(Coord c);

    int getProbBirthLapin();
    int getMinFreeBirthLapin();


    int getFoodInit();
    int getFoodLapin();
    int getFoodReprod();
    int getMaxFood();
    int getProbBirthRenard();

private:
    Type type;
    Coord coord;

    int ProbBirthLapin = 30;
    int MinFreeBirthLapin = 4;


    int FoodInit = 5;
    int FoodLapin = 5;
    int FoodReprod = 8;
    int MaxFood = 10;
    int ProbBirthRenard = 5;
};

#endif // ANIMAL_H
