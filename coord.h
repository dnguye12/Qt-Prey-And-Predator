#ifndef COORD_H
#define COORD_H

#include <QVector>

class Coord
{
public:
    Coord();
    Coord(int x, int y);

    int getRow();
    int getCol();

    void setRow(int x);
    void setCol(int y);

    QVector<Coord> getVoisin();

private:
    int row;
    int col;
};

#endif // COORD_H
