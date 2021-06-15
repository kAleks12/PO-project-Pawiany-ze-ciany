#ifndef MAP_H_KNIGHTS_H
#define MAP_H_KNIGHTS_H

#include "Being.h"

class Knight: public Being{
    //ATTRIBUTES
    static int numOfKnightsCreated_;

public:
    //CONSTRUCTORS AND DESTRUCTOR
    Knight();
    explicit Knight(std::string, int, std::mt19937&);
    virtual ~Knight();

    //PRINTERS
    void show() override;
    void destroy() override;
};

#endif //MAP_H_KNIGHTS_H