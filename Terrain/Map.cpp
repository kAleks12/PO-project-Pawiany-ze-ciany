#include "Map.h"

void Map::spawn(Being * hero, int xPos, int yPos) {
    if(fields_[xPos][yPos].isSpace()) fields_[xPos][yPos].addBeing(hero);
}

void Map::changePos(Being* hero, int verChange, int horChange) {
    int currX = getX(hero);
    int currY = getY(hero);
    int pos = getPos(hero);
    int newX = bCheck(currX + horChange);
    int newY = bCheck(currY + verChange);

    if((!isFieldFull(newX, newY))&&(!isPosEmpty(currX, currY, pos))) {
        fields_[newY][newX].addBeing(fields_[currY][currX].getHero(pos));
        fields_[currY][currX].removeBeing(pos);
        std::cout << hero->getHp() << " Hero of tribe nr " << hero->getTribe() << hero->getId() << " moved from " << currX << ", " << currY << " to " << newX << ", " << newY << std::endl;
    }
    else std::cout << hero->getHp() << " Hero of tribe nr " << hero->getTribe() << hero->getId() << " stayed on " << getX(hero) << " " <<getY(hero) << std::endl;
}

void Map::addHero(Being* hero) {
    allHeroes_.push_back(hero);
}

void Map::removeHero(Being* hero){
    auto pos = std::find(allHeroes_.begin(), allHeroes_.end(), hero);
    allHeroes_.erase(pos);
}

int Map::bCheck(int where) {
    if(where >= mapSize_)
        where = mapSize_-1;
    if(where < 0)
        where = 0;
    return where;
}

void Map::show() {
    int height = 0;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
    /*for (Being* n : allHeroes_) {
        std::cout << n-> getId() << std::endl;
    }*/
    std::cout << allHeroes_.size();
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
    return !(fields_[yPos] [xPos].isSpace());
}

 bool Map::isPosEmpty(int xPos, int yPos, int pos) {
    return (fields_[yPos] [xPos].isPosEmpty(pos));
}

//////////////////////////////////////////////
void Map::getItems(Field field, Being * hero) {
    while(field.areItems())
        hero -> addItem(field.giveItem());
}

int Map::getMapSize() {
    return mapSize_*mapSize_;
}

int Map::getX(Being* hero) {
    for(int i=0; i<mapSize_;i++){
        for(int j=0; j<mapSize_; j++){
            if(fields_[i][j].getHero(0)!=nullptr)
                if(fields_[i][j].getHero(0)->getId() == hero -> getId()) return j;
            if(fields_[i][j].getHero(1)!=nullptr)
                if(fields_[i][j].getHero(1)->getId() == hero -> getId() ) return j;
        }
    }
    return -10;
}

int Map::getY(Being* hero) {
    for(int i=0; i<mapSize_;i++){
        for(int j=0; j<mapSize_; j++){
            if(fields_[i][j].getHero(0)!=nullptr)
                if(fields_[i][j].getHero(0)->getId() == hero -> getId()) return i;
            if(fields_[i][j].getHero(1)!=nullptr)
                if(fields_[i][j].getHero(1)->getId() == hero -> getId() ) return i;
        }
    }
    return -10;
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
    return -10;
}
/////////////////////////////////////////////

void Map::showField(int xPos, int yPos) {
    fields_[xPos][yPos].showField();
}

void Map::move(Being* hero, int moveDirection) {

    int xWhereToGo = -1;
    int yWhereToGo = -1;
    int verChange = 0;
    int horChange = 0;

    seekForInteraction(getX(hero), getY(hero), getPos(hero), hero->getSpeed(), &xWhereToGo, &yWhereToGo);

    if((xWhereToGo == -1) && (yWhereToGo == -1)){

        switch (moveDirection) {
            case 0:
                verChange = -(hero->getSpeed());
                break;
            case 1:
                verChange = -(hero->getSpeed());
                horChange = -(hero->getSpeed());
                break;
            case 2:
                horChange = -(hero->getSpeed());
                break;
            case 3:
                verChange = hero->getSpeed();
                horChange = -(hero->getSpeed());
                break;
            case 4:
                verChange = hero->getSpeed();
                break;
            case 5:
                verChange = hero->getSpeed();
                horChange = hero->getSpeed();
                break;
            case 6:
                horChange = hero->getSpeed();
                break;
            case 7:
                verChange = -(hero->getSpeed());
                horChange = hero->getSpeed();
                break;
            default:
                std::cout << "Wrong direction!";
        }

    }
    else{
        horChange = xWhereToGo - getX(hero);
        verChange = yWhereToGo - getY(hero);
    }
    changePos(hero, verChange, horChange);

}

