//
// Created by Kacper Aleks on 14.06.2021.
//

#ifndef PO_COUT_H
#define PO_COUT_H

#include <map>
#include <windows.h>

enum class Colors{
    white,
    red,
    cyan,
    blue,
    orange,
    yellow,
    green,
    grey,
};

void changeColor(Colors colorId);

#endif //PO_COUT_H
