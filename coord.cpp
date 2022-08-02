#include "coord.h"

Coord::Coord() {
    row = 0;
    col = 0;
}
Coord::Coord(int x, int y)
{
    row = x;
    col = y;
}

int Coord::getRow() {
    return row;
}
int Coord::getCol() {
    return col;
}

void Coord::setRow(int x) {
    if(x < 0) {
        row  = 0;
    }else if(x > 52) {
        row = 52;
    }
    row = x;
}
void Coord::setCol(int y) {
    if(y < 0) {
        col = 0;
    }
    if(y > 126) {
        col = 126;
    }
    col = y;
}

QVector<Coord> Coord::getVoisin() {
    QVector<Coord> helper = {};
    int r = this->getRow();
    int c = this->getCol();

    for(int i = r - 1; i <= r+ 1; i++) {
        for(int j = c - 1; j <= c + 1; j++) {
            if(i < 0 or j < 0 or i > 52 or j > 126) {
                continue;
            }else {
                helper.append( *(new Coord(i, j)) );
            }
        }
    }
    return helper;
}
