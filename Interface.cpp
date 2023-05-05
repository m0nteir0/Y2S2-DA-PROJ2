#include "Interface.h"
#include <iostream>
#include <iomanip>

using namespace std;

/*
 * ESTRUTURA:
 *
 * welcomePage:
 * 1 - read files
 * 2 - credits
 * e - exit
 *
 * readFiles:
 * 1- toy graphs
 * 2- real world graphs
 *
 * dentro do mesmo menu:
 * toy graphs:
 * 1-shippings,2-stadiums,3-tourism  -> readToyData(path file)
 * real world graphs:
 * 1,2,3 -> readRealData(path folder)
 *
 *
 * mainMenu: (algorithm menu)
 * 1 - Brute-Force/Backtracking Algorithm [T2.1: 4 points]
 * 2 - Triangular Approximation Heuristic [T2.2: 4 points]
 * 3 - Other Heuristics [T2.3: 6 points]
 *
 */

Interface::Interface(): d_(Data()) {}

/**
 * Função imprime o menu inicial que permite ao utilizador escolher entre as opções: ler ficheiros, ver créditos ou sair do programa.
 *
 * COMPLEXIDADE: O(n).
 */
void Interface::welcomePage() {
    string input;
    while (true){
        cout << endl << "=========WELCOME PAGE=========" << endl;
        cout << endl << "Options:\n\t1-Read files\n\t2-Credits\n\te-Exit"<<endl;
        cout << "Choose option: ";
        getline(cin, input);
        if(input.size()>1){
            cout << endl << "Please, only type one of the characters in the options described above." << endl;
        }
        else {
            switch (input[0]) {
                case ('1'):
                    if (readFiles())
                        return;
                    /*else if (!d_.getStations().empty() && !d_.getNetwork().empty())
                        return mainMenu();*/
                    break;
                case ('2'):
                    if (credits())
                        return;
                    break;
                case ('e'):
                    cout << endl << "Exiting program..." << endl;
                    return;
                default:
                    cout << endl << "Not a valid option" << endl;
            }
        }
    }
}


/**
 * Função imprime o menu de leitura dos ficheiros, permite ao utilizador escolher entre os ficheiros "default" ou alterar os ficheiros
 *
 * COMPLEXIDADE: O(n).
 */
bool Interface::readFiles() {
    cout << endl << "=========READ FILES=========" << endl;
    cout << endl;
    cout << "Which files do you want to read?" << endl;
    cout << endl << "Options:\n\t1-Toy graphs\n\t2-Real world graphs\n\tb-Back\n\te-Exit"<<endl;

    string input, stations, network;

    while (true){
        cout << "Choose option: ";
        getline( cin, input);
        if(input.size()>1){
            cout << endl << "Please, only type one of the characters in the options described above." << endl;
        }
        else {
            string input2;
            string input3;
            switch (input[0]) {
                case ('1'):
                    cout << endl << "Choose the topic of the graphic you want to analyse.\n\n"
                         << endl;
                    cout << endl << "Options:\n\t1-Shippings\n\t2-Stadiums\n\t3-Tourism\n\tb-back\n\te-Exit" << endl;
                    ;

                    while(true){
                        cout << "Choose option: ";
                        getline( cin, input2);

                        if(input.size()>1){
                            cout << endl << "Please, only type one of the characters in the options described above." << endl;
                        }

                        else{
                            switch(input2[0]){
                                case ('1'):
                                    //d_.readToyData(DEFAULT_SHIPPINGS);
                                    //d_.readToyData(DEFAULT_SHIPPINGS);
                                    return false;
                                case ('2'):
                                    //d_.readToyData(DEFAULT_STADIUMS);
                                    //d_.readToyData(DEFAULT_STADIUMS);
                                    return false;
                                case ('3'):
                                    //d_.readToyData(DEFAULT_TOURISM);
                                    //d_.readToyData(DEFAULT_TOURISM);
                                    return false;
                                case 'b':
                                    return false;
                                case 'e':
                                    cout << endl << "Exiting program..." << endl;
                                    return true;
                                default:
                                    cout << endl << "Not a valid option" << endl;
                            }
                        }
                    }
                    return false;

                case ('2'):
                    cout << endl << "Choose the graphic you want to analyse.\n\n"
                         << endl;
                    cout << endl << "Options:\n\t1-Graph 1\n\t2-Graph 2\n\t3-Graph 3\n\tb-back\n\te-Exit" << endl;

                    while(true){
                        cout << "Choose option: ";
                        getline( cin, input3);

                        if(input.size()>1){
                            cout << endl << "Please, only type one of the characters in the options described above." << endl;
                        }

                        else{
                            switch(input3[0]){
                                case ('1'):
                                    //d_.readRealData(path);
                                    return false;
                                case ('2'):
                                    //d_.readRealData(path);
                                    return false;
                                case ('3'):
                                    //d_.readRealData(path);
                                    return false;
                                case ('b'):
                                    return false;
                                case ('e'):
                                    cout << endl << "Exiting program..." << endl;
                                    return true;
                                default:
                                    cout << endl << "Not a valid option" << endl;
                            }
                        }
                    }
                    return false;
                case ('b'):
                    return false;
                case ('e'):
                    cout << endl << "Exiting program..." << endl;
                    return true;
                default:
                    cout << endl << "Not a valid option" << endl;
            }
        }
    }
}


/**
 * Função imprime o menu principal do programa e permite ir para os outros "sub"-menus, com as funcionalidades específicas.
 *
 * COMPLEXIDADE: O(n).
 */
void Interface::mainMenu() {
    while (true){
        cout << endl << "=========ALGORITHM MENU=========" << endl;
        cout << endl;

        cout << "I want to get informations regarding:" << endl;
        cout << endl << "Options:\n\t1-Brute-Force/Backtracking Algorithm [T2.1]\n\t2-Triangular Approximation Heuristic [T2.2]\n\t3-Other Heuristics [T2.3]\n\te-Exit"<<endl;
        string input;
        cout << "Choose option: ";
        getline( cin, input);
        if(input.size()>1){
            cout << endl << "Please, only type one of the characters in the options described above." << endl;
        }
        else {

            switch (input[0]) {
                case ('1'):
                    //if (bruteTSP())
                    //    return;
                    break;
                case ('2'):
                    //if (triangleTSP())
                    //    return;
                    break;
                case ('3'):
                    //if (customedTSP())
                    //    return;
                    break;
                case ('e'):
                    cout << endl << "Exiting program..." << endl;
                    return;
                default:
                    cout << endl << "Not a valid option" << endl;
            }
        }
    }
}


bool Interface::credits() const {
    cout << endl << "=========CREDITS=========" << endl;
    cout << endl;
    cout << "Made by:" << endl;
    cout << "Tomas Gaspar, up202108828" << endl;
    cout << "Guilherme Monteiro, up202108668" << endl;
    cout << "Sofia Sa, up202108676" << endl;
    cout << endl << endl << "Options:\n\tb-Back\n\te-Exit"<< endl;
    string input;
    while (true) {
        cout << "Choose option: ";
        getline( cin, input);
        if(input.size()>1){
            cout << endl << "Please, only type one of the characters in the options described above." << endl;
        }
        else {

            switch (input[0]) {
                case ('b'):
                    return false;
                case ('e'):
                    cout << endl << "Exiting program..." << endl;
                    return true;
                default:
                    cout << endl << "Not a valid option" << endl;
            }
        }
    }
}

