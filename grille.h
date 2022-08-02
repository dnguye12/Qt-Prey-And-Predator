#ifndef GRILLE_H
#define GRILLE_H

#include <QVector>

#include <animal.h>

class Grille
{
public:
    Grille();

    Animal getAnimalAtCoord(Coord c);
    void setAnimalAtCoord(Coord c, Type t);

    void debug();

private:
    QVector<QVector<Animal>> map;
};

#endif // GRILLE_H
