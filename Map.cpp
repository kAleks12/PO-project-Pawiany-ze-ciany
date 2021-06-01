#include "Map.h"

void Map::spawn(Being * hero, int xPos, int yPos) {

    if(fields_[xPos][yPos].isSpace())
        fields_[xPos][yPos].addBeing(hero);

}
void Map::addHero(Being* hero) {

    allHeroes_.push_back(hero);

}
void Map::addItem(int xPos, int yPos, int itemId) {

    fields_[yPos][xPos].addItem(itemId);

}
void Map::getItems(Field field, Being * hero) {

   // std::cout << "\nItems on this field: ";
    //field.printItems();
    //std::cout << std::endl;

    int iterations = field.getItemsNum();

    for(int i=0; i < iterations; i++) {
        try {
            Item tmp = field.copyItem();

            if (hero->whetherPickUp(tmp)) {

                hero->addItem(tmp);
                hero->changeWeapon();
                field.deleteItem();
            }
        }
        catch( const std::bad_alloc &badAlloc){
            std::cout << "Program crashed in getItems :)";
            exit(69);
        }

    }
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
    //std::cout << "Current weapon: " << hero->findWeapon() << std::endl;
    //std::cout << "Current armor: " << hero->findArmor() << "\n\n";

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


        std::cout << hero->getHP() << "HP Hero of tribe nr " << hero->getTribe() << " " << hero->getId() << " moved from " << currX
        <<"," << currY << " -> the " << fields_[currX][currY].getTerrain() << " to " << newX << "," << newY
        << " -> the "<< fields_[newX][newY].getTerrain();

        if(fields_[newX][newY].getTerrain() == "desert"){
            std::cout<<"\nHero loses 5 HP because he's on the desert\n";
            if(hero->getHP()>5)
            hero->changeHp(-5);
            else
                std::cout<<"\nhero is about to die!\n";
        }
        if(fields_[newX][newY].getTerrain() == "lake"){
            std::cout<<"\nHero gains 5 HP because he's by the lake\n";
            hero->changeHp(5);
        }
    }
    else std::cout << hero->getHP() << "HP Hero of tribe nr " << hero->getTribe() << " " << hero->getId() << " stayed on "
    << getX(hero) << "," << getY(hero) << " -> the " << fields_[currX][currX].getTerrain();

}
void Map::cleanList() {
    /*
    std::list<Being*>::iterator it = allHeroes_.begin();
    while (it != allHeroes_.end())
    {
        if (!(*it)->isAlive())
        {
            (*it)->destroy();
            it = allHeroes_.erase(it);  // alternatively, i = items.erase(i);
            //showList();
            //system("Pause");
        }
        else it++;
    }*/
    std::list<Being *> tmpList;
    auto it = allHeroes_.begin();
        while (it != allHeroes_.end()) {
            if (!(*it)->isAlive()) {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
                (*it)->destroy();
            } else
                tmpList.push_back(*it);
            it++;
        }
        allHeroes_.clear();
        allHeroes_.swap(tmpList);


}
int Map::bCheck(int where) {

    if(where >= mapSize_)
        where = mapSize_-1;
    if(where < 0)
        where = 0;
    return where;

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
int Map::getListSize() {

    return allHeroes_.size();

}


void Map::move(Being* hero, int moveDirection) {

    int xWhereToGo = -1;
    int yWhereToGo = -1;
    int verChange = 0;
    int horChange = 0;

    seekForInteraction(getX(hero), getY(hero), getPos(hero), hero->getSpeed(), &xWhereToGo, &yWhereToGo);

    if((xWhereToGo == -1) && (yWhereToGo == -1)){

        int speed = hero->getSpeed();

        if((hero->getId()[0]=='S')&&(fields_[getX(hero)][getY(hero)].getTerrain()=="forest"))
            speed = speed + 2;

        if((hero->getId()[0]=='V')&&(fields_[getX(hero)][getY(hero)].getTerrain()=="lake"))
            speed = speed + 2;

        if((hero->getId()[0]=='K')&&(fields_[getX(hero)][getY(hero)].getTerrain()=="mountains"))
            speed = speed + 1;

        switch (moveDirection) {
            case 0:
                verChange = -(speed);
                break;
            case 1:
                verChange = -(speed);
                horChange = -(speed);
                break;
            case 2:
                horChange = -(speed);
                break;
            case 3:
                verChange = speed;
                horChange = -(speed);
                break;
            case 4:
                verChange = speed;
                break;
            case 5:
                verChange = speed;
                horChange = speed;
                break;
            case 6:
                horChange = speed;
                break;
            case 7:
                verChange = -(speed);
                horChange = speed;
                break;
            default:
                //std::cout << "Wrong direction!";
                break;
        }

    }
    else{
        horChange = xWhereToGo - getX(hero);
        verChange = yWhereToGo - getY(hero);
    }
    changePos(hero, verChange, horChange);

}
void Map::encounter(Field & field, int startingPos){

    int attackModificator = 1;
    int damageModificator = 1;

    if((field.getHero(startingPos)->getId()[0]=='S')&&(field.getTerrain()=="forest")){
        attackModificator = 2;
        damageModificator = 1;
    }

    if((field.getHero(startingPos)->getId()[0]=='V')&&(field.getTerrain()=="lake")){
        attackModificator = 1;
        damageModificator = 2;
    }

    if((field.getHero(startingPos)->getId()[0]=='N')&&(field.getTerrain()=="plain")){
        attackModificator = 2;
        damageModificator = 2;
    }

    if(field.getHero(0)->getTribe() != field.getHero(1)->getTribe()) {
        if (startingPos == 0) {

            field.getHero(1) -> changeHp(-attackModificator*(field.getHero(0)->getTotalAP() - field.getHero(1) -> getDefense()));
            std::cout << "\tHero -> " << field.getHero(0)->getId() << " attacked " << field.getHero(1)->getId() << " with " << field.getHero(0)->findWeapon() <<
            " for " << attackModificator*(field.getHero(0)->getTotalAP() - field.getHero(1) -> getDefense())<< " hp\n";

            if (field.getHero(1)->isAlive()) {
                field.getHero(0) -> changeHp(-damageModificator*(3*(field.getHero(1)->getTotalAP() / 4) - field.getHero(0)->getDefense()));
                std::cout << "Hero -> " << field.getHero(1)->getId() << " attacked back " << field.getHero(0)->getId() << " with " << field.getHero(1)->findWeapon() <<
                " for " << damageModificator*(3*(field.getHero(1)->getTotalAP()/4) - field.getHero(0)->getDefense()) << " hp\n\n";
            }

        } else {
            field.getHero(0)->changeHp(-attackModificator*(field.getHero(1)->getTotalAP() - field.getHero(0) -> getDefense()));
            std::cout << "\tHero -> " << field.getHero(1)->getId() << " attacked " << field.getHero(0)->getId() << " with " << field.getHero(1)->findWeapon() <<
            " for " << attackModificator*(field.getHero(1)->getTotalAP() - field.getHero(0) -> getDefense())  << " hp\n";

            if (field.getHero(0)->isAlive()) {
                field.getHero(1)->changeHp(-damageModificator*(3*(field.getHero(0)->getTotalAP() / 4) - field.getHero(1)->getDefense()));
                std::cout << "Hero -> " << field.getHero(0)->getId() << " attacked back " << field.getHero(1)->getId() << " with " << field.getHero(0)->findWeapon() <<
                " for " << damageModificator*(3*(field.getHero(0)->getTotalAP() / 4) - field.getHero(1)->getDefense()) << " hp\n\n";
            }
        }

        if (!(field.getHero(0)->isAlive())){
            field.removeBeing(0);
            addTribeKill(field.getHero(1)->getTribe());
            field.getHero(1)->addKill();
        }

        if (!(field.getHero(1)->isAlive())){
            field.removeBeing(1);
            addTribeKill(field.getHero(0)->getTribe());
            field.getHero(0)->addKill();
        }
    }
    else{
        if (startingPos == 0) {
            field.getHero(0)->changeHp(10);
            std::cout << "\tHero -> " << field.getHero(0)->getId() << " got healed (10hp)\n\n";
        } else {
            field.getHero(1)->changeHp(10);
            std::cout << "\tHero -> " << field.getHero(1)->getId() << " got healed (10hp)\n\n";
        }
    }

}
void Map::iteration()
{
    srand(time(nullptr));

        for(auto & hero : allHeroes_) {
            if(getX(hero)!=-10) {

                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);

                std::cout << "\n\nTurn of: " << hero->getId() << " !\n\n";
                int movement = rand() % 8;

                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);

                move(hero, movement);

                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);

                if (isFieldFull(getX(hero), getY(hero))) {
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
                    std::cout << "\nENCOUNTER!!!!";
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
                    encounter(fields_[getY(hero)][getX(hero)], getPos(hero));
                }

                if(getX(hero)!=-10) {
                    getItems(fields_[getX(hero)][getY(hero)], hero);
                    hero->useTempItems();
                    hero->printBackpack();
                }

                show();
                //Sleep(500);
                //system("Pause");
            }
        }
        cleanList();

}
void Map::seekForInteraction(int yPos, int xPos, int pos, int howFarIllGo, int * xWhereToGo, int * yWhereToGo) {

    int xFriendly = -1;
    int yFriendly = -1;
    int xEnemy = -1;
    int yEnemy = -1;
    int enemyHp;
    int myHp = fields_[xPos][yPos].getHero(pos)->getHP();

    bool wannaHeal = false;
    if (myHp < 50)
        wannaHeal = true;


    for (int i = bCheck(xPos - howFarIllGo); i < bCheck(xPos + howFarIllGo); i++) {
        for (int j = bCheck(yPos - howFarIllGo); j < bCheck(yPos + howFarIllGo); j++) {
            if ((fields_[i][j].isPosEmpty(0) && !fields_[i][j].isPosEmpty(1)) && ((i != xPos) || (j != yPos))) {
                if (fields_[i][j].getHero(1)->getTribe() == fields_[xPos][yPos].getHero(pos)->getTribe()) {
                    xFriendly = i;
                    yFriendly = j;
                } else {
                    xEnemy = i;
                    yEnemy = j;
                    enemyHp = fields_[i][j].getHero(1)->getHP();
                }
            }


            if ((fields_[i][j].isPosEmpty(1) && !fields_[i][j].isPosEmpty(0)) && ((i != xPos) || (j != yPos))) {
                if ((fields_[i][j].getHero(0)->getTribe() == fields_[xPos][yPos].getHero(pos)->getTribe())) {
                    xFriendly = i;
                    yFriendly = j;
                } else {
                    xEnemy = i;
                    yEnemy = j;
                    enemyHp = fields_[i][j].getHero(0)->getHP();
                }
            }
        }
    }

    if ((xFriendly != -1) && (yFriendly != -1)) {
        if (wannaHeal && ((xFriendly != xPos) || (yFriendly != yPos))) {
            *xWhereToGo = yFriendly;
            *yWhereToGo = xFriendly;
        }
    } else {
        if ((xEnemy != -1) && (yEnemy != -1)) {
            if ((enemyHp<=myHp) && ((xEnemy != xPos) || (yEnemy != yPos))) {
                *xWhereToGo = yEnemy;
                *yWhereToGo = xEnemy;
            }
        } else {
            if ((xFriendly != -1) && (yFriendly != -1)) {
                if (!wannaHeal && ((xFriendly != xPos) || (yFriendly != yPos))) {
                    *xWhereToGo = yFriendly;
                    *yWhereToGo = xFriendly;
                }
            }
        }
    }

}


