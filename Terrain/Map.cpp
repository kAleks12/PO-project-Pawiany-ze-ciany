#include "Map.h"

void Map::spawn(Being * hero, int xPos, int yPos) {
    if(fields_[xPos][yPos].isSpace()) fields_[xPos][yPos].addBeing(hero);
}

void Map::remove(int xPos, int yPos, int position) {
    fields_[xPos][yPos].removeBeing(position);
}

void Map::changePos(int fromX, int fromY, int pos, int whereX, int whereY) {
    if((!isFieldFull(whereX, whereY))&&(!isPosEmpty(fromX, fromY, pos))) {
        fields_[whereX][whereY].addBeing(fields_[fromX][fromY].getHero(pos));
        fields_[fromX][fromY].removeBeing(pos);
    }
    else std::cout << "Where is full, or From is empty" << std::endl;
}

void Map::addHero(Being* hero) {
    allHeroes_.push_back(hero);
}

void Map::show() {
    int height = 0;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
    for (Being* n : allHeroes_) {
        std::cout << n-> getId() << std::endl;
    }
    std::cout << "                                            Game Map\n";
    std::cout << "===========================================================================================================\n";
    std::cout << "||     0         1         2         3         4         5         6         7         8         9       ||\n";
    for(auto & field : fields_){
        std::cout << "||";
        for(auto & j : field){
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
            if(j.isPosEmpty(0)&&j.isPosEmpty(1)) std::cout << " + empty +";
            else {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
                if(j.getHero(0) != nullptr) std::cout << " " << j.getHero(0) -> getId() << "/";
                else std::cout << " ----/";
                if(j.getHero(1) != nullptr) std::cout << j.getHero(1) -> getId();
                else std::cout << "----";
            }
        }
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
        std::cout << " " << height++ << " ||\n";
    }
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
    std::cout << "===========================================================================================================\n";
}
////////////////////////////////////////////

bool Map::isFieldFull(int xPos, int yPos) {
    return !(fields_[xPos] [yPos].isSpace());
}

 bool Map::isPosEmpty(int xPos, int yPos, int pos) {
    return (fields_[xPos] [yPos].isPosEmpty(pos));
}

//////////////////////////////////////////////
int Map::getMapSize() {
    return mapSize_*mapSize_;
}

int Map::getX(Being* hero) {
    for(int i=0; i<mapSize_;i++){
        for(int j=0; j<mapSize_; j++){
            if(fields_[i][j].getHero(0)!=nullptr)
                if(fields_[i][j].getHero(0)->getId() == hero -> getId()) return i;
            if(fields_[i][j].getHero(1)!=nullptr)
                if(fields_[i][j].getHero(1)->getId() == hero -> getId() ) return i;
        }
    }
}

int Map::getY(Being* hero) {
    for(auto & field : fields_){
        for(int j=0; j<mapSize_; j++){
            if(field[j].getHero(0)!=nullptr)
                if(field[j].getHero(0)->getId() == hero -> getId()) return j;
            if(field[j].getHero(1)!=nullptr)
                if(field[j].getHero(1)->getId() == hero -> getId() ) return j;
        }
    }
}

int Map::getPos(Being* hero) {
    for(auto & field : fields_){
        for(auto & j : field){
            if(j.getHero(0)!=nullptr)
                if(j.getHero(0)->getId() == hero -> getId()) return 0;
            if(j.getHero(1)!=nullptr)
                if(j.getHero(1)->getId() == hero -> getId() ) return 1;
        }
    }
}
/////////////////////////////////////////////

void Map::showField(int xPos, int yPos) {
    fields_[xPos][yPos].showField();
}

