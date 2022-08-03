#ifndef GRILLE_H
#define GRILLE_H

#include <QVector>

#include <animal.h>
#include <population.h>

class Grille
{
public:
    Grille();

    Animal* getAnimalAtCoord(int row, int col);
    Animal* getAnimalAtCoord(Coord c);
    void setAnimalAtCoord(Coord c, Type t, int idx);
    void setAnimalAtCoord(Coord c, Animal* a);

    QVector<Animal*> voisinVide(Coord c);
    QVector<Animal*> voisinRab(Coord c);
    QVector<Animal*> voisinFox(Coord c);

    void updateGrille();

    void debug();

private:
    QVector<QVector<Animal*>> map;
    Population pop = *(new Population());
};

#endif // GRILLE_H
