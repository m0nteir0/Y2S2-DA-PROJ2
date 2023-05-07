#include <iostream>
#include "Data.h"
#include "Interface.h"
int main() {
    std::cout << "Hello, World!" << std::endl;
    Data d = Data();
    //d.readToyData("../data/Project2Graphs/Toy-Graphs/tourism.csv");

    Interface i = Interface();
    i.welcomePage();

    return 0;
}
