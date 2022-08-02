#ifndef GRILLE_H
#define GRILLE_H

#include <QVector>

#include <animal.h>

class Grille
{
public:
    Grille();

    Animal* getAnimalAtCoord(int row, int col);
    Animal* getAnimalAtCoord(Coord c);
    void setAnimalAtCoord(Coord c, Type t);
    void setAnimalAtCoord(Coord c, Animal* a);

    QVector<Animal*> voisinVide(Coord c);
    QVector<Animal*> voisinRab(Coord c);
    QVector<Animal*> voisinFox(Coord c);

    void updateGrille();

    void debug();

private:
    QVector<QVector<Animal*>> map;
};

#endif // GRILLE_H
