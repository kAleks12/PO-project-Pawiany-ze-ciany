#ifndef MAP_H_SLAV_H
#define MAP_H_SLAV_H

#include "Being.h"

class Slav: public Being{
private:
    //ATTRIBUTES
    static int numOfSlavsCreated_;

public:
    //CONSTRUCTORS AND DESTRUCTOR
    Slav();
    explicit Slav(std::string, int, std::mt19937&);
    virtual ~Slav();

    //PRINTERS
    void show() override;
    void destroy() override;

};


#endif //MAP_H_SLAV_H
