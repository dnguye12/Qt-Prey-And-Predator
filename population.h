#ifndef POPULATION_H
#define POPULATION_H

#include "animal.h"


class Population
{
public:
    Population();

    Animal* get(int i);

    Animal* getByIndex(int idx);

    int size();

    QVector<Animal *> getIds(Type t);

    int reserve();

    int getFreeId();

    int set(Type t, Coord c);

    void addAnimal(Coord c, Type t, int idx);

    void del(int id);

    void changeCoord(int id, Coord c);



private:
    QVector<Animal *> pop;
    QVector<int> freeId;
};

#endif // POPULATION_H
