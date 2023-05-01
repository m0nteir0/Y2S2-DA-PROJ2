//
// Created by Guilherme Monteiro on 01/05/2023.
//

#include "Data.h"

bool Data::readToyData(string filename) {
    ifstream input(filename);
    if (input.is_open()) {
        string l;
        getline(input, l);
        string = ;
        while (getline(input, l)) {
            stringstream iss(l);
            getline(iss, name, ',');


        }
        input.close();
        return true;
    } else {
        cout << "Unable to open file";
        return false;
    }
}
