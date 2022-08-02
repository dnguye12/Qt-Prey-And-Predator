#include "grille.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <QDebug>

Grille::Grille()
{
    QVector<Animal> helper;
    for(int i = 0; i < 127; i++) {
        helper.append(*(new Animal(Type::none, *(new Coord(0,0)))));
    }
    for(int i = 0; i < 53; i++) {
        map.append(helper);
    }
    srand(time(NULL));
    for(int i = 0; i < 53; i++) {
        for(int j = 0; j < 127; j++) {
            Animal a = *(new Animal(Type::none, *(new Coord(i,j))));
            int rate = rand() % 100 + 1;
            if(rate <= a.getProbBirthLapin()) {
                a.setType(Type::rabbit);
            }else if(rate > a.getProbBirthLapin() and rate <= a.getProbBirthLapin() + a.getProbBirthRenard()) {
                a.setType(Type::fox);
            }
            map[i][j] = a;
        }
    }
}

Animal Grille::getAnimalAtCoord(Coord c) {
    return map[c.getRow()][c.getCol()];
}
void Grille::setAnimalAtCoord(Coord c, Type t) {
    map[c.getRow()][c.getCol()] = *(new Animal(t, c));
}

void Grille::debug() {
    for(int i = 0; i < 53; i++) {
        QString helper = "";
        for(int j = 0; j < 127; j++) {
            Animal a = getAnimalAtCoord(*(new Coord(i, j)));
            helper += a.toString();
            helper += " ";
        }
        helper += "\n";
        qDebug() << helper;
}
}
