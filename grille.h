#ifndef GRILLE_H
#define GRILLE_H

#include <QVector>

#include <animal.h>

class Grille
{
public:
    Grille();

    Animal getAnimalAtCoord(int row, int col);
    void setAnimalAtCoord(Coord c, Type t);

    void debug();

private:
    QVector<QVector<Animal>> map;
};

#endif // GRILLE_H
