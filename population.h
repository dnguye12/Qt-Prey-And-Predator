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

    int set(Type t, Coord c);

    void del(int id);

    void changeCoord(int id, Coord c);



private:
    QVector<Animal *> pop;
    QVector<int> freeId;
};

#endif // POPULATION_H
