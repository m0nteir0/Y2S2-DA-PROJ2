#include <iostream>
#include "Data.h"
int main() {
    std::cout << "Hello, World!" << std::endl;
    Data d = Data();
    d.readToyData("../data/Project2Graphs/Toy-Graphs/tourism.csv");



    return 0;
}
