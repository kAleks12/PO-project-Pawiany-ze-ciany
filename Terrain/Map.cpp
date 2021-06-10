#include "Map.h"
#include "../Config.h"

int Map::numOfMapsCreated = 0;

Map::Map() {

    name_ = "Map_" + std::to_string(numOfMapsCreated) + "_";
    summary_.open(name_ + "_summary.txt", std::ios::out | std::ios::trunc);

    if(summary_.good()) {
        summary_ << "Welcome to the simulation summary file!" << std::endl << std::endl << std::endl << "Cemetery(graves of brave heroes will remind us of them forever):" << std::endl << std::endl;
    }

    numOfMapsCreated++;
    summary_.close();
}

void Map::spawn(Being * hero, int xPos, int yPos) {     //adding heroes to the specific field on the map

    if(fields_[xPos][yPos].isSpace())
        fields_[xPos][yPos].addBeing(hero);

}
void Map::addHero(Being* hero) {    //adding heroes to the heroes list

    allHeroes_.push_back(hero);

}
void Map::addItem(int xPos, int yPos, int itemId) {     //adding item to the specific field on the map

    fields_[yPos][xPos].addItem(itemId);

}
void Map::getItems(Field field, Being * hero) {     //picking up objects from the certain field by hero

/*
    std::cout << "\nItems on this field: ";
    field.printItems();
    std::cout << std::endl;
*/

    //getting number of items on this field
    int iterations = field.getItemsNum();


    //checking for each item if the hero wants to pick it up
    for(int iterator = 0; iterator < iterations; iterator++){
        Item tmpItem = field.copyItem();
            if (hero->whetherPickUp(tmpItem)) {
                hero->addItem(tmpItem);
                hero->updateWeapon();
                field.deleteItem();
            }
    }
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);

/*
    std::cout << "Current weapon: " << hero->findWeapon() << std::endl;
    std::cout << "Current armor: " << hero->findArmor() << "\n\n";
*/

}
void Map::changePos(Being* hero, int verChange, int horChange) {    //relocating heroes from field to another field

    int currX = getX(hero);
    int currY = getY(hero);
    int pos = getPos(hero);

    int newX = bCheck(currX + horChange);
    int newY = bCheck(currY + verChange);

    if((!isFieldFull(newX, newY))&&(!isPosEmpty(currX, currY, pos))) {      //moving hero if there is anyone to be moved and any space on the destination
        fields_[newY][newX].addBeing(fields_[currY][currX].getHero(pos));
        fields_[currY][currX].removeBeing(pos);

        //printing movement details
        std::cout << hero->getHP() << "HP Hero of tribe nr " << hero->getTribe() << " " << hero->getId() << " moved from " << currX
                  << "," << currY << " -> the " << fields_[currX][currY].getTerType() << " to " << newX << "," << newY
        << " -> the "<< fields_[newX][newY].getTerType();

        if(fields_[newX][newY].getTerType() == "desert"){      //depending on terrain, dealing damage
            std::cout<<"\nHero loses 5 HP because he's on the desert\n";
            if(hero->getHP()>5)
            hero->changeHp(-5);
            else
                std::cout<<"\nhero is about to die!\n";
        }
        if(fields_[newX][newY].getTerType() == "lake"){     //or healing
            std::cout<<"\nHero gains 5 HP because he's by the lake\n";
            hero->changeHp(5);
        }
    }//if hero doesnt move
    else std::cout << hero->getHP() << "HP Hero of tribe nr " << hero->getTribe() << " " << hero->getId() << " stayed on "
    << getX(hero) << "," << getY(hero) << " -> the " << fields_[currX][currX].getTerType();

}
void Map::cleanList() {     //deleting dead heroes from the list

    std::list<Being*>::iterator it = allHeroes_.begin();
    summary_.open(name_ + "_summary.txt", std::ios::out | std::ios::app );

    while (it != allHeroes_.end())
    {
        if (getX(*it) == -10)
        {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
            summary_ << "[*] " << (*it)->getTribe() << (*it)->getId() << "\t" << (*it)->getName() << " || kills: " << (*it)->getKills() << std::endl;
            (*it)->destroy();
            it = allHeroes_.erase(it);
        }
        else it++;
    }

/*
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

*/
summary_.close();
}
int Map::bCheck(int where) {    //checking whether action isn't trying to reach outside map

    if(where >= mapSize_)
        where = mapSize_-1;
    if(where < 0)
        where = 0;
    return where;

}


