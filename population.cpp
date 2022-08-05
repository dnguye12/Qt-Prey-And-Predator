#include "population.h"

#include <QDebug>

Population::Population()
{
    pop = {};
    for(int i = 0; i < 26 * 63; i++) {
        freeId.append(i);
    }
}

Animal* Population::get(int i) {
    foreach(Animal* a, pop) {
        if(a->getId() == i) {
            return a;
        }
    }
    return NULL;
}

Animal* Population::getByIndex(int idx) {
    if(idx < 0 or idx > pop.size()) {
        return NULL;
    }else {
        return pop[idx];
    }
}

int Population::size() {
    return pop.size();
}

QVector<Animal *> Population::getIds(Type t) {
    QVector<Animal*> helper = {};
    foreach(Animal* a, pop) {
        if(a->getType() == t) {
            helper.append(a);
        }
    }
    return helper;
}

int Population::reserve() {
    if(freeId.size() == 0) {
        return -1;
    }
    int idx = freeId[0];
    freeId.removeFirst();
    return idx;
}

int Population::getFreeId() {
    if(freeId.size() == 0) {
        return -1;
    }
    return freeId[0];
}

int Population::set(Type t, Coord c) {
    int idx = reserve();
    if(idx == -1) {
        qDebug() <<  "can't add more animals to the population";
        return -1;
    }
    Animal* a = new Animal(t, idx, c);
    pop.append(a);
    return idx;
}

void Population::del(int id) {
    for(int i = 0; i < pop.size(); i++) {
        if(pop[i]->getId() == id) {
            pop.removeAt(i);
            freeId.append(id);
            return;
        }
    }
}

void Population::changeCoord(int id, Coord c) {
    Animal* a = get(id);
    if(a == NULL) {
        return;
    }else {
        a->setCoord(c.getRow(), c.getCol());
    }
}

void Population::addAnimal(Coord c, Type t, int idx) {
    if(freeId.contains(idx)) {
    Animal* a = new Animal(t, idx, c);
    pop.append(a);
    freeId.removeAt(freeId.indexOf(idx));
    }

}

