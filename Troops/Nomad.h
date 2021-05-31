#ifndef MAP_H_SOUTHERN_WARRIOR_H
#define MAP_H_SOUTHERN_WARRIOR_H

#include "Being.h"

class Nomad: public Being{
private:
    static int numOfNomadsCreated_;
public:
    Nomad();
    explicit Nomad(std::string, int, std::mt19937& );
    virtual ~Nomad();

    void show() override;
    void destroy() override;
};


#endif //MAP_H_SOUTHERN_WARRIOR_H