int Map::getMapSize() {

    return mapSize_*mapSize_;

}
int Map::getX(Being* hero) {    //seeking trough an entire map to find certain hero, and return its coords

    for(int i=0; i<mapSize_;i++){
        for(int j=0; j<mapSize_; j++){
            if(fields_[i][j].getHero(0)!=nullptr)
                if(fields_[i][j].getHero(0)->getId() == hero -> getId()) return j;
            if(fields_[i][j].getHero(1)!=nullptr)
                if(fields_[i][j].getHero(1)->getId() == hero -> getId() ) return j;
        }
    }
    return -10;     //he dead :(

}
int Map::getY(Being* hero) {

    for(int i=0; i<mapSize_;i++){   //same here
        for(int j=0; j<mapSize_; j++){
            if(fields_[i][j].getHero(0)!=nullptr)
                if(fields_[i][j].getHero(0)->getId() == hero -> getId()) return i;
            if(fields_[i][j].getHero(1)!=nullptr)
                if(fields_[i][j].getHero(1)->getId() == hero -> getId() ) return i;
        }
    }
    return -10;

}
int Map::getPos(Being* hero) {      //seeking trough an entire map to find certain hero, and return its position on the field

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
int Map::heroesOnMap() {
    int number = 0;
    for(auto hero: allHeroes_){
        if(getX(hero) != -10)
            number ++;
    }
    return number;
}
bool Map::getStatus(){
    return isFinished_;
}

void Map::move(Being* hero, int moveDirection) {    //movement section

    int xWhereToGo = -1;
    int yWhereToGo = -1;
    int verChange = 0;
    int horChange = 0;

    //seeking for interaction
    seekForInteraction(getX(hero), getY(hero), getPos(hero), hero->getSpeed(), &xWhereToGo, &yWhereToGo);

    if((xWhereToGo == -1) && (yWhereToGo == -1)){   //if there is no friendly or enemy unit

        int speed = hero->getSpeed();

        //changing heroes speed depending on terrain
        if( (hero->getId()[0]=='S') && (fields_[getX(hero)][getY(hero)].getTerType() == "forest") )
            speed = speed + 2;

        if( (hero->getId()[0]=='V') && (fields_[getX(hero)][getY(hero)].getTerType() == "lake") )
            speed = speed + 2;

        if( (hero->getId()[0]=='K') && (fields_[getX(hero)][getY(hero)].getTerType() == "mountains") )
            speed = speed + 1;

        switch (moveDirection) {    //drawing where to go
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
    else{      //go towards potential interaction
        horChange = xWhereToGo - getX(hero);
        verChange = yWhereToGo - getY(hero);
    }

    changePos(hero, verChange, horChange);

}
    void Map::encounter(Field & field, int startingPos){    //interaction with other heroes

    int attackMod = 1;
    int dmgMod = 1;

    //setting attack modificators
    if((field.getHero(startingPos)->getId()[0]=='S')&&(field.getTerType() == "forest")){
        attackMod = 2;
        dmgMod = 1;
    }

    if((field.getHero(startingPos)->getId()[0]=='V')&&(field.getTerType() == "lake")){
        attackMod = 1;
        dmgMod = 2;
    }

    if((field.getHero(startingPos)->getId()[0]=='N')&&(field.getTerType() == "plain")){
        attackMod = 2;
        dmgMod = 2;
    }

    if(field.getHero(0)->getTribe() != field.getHero(1)->getTribe()) {  //interaction with enemy unit
        if (startingPos == 0) {
        //mutual dealing damage and printing fight details
            field.getHero(1) -> changeHp(-attackMod * (field.getHero(0)->getTotalAP() - field.getHero(1) -> getDefense()));
            std::cout << "\tHero -> " << field.getHero(0)->getId() << " attacked " << field.getHero(1)->getId() << " with " << field.getHero(0)->findWeapon() <<
                      " for " << attackMod * (field.getHero(0)->getTotalAP() - field.getHero(1) -> getDefense()) << " hp\n";

            if (field.getHero(1)->isAlive()) {
                field.getHero(0) -> changeHp(-dmgMod * (3 * (field.getHero(1)->getTotalAP() / 4) - field.getHero(0)->getDefense()));
                std::cout << "Hero -> " << field.getHero(1)->getId() << " attacked back " << field.getHero(0)->getId() << " with " << field.getHero(1)->findWeapon() <<
                          " for " << dmgMod * (3 * (field.getHero(1)->getTotalAP() / 4) - field.getHero(0)->getDefense()) << " hp\n\n";
            }

        } else {    //same thing here
            field.getHero(0)->changeHp(-attackMod * (field.getHero(1)->getTotalAP() - field.getHero(0) -> getDefense()));
            std::cout << "\tHero -> " << field.getHero(1)->getId() << " attacked " << field.getHero(0)->getId() << " with " << field.getHero(1)->findWeapon() <<
                      " for " << attackMod * (field.getHero(1)->getTotalAP() - field.getHero(0) -> getDefense()) << " hp\n";

            if (field.getHero(0)->isAlive()) {
                field.getHero(1)->changeHp(-dmgMod * (3 * (field.getHero(0)->getTotalAP() / 4) - field.getHero(1)->getDefense()));
                std::cout << "Hero -> " << field.getHero(0)->getId() << " attacked back " << field.getHero(1)->getId() << " with " << field.getHero(0)->findWeapon() <<
                          " for " << dmgMod * (3 * (field.getHero(0)->getTotalAP() / 4) - field.getHero(1)->getDefense()) << " hp\n\n";
            }
        }

        if (!(field.getHero(0)->isAlive())){    //kill counters and removing heroes
            field.removeBeing(0);
            addTribeKill(field.getHero(1)->getTribe());
            field.getHero(1)->addKill();
        }

        if (!(field.getHero(1)->isAlive())){    //same here
            field.removeBeing(1);
            addTribeKill(field.getHero(0)->getTribe());
            field.getHero(0)->addKill();
        }
    }
    else{   //interaction with friendly unit
        if (startingPos == 0) {
            field.getHero(0)->changeHp(10);
            std::cout << "\tHero -> " << field.getHero(0)->getId() << " got healed (10hp)\n\n";
        } else {
            field.getHero(1)->changeHp(10);
            std::cout << "\tHero -> " << field.getHero(1)->getId() << " got healed (10hp)\n\n";
        }
    }

}
void Map::iteration()   //iteration
{
    srand(time(nullptr));

    for(auto & hero : allHeroes_) {

        goToXY(0,21);

        if(getX(hero)!=-10) {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);

            std::cout << "\n\nTurn of: " << hero->getId() << " ! " << hero->getHP() << "\n\n";
            int movement = rand() % 8;

            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);

            move(hero, movement);

            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
            
            if(getX(hero)!= -10) {
                if (isFieldFull(getX(hero), getY(hero))) {
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
                    std::cout << "\nENCOUNTER!!!!";
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
                    encounter(fields_[getY(hero)][getX(hero)], getPos(hero));
                }
                if(getX(hero)!= -10) {
                    getItems(fields_[getX(hero)][getY(hero)], hero);
                    hero->useTmpItems();
                    hero->printBackpack();
                }
            }

            goToXY(0,1);

            #ifdef USEROUTPUT
            show();
            Sleep(1000);
            #endif

            clearScreen(31,107);
        }
    }
    iterationCount_++;
    cleanList();

}
void Map::seekForInteraction(int yPos, int xPos, int pos, int howFarIllGo, int * xWhereToGo, int * yWhereToGo) {
//tiny movement mainEngine
    int xFriendly = -1;
    int yFriendly = -1;

    int xEnemy = -1;
    int yEnemy = -1;

    int enemyHp;
    int myHp = fields_[xPos][yPos].getHero(pos)->getHP();

    bool wannaHeal = false;//if hero is low hp he prefers to heal himself

    if (myHp < 50)
        wannaHeal = true;

    //looking for any enemy or friendly in heroes move range
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
    } else {    //if hero doesnt wanna heal or there is no friendly he chooses to fight enemy (only if enemy has less or equal hp than hero)
        if ((xEnemy != -1) && (yEnemy != -1)) {
            if ((enemyHp<=myHp) && ((xEnemy != xPos) || (yEnemy != yPos))) {
                *xWhereToGo = yEnemy;
                *yWhereToGo = xEnemy;
            }
        } else {    //if there is no enemy hero tries to at least heal himself
            if ((xFriendly != -1) && (yFriendly != -1)) {
                if (!wannaHeal && ((xFriendly != xPos) || (yFriendly != yPos))) {
                    *xWhereToGo = yFriendly;
                    *yWhereToGo = xFriendly;
                }
            }
        }
    }

}
void Map::generateSummary() {
    int victoriousTribe;
    summary_.open(name_ + "_summary.txt", std::ios::out | std::ios::app );

    summary_ << std::endl;
    for(int i=0; i<4; i++) {
        summary_ << "Tribe number " << i << " kills: " << getTribeKills(i) << std::endl;
        std::cout << "Tribe number " << i << " kills: " << getTribeKills(i) << std::endl;
    }
    summary_ << std::endl;
    std::cout << std::endl;


    for(int i=0; i<4; i++){
        if(isTribeAlive(i)){
            summary_ << std::endl << "\t\tTribe number " << i << " Has won" << std::endl << std::endl;
            std::cout << std::endl << "\t\tTribe number " << i << " Has won" << std::endl << std::endl;
            victoriousTribe = i;
        }
    }

    summary_.close();
    generateKillList(victoriousTribe);
}


