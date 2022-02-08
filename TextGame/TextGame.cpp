// TextGame.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Room.h"
#include "program.h"


int main()
{
    std::cout << "If this is your first time playing, type HELP. Good luck!" << std::endl;

    while (1) {
        Program program;
        program.run();
    }

    return 0;
}