void Map::encounter(Field & field, int startingPos){
    if(field.getHero(0)->getTribe() != field.getHero(1)->getTribe()) {
        if (startingPos == 0) {
            field.getHero(1)->changeHp(-(field.getHero(0)->getTotalAttackPower() - field.getHero(1) -> getDefense()));
            if (field.getHero(1)->isAlive())
                field.getHero(0)->changeHp( -((field.getHero(1)->getTotalAttackPower()/2) - field.getHero(0) -> getDefense()) );
        } else {
            field.getHero(0)->changeHp(-(field.getHero(1)->getTotalAttackPower() - field.getHero(0) -> getDefense()));
            if (field.getHero(0)->isAlive())
                field.getHero(1)->changeHp( -((field.getHero(0)->getTotalAttackPower()/2) - field.getHero(1) -> getDefense()) );
        }

        if (!(field.getHero(0)->isAlive()))
            field.removeBeing(0);
        if (!(field.getHero(1)->isAlive()))
            field.removeBeing(1);
    }
    else{
        if (startingPos == 0) {
            field.getHero(1)->changeHp(10);
        } else {
            field.getHero(0)->changeHp(10);
        }
    }
}

void Map::iteration()
{
    srand(time(nullptr));
        for(auto & hero : allHeroes_) {
            if(getX(hero)!=-10) {
                int movement = rand() % 8;
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
                move(hero, movement);
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
                if (isFieldFull(getX(hero), getY(hero))) {
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
                    std::cout << "\nENCOUNTER!!!!" << "\n\n";
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
                    encounter(fields_[getY(hero)][getX(hero)], getPos(hero));
                }
                getItems(fields_[getX(hero)][getY(hero)], hero);
                hero -> useEq();
            }
            else{
            }
        }
}

void Map::seekForInteraction(int yPos, int xPos, int pos, int howFarIllGo, int * xWhereToGo, int * yWhereToGo) {

    bool wannaHeal = false;
    if(fields_[xPos][yPos].getHero(pos)->getHp()<50)
        wannaHeal = true;

        int xFriendly = -1;
        int yFriendly = -1;
        int xEnemy = -1;
        int yEnemy = -1;


    for(int i= bCheck(xPos - howFarIllGo); i < bCheck(xPos + howFarIllGo); i++){
        for(int j = bCheck(yPos - howFarIllGo); j < bCheck(yPos + howFarIllGo); j++){
            if((fields_[i][j].isPosEmpty(0) && !fields_[i][j].isPosEmpty(1)) && ((i != xPos) || (j != yPos))){
                if(fields_[i][j].getHero(1)->getTribe() == fields_[xPos][yPos].getHero(pos)->getTribe()){
                    xFriendly = i;
                    yFriendly = j;
                }
                else{
                    xFriendly = i;
                    yFriendly = j;
                }
            }



            if((fields_[i][j].isPosEmpty(1) && !fields_[i][j].isPosEmpty(0)) && ((i != xPos) || (j != yPos))){
                if((fields_[i][j].getHero(0)->getTribe() == fields_[xPos][yPos].getHero(pos)->getTribe())){
                    xFriendly = i;
                    yFriendly = j;
                }
                else{
                    xEnemy = i;
                    yEnemy = j;
                }
            }
        }
    }

    if((xFriendly != -1) && (yFriendly != -1)){
        if(wannaHeal && ((xFriendly != xPos ) || (yFriendly != yPos ))){
            *xWhereToGo = yFriendly;
            *yWhereToGo = xFriendly;
        }
    }

    if((xEnemy != -1) && (yEnemy != -1)){
        if(!wannaHeal && ((xEnemy != xPos ) || (yEnemy != yPos ))){
            *xWhereToGo = yEnemy;
            *yWhereToGo = xEnemy;
        }
    }
    else{
        if((xFriendly != -1) && (yFriendly != -1)){
            if(!wannaHeal && ((xFriendly != xPos ) || (yFriendly != yPos ))){
                *xWhereToGo = yFriendly;
                *yWhereToGo = xFriendly;
            }
        }
    }


}