[[maybe_unused]] void Map::showField(int xPos, int yPos) {

    fields_[xPos][yPos].showField();

}

void Map::showAndKillList(int tribeName) {


    while(allHeroes_.size() != 0){

        if(allHeroes_.front()->getTribe() == tribeName){
            std::cout << "ID: " << allHeroes_.front()->getId();
            std::cout << ", HP: " << allHeroes_.front()->getHP();
            std::cout << ", Name: " << allHeroes_.front()->getName();
            std::cout << ", Kill counter: " << allHeroes_.front()->returnKills();
            std::cout << std::endl;
        }

        allHeroes_.pop_front();

    }



}
void Map::show() {

    int height = 0;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);

    /*for (Being* n : allHeroes_) {
        std::cout << n->getId() << "\t" << n->getItemsQt() << std::endl;
    }*/
    std::cout << allHeroes_.size();
    std::cout << "                                            Game Map\n";
    std::cout << "===========================================================================================================\n";
    std::cout << "||     0         1         2         3         4         5         6         7         8         9       ||\n";
    for(auto & field : fields_){
        std::cout << "| |";
        for(auto & j : field){
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
            if(j.isPosEmpty(0)&&j.isPosEmpty(1)) {
                std::cout << " + empty +";
            }
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


bool Map::isFieldFull(int xPos, int yPos) {

    return !(fields_[yPos] [xPos].isSpace());

}
bool Map::isPosEmpty(int xPos, int yPos, int pos) {

    return (fields_[yPos] [xPos].isPosEmpty(pos));

}

int Map::numOfTribes() {
    int tribesTab[4];
    tribesTab[0] = 0;
    tribesTab[1] = 0;
    tribesTab[2] = 0;
    tribesTab[3] = 0;
    for(auto & hero: allHeroes_){
        tribesTab[hero->getTribe()]++;
    }
    int howMany = 4;
    if(tribesTab[0] == 0)
        howMany --;
    if(tribesTab[1] == 0)
        howMany --;
    if(tribesTab[2] == 0)
        howMany --;
    if(tribesTab[3] == 0)
        howMany --;

    return howMany;
}

bool Map::isThisTribeAlive(int tribeNumber) {
    int tribesTab[4];
    tribesTab[0] = 0;
    tribesTab[1] = 0;
    tribesTab[2] = 0;
    tribesTab[3] = 0;
    for(auto & hero: allHeroes_){
        tribesTab[hero->getTribe()]++;
    }
    if(tribesTab[tribeNumber])
        return true;
    else
        return false;
}

void Map::addTribeKill(int tribeNumber) {
    tribeKills[tribeNumber]++;

}

int Map::returnTribeKills(int tribeNumber) {
    return tribeKills[tribeNumber];
}

