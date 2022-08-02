#ifndef COORD_H
#define COORD_H


class Coord
{
public:
    Coord();
    Coord(int x, int y);

    int getRow();
    int getCol();

    void setRow(int x);
    void setCol(int y);

private:
    int row;
    int col;
};

#endif // COORD_H
