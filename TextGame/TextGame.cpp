// TextGame.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Room.h"
#include "program.h"


int main()
{
    std::cout << "Hello World!\n";

    while (1) {
        Program program;
        program.run();
    }

    return 0;
}