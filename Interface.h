#ifndef DA_PROJECT2_INTERFACE_H
#define DA_PROJECT2_INTERFACE_H

#include "Data.h"

using namespace std;

class Interface {

private:
    Data d_;

public:

    Interface();
    void welcomePage();
    void mainMenu();
    bool readFiles();

    bool credits() const;

};


#endif //DA_PROJECT2_INTERFACE_H
