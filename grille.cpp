#include "grille.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <QDebug>

Grille::Grille()  {
    QVector<Animal*> helper;
    for(int i = 0; i < 63; i++) {
        helper.append((new Animal(Type::none, -1, *(new Coord(0,0)))));
    }
    for(int i = 0; i < 26; i++) {
        map.append(helper);
    }
    srand(time(NULL));
    for(int i = 0; i < 26; i++) {
        for(int j = 0; j < 63; j++) {
            Animal* a = (new Animal(Type::none, -1, *(new Coord(i,j))));
            int rate = rand() % 100 + 1;
            if(rate <= a->getProbBirthLapin() + a->getProbBirthRenard()) {
                if(pop.size() < 26 * 63) {
                    if(rate <= a->getProbBirthLapin()) {
                        a->setType(Type::rabbit);

                    }else if(rate > a->getProbBirthLapin() and rate <= a->getProbBirthLapin() + a->getProbBirthRenard()) {
                        a->setType(Type::fox);
                    }
                    int idx = pop.set(a->getType(), a->getCoord());
                    a->setId(idx);
                }
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

void Grille::setAnimalAtCoord(Coord c, Type t, int idx) {
    map[c.getRow()][c.getCol()] = (new Animal(t,idx,  c));
    pop.addAnimal(c,t, idx);
}

void Grille::setAnimalAtCoord(Coord c, Animal* a) {
    map[c.getRow()][c.getCol()] = a;
    pop.addAnimal(c, a->getType(), a->getId());
}

Population Grille::getPop() {
    return pop;
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

QPair<int,int> Grille::popCount() {
    int countRab = 0;
    int countFox = 0;
    for(int i = 0; i < pop.size(); i++) {
        if(pop.getByIndex(i)->getType() == Type::fox) {
            countFox++;
        }else if (pop.getByIndex(i)->getType() == Type::rabbit) {
            countRab++;
        }
    }
    QPair<int,int> helper;
    helper.first = countRab;
    helper.second = countFox;
    return helper;
}


void Grille::updateGrille() {
    srand(time(NULL));
    QVector<int> moved = {};
    for(int i = 0; i < pop.size(); i++) {
        Animal* a = pop.getByIndex(i);
        if(a->getType() == Type::rabbit and not moved.contains(a->getId())) {
            a->setAge(a->getAge() + 1);
            Coord c = a->getCoord();
            int id = a->getId();
            moved.append(id);
            QVector<Animal*> cVide = voisinVide(c);
            QVector<Animal*> rVide = voisinRab(c);
            if(cVide.size() > 0) {
                int choice = rand() % (cVide.size());
                pop.changeCoord(id, cVide[choice]->getCoord());
                setAnimalAtCoord(cVide[choice]->getCoord(), a);
                if(rVide.size() >= a->getMinFreeBirthLapin()) {
                    int choiceRabbit = rand() % 100 + 1;
                    if(choiceRabbit <= a->getProbBirthLapin()) {
                        int nId = pop.getFreeId();
                        moved.append(nId);
                        setAnimalAtCoord(c, Type::rabbit, nId);
                    }else {
                        setAnimalAtCoord(c, Type::none, -1);
                    }

                }else {
                    setAnimalAtCoord(c, Type::none, -1);
                }

                //continue;
            }
            if(a->getAge() > a->getMaxAge()) {
                setAnimalAtCoord(a->getCoord(), Type::none, -1);
                pop.del(a->getId());

            }
        }else if(a->getType() == Type::fox and not moved.contains(a->getId())) {
            a->setAge(a->getAge() + 1);
            a->setFoodInit(a->getFoodInit() - 1);
            Coord c = a->getCoord();
            int id = a->getId();
            moved.append(id);
            QVector<Animal*> cVide = voisinVide(c);
            QVector<Animal*> rVide = voisinRab(c);
            QVector<Animal *> fVide = voisinFox(c);

            if(rVide.size() > 0) {
                int choice = rand() % (rVide.size());
                Animal* rab = rVide[choice];
                setAnimalAtCoord(rab->getCoord(), Type::none, -1);
                pop.del(rab->getId());
                pop.changeCoord(id, rVide[choice]->getCoord());
                setAnimalAtCoord(a->getCoord(), a);
                a->setFoodInit(a->getFoodInit() + a->getFoodLapin() + 1);

                if(a->getFoodInit() >= a->getFoodReprod() and fVide.size() > 0) {

                    int choiceFox = rand() % 100 + 1;
                    if(choiceFox <= a->getProbBirthRenard()) {
                        int nId = pop.getFreeId();
                        moved.append(nId);
                        setAnimalAtCoord(c, Type::fox, nId);
                    }else {
                        setAnimalAtCoord(c, Type::none, -1);
                    }

                }else {
                    setAnimalAtCoord(c, Type::none, -1);
                }
            }
            if(cVide.size() > 0 and rVide.size() == 0) {
                int choice = rand() % (cVide.size());
                pop.changeCoord(id, cVide[choice]->getCoord());
                setAnimalAtCoord(c, Type::none, -1);
                setAnimalAtCoord(a->getCoord(), a);

                if(a->getFoodInit() >= a->getFoodReprod() and fVide.size() > 0) {

                    int choiceFox = rand() % 100 + 1;
                    if(choiceFox <= a->getProbBirthRenard()) {
                        int nId = pop.getFreeId();
                        moved.append(nId);
                        setAnimalAtCoord(c, Type::fox, nId);
                    }else {
                        setAnimalAtCoord(c, Type::none, -1);
                    }

                }else {
                    setAnimalAtCoord(c, Type::none, -1);
                }

            }
            if(a->getAge() > a->getMaxAge()) {
                setAnimalAtCoord(a->getCoord(), Type::none, -1);
                pop.del(a->getId());
                continue;
            }
            if(a->getFoodInit() <= 0) {
                setAnimalAtCoord(a->getCoord(), Type::none, -1);
                pop.del(a->getId());
                continue;
            }
        }
    }
}