void Map::move(Being* hero, int moveDirection)
{
    switch(hero -> getId()[0]) {
        case 'S':
            switch (moveDirection) {
                case 0:
                    if(getY(hero)-3 < 0)
                    changePos(getX(hero), getY(hero), getPos(hero), getX(hero), 0);
                    else changePos(getX(hero), getY(hero), getPos(hero), getX(hero), getY(hero) - 3);
                    break;
                case 1:
                    if(getY(hero)-3 < 0 || getX(hero)-3 < 0) {
                        if(getY(hero)-3 < 0 && getX(hero)-3 < 0) changePos(getX(hero), getY(hero), getPos(hero), 0, 0);
                        if(getY(hero)-3 < 0) changePos(getX(hero), getY(hero), getPos(hero), getX(hero) - 3, 0);
                        if(getX(hero)-3 < 0) changePos(getX(hero), getY(hero), getPos(hero), 0, getY(hero) - 3);
                    }
                    else changePos(getX(hero), getY(hero), getPos(hero), getX(hero) - 3, getY(hero) - 3);
                    break;
                case 2:
                    changePos(getX(hero), getY(hero), getPos(hero), getX(hero) - 3, getY(hero));
                    break;
                case 3:
                    changePos(getX(hero), getY(hero), getPos(hero), getX(hero) - 3, getY(hero) + 3);
                    break;
                case 4:
                    changePos(getX(hero), getY(hero), getPos(hero), getX(hero), getY(hero) + 3);
                    break;
                case 5:
                    changePos(getX(hero), getY(hero), getPos(hero), getX(hero) + 3, getY(hero) + 3);
                    break;
                case 6:
                    changePos(getX(hero), getY(hero), getPos(hero), getX(hero) + 3, getY(hero));
                    break;
                case 7:
                    changePos(getX(hero), getY(hero), getPos(hero), getX(hero) + 3, getY(hero) - 3);
                    break;
                default:
                    std::cout << "Wrong direction!";
            }
            break;
        case 'N':
            switch(moveDirection){
                case 0:
                    changePos(getX(hero), getY(hero), getPos(hero), getX(hero), getY(hero) - 2);
                    break;
                case 1:
                    changePos(getX(hero), getY(hero), getPos(hero), getX(hero) - 2, getY(hero) - 2);
                    break;
                case 2:
                    changePos(getX(hero), getY(hero), getPos(hero), getX(hero) - 2, getY(hero));
                    break;
                case 3:
                    changePos(getX(hero), getY(hero), getPos(hero), getX(hero) - 2, getY(hero) + 2);
                    break;
                case 4:
                    changePos(getX(hero), getY(hero), getPos(hero), getX(hero), getY(hero) + 2);
                    break;
                case 5:
                    changePos(getX(hero), getY(hero), getPos(hero), getX(hero) + 2, getY(hero) + 2);
                    break;
                case 6:
                    changePos(getX(hero), getY(hero), getPos(hero), getX(hero) + 2, getY(hero));
                    break;
                case 7:
                    changePos(getX(hero), getY(hero), getPos(hero), getX(hero) + 2, getY(hero) - 2);
                    break;
                default:
                    std::cout << "Wrong direction!";
            }
            break;
        case 'V':
            switch(moveDirection){
                case 0:
                    changePos(getX(hero), getY(hero), getPos(hero), getX(hero), getY(hero) - 2);
                    break;
                case 1:
                    changePos(getX(hero), getY(hero), getPos(hero), getX(hero) - 2, getY(hero) - 2);
                    break;
                case 2:
                    changePos(getX(hero), getY(hero), getPos(hero), getX(hero) - 2, getY(hero));
                    break;
                case 3:
                    changePos(getX(hero), getY(hero), getPos(hero), getX(hero) - 2, getY(hero) + 2);
                    break;
                case 4:
                    changePos(getX(hero), getY(hero), getPos(hero), getX(hero), getY(hero) + 2);
                    break;
                case 5:
                    changePos(getX(hero), getY(hero), getPos(hero), getX(hero) + 2, getY(hero) + 2);
                    break;
                case 6:
                    changePos(getX(hero), getY(hero), getPos(hero), getX(hero) + 2, getY(hero));
                    break;
                case 7:
                    changePos(getX(hero), getY(hero), getPos(hero), getX(hero) + 2, getY(hero) - 2);
                    break;
                default:
                    std::cout << "Wrong direction!";
            }
            break;
        case 'K':
            switch(moveDirection){
                case 0:
                    changePos(getX(hero), getY(hero), getPos(hero), getX(hero), getY(hero) - 1);
                    break;
                case 1:
                    changePos(getX(hero), getY(hero), getPos(hero), getX(hero) - 1, getY(hero) - 1);
                    break;
                case 2:
                    changePos(getX(hero), getY(hero), getPos(hero), getX(hero) - 1, getY(hero));
                    break;
                case 3:
                    changePos(getX(hero), getY(hero), getPos(hero), getX(hero) - 1, getY(hero) + 1);
                    break;
                case 4:
                    changePos(getX(hero), getY(hero), getPos(hero), getX(hero), getY(hero) + 1);
                    break;
                case 5:
                    changePos(getX(hero), getY(hero), getPos(hero), getX(hero) + 1, getY(hero) + 1);
                    break;
                case 6:
                    changePos(getX(hero), getY(hero), getPos(hero), getX(hero) + 1, getY(hero));
                    break;
                case 7:
                    changePos(getX(hero), getY(hero), getPos(hero), getX(hero) + 1, getY(hero) - 1);
                    break;
                default:
                    std::cout << "Wrong direction!";
            }
            break;
    }

}

void Map::getItems(Field field, Being * hero) {
    while(field.areItems()) hero -> addItem(field.giveItem());
}

void Map::encounter(Field & field, int startingPos){
    if(startingPos == 0){
        field.getHero(1)->changeHp(field.getHero(0)->getTotalAttackPower());
        if(field.getHero(1)->isAlive()) field.getHero(0)->changeHp(field.getHero(1)->getTotalAttackPower()/2);
        else field.removeBeing(1);

        if(!(field.getHero(0)->isAlive())) field.removeBeing(0);;
    }
    else{
        field.getHero(0)->changeHp(field.getHero(1)->getTotalAttackPower());
        if(field.getHero(0)->isAlive()) field.getHero(1)->changeHp(field.getHero(0)->getTotalAttackPower()/2);
        else field.removeBeing(0);

        if(!(field.getHero(1)->isAlive())) field.removeBeing(1);
    }
}

void Map::iteration()
{
    for(Being* hero : allHeroes_) {
        if(hero->isAlive()) {
            move(hero, 5);
            getItems(fields_[getX(hero)][getY(hero)], hero);
            if (isFieldFull(getX(hero), getY(hero))) {
                encounter(fields_[getX(hero)][getY(hero)], getPos(hero));
            }
        }
        else delete hero;
    }

}