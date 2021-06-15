//
// Created by Kacper Aleks on 14.06.2021.
//
#include "COUT.h"

void changeColor (Colors colorId){

const std::map <Colors, int> colors {{Colors::orange,6},{Colors::white,7},{Colors::grey,8},{Colors::blue, 9}, {Colors::green, 10},{Colors::cyan, 11},{Colors::red, 12},{Colors::yellow, 14}};

SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE), colors.at(colorId) );
}

