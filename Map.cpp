#include "Map.h"



void Map::spawn(Being * hero, int xPos, int yPos) {
    if(map[xPos][yPos].isEmpty()) map[xPos][yPos].addBeing(hero);
}

void Map::remove(int xPos, int yPos, int position) {
    map[xPos][yPos].removeBeing(position);

}
