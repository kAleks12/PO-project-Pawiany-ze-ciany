//
// Created by Michał on 15.04.2021.
//

#ifndef PO_VIKING_H
#define PO_VIKING_H

#include "Being.h"

class Viking: public Being {
private:
    //ATTRIBUTES
    static int numOfVikingsCreated_;

public:
    //CONSTRUCTORS AND DESTRUCTOR
    Viking();
    explicit Viking(std::string, int, std::mt19937&);
    virtual ~Viking();

    //PRINTERS
    void show() override;
    void destroy() override;
};


#endif //PO_VIKING_H
