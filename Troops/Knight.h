#ifndef MAP_H_KNIGHTS_H
#define MAP_H_KNIGHTS_H

#include "Being.h"

class Knight: public Being{
    static int numOfKnightsCreated_;
    bool isOnHorse;
public:
    Knight();
    ~Knight();
    explicit Knight(std::string, int);

    void changeStatus();
    void show() override;
    void destroy() override;
};

#endif //MAP_H_KNIGHTS_H