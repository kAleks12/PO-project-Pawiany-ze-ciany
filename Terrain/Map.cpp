#include "Map.h"

void Map::spawn(Being * hero, int xPos, int yPos) {//adding heroes to the map

    if(fields_[xPos][yPos].isSpace())
        fields_[xPos][yPos].addBeing(hero);

}
void Map::addHero(Being* hero) {//adding heroes to the list

    allHeroes_.push_back(hero);

}
void Map::addItem(int xPos, int yPos, int itemId) {

    fields_[yPos][xPos].addItem(itemId);

}
void Map::getItems(Field field, Being * hero) {//printing items on field

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
void Map::changePos(Being* hero, int verChange, int horChange) {//relocating heroes

    int currX = getX(hero);
    int currY = getY(hero);
    int pos = getPos(hero);
    int newX = bCheck(currX + horChange);
    int newY = bCheck(currY + verChange);

    if((!isFieldFull(newX, newY))&&(!isPosEmpty(currX, currY, pos))) {//moving hero if there is any hero and space on the dest.
        fields_[newY][newX].addBeing(fields_[currY][currX].getHero(pos));
        fields_[currY][currX].removeBeing(pos);

        //printing movement details
        std::cout << hero->getHP() << "HP Hero of tribe nr " << hero->getTribe() << " " << hero->getId() << " moved from " << currX
        <<"," << currY << " -> the " << fields_[currX][currY].getTerrain() << " to " << newX << "," << newY
        << " -> the "<< fields_[newX][newY].getTerrain();

        if(fields_[newX][newY].getTerrain() == "desert"){//depending on terrain, dealing damage
            std::cout<<"\nHero loses 5 HP because he's on the desert\n";
            if(hero->getHP()>5)
            hero->changeHp(-5);
            else
                std::cout<<"\nhero is about to die!\n";
        }
        if(fields_[newX][newY].getTerrain() == "lake"){//or healing
            std::cout<<"\nHero gains 5 HP because he's by the lake\n";
            hero->changeHp(5);
        }
    }//if hero doesnt move
    else std::cout << hero->getHP() << "HP Hero of tribe nr " << hero->getTribe() << " " << hero->getId() << " stayed on "
    << getX(hero) << "," << getY(hero) << " -> the " << fields_[currX][currX].getTerrain();

}
void Map::cleanList() {//deleting dead heroes from the list
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
int Map::bCheck(int where) {//checking whether action isnt trying to reach outside map

    if(where >= mapSize_)
        where = mapSize_-1;
    if(where < 0)
        where = 0;
    return where;

}


int Map::getMapSize() {

    return mapSize_*mapSize_;

}
int Map::getX(Being* hero) {//seeking trough an entire map to find exact hero, and return its coords

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

    for(int i=0; i<mapSize_;i++){//same here
        for(int j=0; j<mapSize_; j++){
            if(fields_[i][j].getHero(0)!=nullptr)
                if(fields_[i][j].getHero(0)->getId() == hero -> getId()) return i;
            if(fields_[i][j].getHero(1)!=nullptr)
                if(fields_[i][j].getHero(1)->getId() == hero -> getId() ) return i;
        }
    }
    return -10;

}
int Map::getPos(Being* hero) {//seeking trough an entire map to find exact hero, and return its position on the field

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


void Map::move(Being* hero, int moveDirection) {//movement section

    int xWhereToGo = -1;
    int yWhereToGo = -1;
    int verChange = 0;
    int horChange = 0;
    //seeking for interaction
    seekForInteraction(getX(hero), getY(hero), getPos(hero), hero->getSpeed(), &xWhereToGo, &yWhereToGo);

    if((xWhereToGo == -1) && (yWhereToGo == -1)){//if there is no friendly or enemy unit

        int speed = hero->getSpeed();
        //changing heroes speed depending on terrain
        if((hero->getId()[0]=='S')&&(fields_[getX(hero)][getY(hero)].getTerrain()=="forest"))
            speed = speed + 2;

        if((hero->getId()[0]=='V')&&(fields_[getX(hero)][getY(hero)].getTerrain()=="lake"))
            speed = speed + 2;

        if((hero->getId()[0]=='K')&&(fields_[getX(hero)][getY(hero)].getTerrain()=="mountains"))
            speed = speed + 1;

        switch (moveDirection) {//drawing where to go
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
    else{//go towards potential interaction
        horChange = xWhereToGo - getX(hero);
        verChange = yWhereToGo - getY(hero);
    }
    changePos(hero, verChange, horChange);

}
void Map::encounter(Field & field, int startingPos){//interaction with other players

    int attackModificator = 1;
    int damageModificator = 1;
    //setting attack modificators
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

    if(field.getHero(0)->getTribe() != field.getHero(1)->getTribe()) {//interaction with enemy unit
        if (startingPos == 0) {
        //mutual dealing damage and printing fight details
            field.getHero(1) -> changeHp(-attackModificator*(field.getHero(0)->getTotalAP() - field.getHero(1) -> getDefense()));
            std::cout << "\tHero -> " << field.getHero(0)->getId() << " attacked " << field.getHero(1)->getId() << " with " << field.getHero(0)->findWeapon() <<
            " for " << attackModificator*(field.getHero(0)->getTotalAP() - field.getHero(1) -> getDefense())<< " hp\n";

            if (field.getHero(1)->isAlive()) {
                field.getHero(0) -> changeHp(-damageModificator*(3*(field.getHero(1)->getTotalAP() / 4) - field.getHero(0)->getDefense()));
                std::cout << "Hero -> " << field.getHero(1)->getId() << " attacked back " << field.getHero(0)->getId() << " with " << field.getHero(1)->findWeapon() <<
                " for " << damageModificator*(3*(field.getHero(1)->getTotalAP()/4) - field.getHero(0)->getDefense()) << " hp\n\n";
            }

        } else {//same thing here
            field.getHero(0)->changeHp(-attackModificator*(field.getHero(1)->getTotalAP() - field.getHero(0) -> getDefense()));
            std::cout << "\tHero -> " << field.getHero(1)->getId() << " attacked " << field.getHero(0)->getId() << " with " << field.getHero(1)->findWeapon() <<
            " for " << attackModificator*(field.getHero(1)->getTotalAP() - field.getHero(0) -> getDefense())  << " hp\n";

            if (field.getHero(0)->isAlive()) {
                field.getHero(1)->changeHp(-damageModificator*(3*(field.getHero(0)->getTotalAP() / 4) - field.getHero(1)->getDefense()));
                std::cout << "Hero -> " << field.getHero(0)->getId() << " attacked back " << field.getHero(1)->getId() << " with " << field.getHero(0)->findWeapon() <<
                " for " << damageModificator*(3*(field.getHero(0)->getTotalAP() / 4) - field.getHero(1)->getDefense()) << " hp\n\n";
            }
        }

        if (!(field.getHero(0)->isAlive())){//kill counters and removing heroes
            field.removeBeing(0);
            addTribeKill(field.getHero(1)->getTribe());
            field.getHero(1)->addKill();
        }

        if (!(field.getHero(1)->isAlive())){//same here
            field.removeBeing(1);
            addTribeKill(field.getHero(0)->getTribe());
            field.getHero(0)->addKill();
        }
    }
    else{//interaction with friendly unit
        if (startingPos == 0) {
            field.getHero(0)->changeHp(10);
            std::cout << "\tHero -> " << field.getHero(0)->getId() << " got healed (10hp)\n\n";
        } else {
            field.getHero(1)->changeHp(10);
            std::cout << "\tHero -> " << field.getHero(1)->getId() << " got healed (10hp)\n\n";
        }
    }

}
void Map::iteration()//iteration xD
{
    srand(time(nullptr));

        for(auto & hero : allHeroes_) {
            if(getX(hero)!=-10) {

                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);

                std::cout << "\n\nTurn of: " << hero->getId() << " !\n\n";
                int movement = rand() % 8;

                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);

                move(hero, movement);//every hero moves on its turn

                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);

                if (isFieldFull(getX(hero), getY(hero))) {//if he meets someone there is an ENCOUNTER!!!
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
                    std::cout << "\nENCOUNTER!!!!";
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
                    encounter(fields_[getY(hero)][getX(hero)], getPos(hero));
                }

                if(getX(hero)!=-10) {//if hero is alive he picks up all items on field he stands on
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
//tiny movement engine
    int xFriendly = -1;
    int yFriendly = -1;
    int xEnemy = -1;
    int yEnemy = -1;
    int enemyHp;
    int myHp = fields_[xPos][yPos].getHero(pos)->getHP();

    bool wannaHeal = false;//if hero is low hp he prefers to heal himself
    if (myHp < 50)
        wannaHeal = true;

    //looking for random enemy or friendly in heroes range
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
            //same here

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
    //if friendly was found and hero wants to heal he priorly goes there
    if ((xFriendly != -1) && (yFriendly != -1)) {
        if (wannaHeal && ((xFriendly != xPos) || (yFriendly != yPos))) {
            *xWhereToGo = yFriendly;
            *yWhereToGo = xFriendly;
        }
    } else {//if hero doesnt wanna heal or there is no friendly he chooses to fight enemy (only if enemy has less or equal hp than hero)
        if ((xEnemy != -1) && (yEnemy != -1)) {
            if ((enemyHp<=myHp) && ((xEnemy != xPos) || (yEnemy != yPos))) {
                *xWhereToGo = yEnemy;
                *yWhereToGo = xEnemy;
            }
        } else {//if there is no enemy hero tries to at least heal himself
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

void Map::showAndKillList(int tribeName) {//printing entire list of tribe that has won (only alive heroes)


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
void Map::show() {//printing map

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

int Map::numOfTribes() {//how many tribes there are
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

bool Map::isThisTribeAlive(int tribeNumber) {//checking whether exact tribe is alive
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

