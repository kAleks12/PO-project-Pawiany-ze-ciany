#ifndef PO_MAP_H
#define PO_MAP_H
#include "Field.h"
#include "Being.h"
#include "Southern_Warrior.h"
#include "Knight.h"
#include "Slav.h"

class Map {
    Field map[100][100];
public:
    void spawn(Being *, int, int);
    void remove(int, int, int);

};

#endif //PO_MAP_H
