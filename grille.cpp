#include "grille.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <QDebug>

Grille::Grille()
{
    QVector<Animal*> helper;
    for(int i = 0; i < 127; i++) {
        helper.append((new Animal(Type::none, *(new Coord(0,0)))));
    }
    for(int i = 0; i < 53; i++) {
        map.append(helper);
    }
    srand(time(NULL));
    for(int i = 0; i < 53; i++) {
        for(int j = 0; j < 127; j++) {
            Animal* a = (new Animal(Type::none, *(new Coord(i,j))));
            int rate = rand() % 100 + 1;
            if(rate <= a->getProbBirthLapin()) {
                a->setType(Type::rabbit);
            }else if(rate > a->getProbBirthLapin() and rate <= a->getProbBirthLapin() + a->getProbBirthRenard()) {
                a->setType(Type::fox);
            }
            map[i][j] = a;
        }
    }
}

Animal* Grille::getAnimalAtCoord(int row, int col) {
    return map[row][col];
}

Animal* Grille::getAnimalAtCoord(Coord c) {
    return map[c.getRow()][c.getCol()];
}

void Grille::setAnimalAtCoord(Coord c, Type t) {
    map[c.getRow()][c.getCol()] = (new Animal(t, c));
}

void Grille::setAnimalAtCoord(Coord c, Animal* a) {
    map[c.getRow()][c.getCol()] = a;
}

void Grille::debug() {
    for(int i = 0; i < 53; i++) {
        QString helper = "";
        for(int j = 0; j < 127; j++) {
            Animal* a = getAnimalAtCoord(i, j);
            helper += a->toString();
            helper += " ";
        }
        helper += "\n";
        qDebug() << helper;
    }
}

QVector<Animal*> Grille::voisinVide(Coord c) {
    QVector<Coord> voisinCoord = c.getVoisin();
    QVector<Animal*> helper = {};

    foreach(Coord c, voisinCoord) {

        if(this->getAnimalAtCoord(c)->getType() == Type::none) {
            helper.append(this->getAnimalAtCoord(c));
        }
    }
    return helper;
}
QVector<Animal*> Grille::voisinRab(Coord c) {
    QVector<Coord> voisinCoord = c.getVoisin();
    QVector<Animal*> helper = {};

    foreach(Coord c, voisinCoord) {
        if(this->getAnimalAtCoord(c)->getType() == Type::rabbit) {
            helper.append(this->getAnimalAtCoord(c));
        }
    }
    return helper;
}
QVector<Animal*> Grille::voisinFox(Coord c) {
    QVector<Coord> voisinCoord = c.getVoisin();
    QVector<Animal*> helper = {};

    foreach(Coord c, voisinCoord) {
        if(this->getAnimalAtCoord(c)->getType() == Type::fox) {
            helper.append(this->getAnimalAtCoord(c));
        }
    }
    return helper;
}

void Grille::updateGrille() {
    srand(time(NULL));
    for(int i = 0; i < 53; i++) {
        for(int j = 0; j < 127; j++) {
            if(getAnimalAtCoord(i, j)->getType() == Type::rabbit) {
                Animal* a = getAnimalAtCoord(i, j);
                Coord c = a->getCoord();
                QVector<Animal*> cVide = voisinVide(c);

                if(cVide.size() > 0) {

                    int choice = rand() % (cVide.size());
                    a->setCoord(cVide[choice]->getCoord());
                    setAnimalAtCoord(c, Type::none);
                    setAnimalAtCoord(a->getCoord(), a);
                }
                else {
                    continue;
                }
            }
        }
    }
}
