
#include "Map.h"

void Map::spawn(Being * hero, int xPos, int yPos) {
    if(fields[xPos][yPos].isEmpty()) fields[xPos][yPos].addBeing(hero);
}

void Map::remove(int xPos, int yPos, int position) {
    fields[xPos][yPos].removeBeing(position);

}