void Map::generateKillList(int tribeName) {  //printing entire list of tribe that has won (only alive heroes)

    summary_.open(name_ + "_summary.txt", std::ios::out | std::ios::app );
    while(!allHeroes_.empty()){

        if(allHeroes_.front()->getTribe() == tribeName){
            std::cout << "ID: " << allHeroes_.front()->getId();
            std::cout << ", HP: " << allHeroes_.front()->getHP();
            std::cout << ", Name: " << allHeroes_.front()->getName();
            std::cout << ", Kill counter: " << allHeroes_.front()->getKills();
            std::cout << std::endl;
            summary_ << "ID: " << allHeroes_.front()->getId();
            summary_ << ", HP: " << allHeroes_.front()->getHP();
            summary_ << ", Name: " << allHeroes_.front()->getName();
            summary_ << ", Kill counter: " << allHeroes_.front()->getKills();
            summary_ << std::endl;
        }

        allHeroes_.pop_front();

    }

    summary_.close();

}
void Map::show() {  //printing map

    int height = 0;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);

    /*for (Being* n : allHeroes_) {
        std::cout << n->getId() << "\t" << n->getItemsQt() << std::endl;
    }*/
    std::cout << heroesOnMap();
    std::cout << "                                            Game Map\n";
    std::cout << "===========================================================================================================\n";
    std::cout << "||     0         1         2         3         4         5         6         7         8         9       ||\n";
    for(auto & field : fields_){
        std::cout << "||";
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
void Map::goToXY(int x, int y){
    COORD pos;
    pos.X = x;
    pos.Y = y;

    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}
void Map::clearScreen(int lines, int characters){

    for(int it = 0; it < lines; it++){
        for(int it2 = 0; it2 < characters; it2++){
            std::cout << " ";
        }
        std::cout << std::endl;
    }
}



bool Map::isFieldFull(int xPos, int yPos) {

    return !(fields_[yPos] [xPos].isSpace());

}
bool Map::isPosEmpty(int xPos, int yPos, int pos) {

    return (fields_[yPos] [xPos].isPosEmpty(pos));

}

int Map::numOfTribes() {    //how many tribes there are

    int tribesTab[4];
    tribesTab[0] = 0;
    tribesTab[1] = 0;
    tribesTab[2] = 0;
    tribesTab[3] = 0;

    for(auto & hero: allHeroes_){
        tribesTab[hero->getTribe()]++;
    }

    int tribesNum = 4;

    if(tribesTab[0] == 0)
        tribesNum --;
    if(tribesTab[1] == 0)
        tribesNum --;
    if(tribesTab[2] == 0)
        tribesNum --;
    if(tribesTab[3] == 0)
        tribesNum --;

    return tribesNum;
}

bool Map::isTribeAlive(int tribeNumber) {   //checking whether exact tribe is alive

    for(auto & hero: allHeroes_){
        if( hero->getTribe() == tribeNumber)
            return true;
    }
    return false;
}

void Map::addTribeKill(int tribeNumber) {
    tribeKills[tribeNumber]++;

}

int Map::getTribeKills(int tribeNumber) {
    return tribeKills[tribeNumber];
}

void Map::deactivateMap() {
    isFinished_ = true;
}
