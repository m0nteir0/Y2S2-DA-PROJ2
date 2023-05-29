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
 * 1 -  toy graphs
 * 2 -  real world graphs
 *
 * dentro do mesmo menu:
 * toy graphs:
 * 1 - shippings,2 - stadiums,3 - tourism  -> readToyData(path file)
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

Interface::Interface() : d_(Data()) {}

/**
 * Função imprime o menu inicial que permite ao utilizador escolher entre as opções: ler ficheiros, ver créditos ou sair do programa.
 *
 * COMPLEXIDADE: O(n).
 */
void Interface::welcomePage() {
    string input;
    while (true) {
        cout << endl << "=========WELCOME PAGE=========" << endl;
        cout << endl << "Options:\n\t1 - Read files\n\t2 - Credits\n\te - Exit" << endl;
        cout << "Choose option:  ";
        cout << endl;
        getline(cin, input);
        if (input.size() > 1) {
            cout << endl << "Please, only type one of the characters in the options described above." << endl;
        } else {
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
    d_.getG().clearGraph();
    cout << endl << "=========READ FILES=========" << endl;
    cout << endl;
    cout << "Which files do you want to read?" << endl;
    cout << endl
         << "Options:\n\t1 - Toy graphs\n\t2 - Real world graphs\n\t3 - Fully connected graphs\n\tb - Back\n\te - Exit"
         << endl;

    string input;

    while (true) {
        cout << "Choose option: ";
        cout << endl;
        getline(cin, input);
        if (input.size() > 1) {
            cout << endl << "Please, only type one of the characters in the options described above." << endl;
        } else {
            string input2;
            switch (input[0]) {
                case ('1'):
                    cout << endl << "Choose the topic of the graph you want to analyse.\n\n"
                         << endl;
                    cout << endl << "Options:\n\t1 - Shippings\n\t2 - Stadiums\n\t3 - Tourism\n\tb - back\n\te - Exit"
                         << endl;

                    while (true) {
                        cout << "Choose option:  ";
                        cout << endl;
                        getline(cin, input2);

                        if (input2.size() > 1) {
                            cout << endl << "Please, only type one of the characters in the options described above."
                                 << endl;
                        } else {
                            clock_t begin_time = 0;
                            switch (input2[0]) {
                                case ('1'):
                                    cout << "---------------------------------" << endl;
                                    cout << "EXECUTION TIMES:" << endl;
                                    begin_time = clock();
                                    d_.readToyData("../data/Project2Graphs/Toy-Graphs/shipping.csv");
                                    cout << "Total time:" << float(clock() - begin_time) / CLOCKS_PER_SEC << "s"
                                         << endl;
                                    // call to algorithm menu
                                    if (mainMenu());
                                    return false;
                                case ('2'):
                                    cout << "---------------------------------" << endl;
                                    cout << "EXECUTION TIMES:" << endl;
                                    begin_time = clock();
                                    d_.readToyData("../data/Project2Graphs/Toy-Graphs/stadiums.csv");
                                    cout << "Total time:" << float(clock() - begin_time) / CLOCKS_PER_SEC << "s"
                                         << endl;
                                    // call to algorithm menu
                                    return false;
                                case ('3'):
                                    cout << "---------------------------------" << endl;
                                    cout << "EXECUTION TIMES:" << endl;
                                    begin_time = clock();
                                    d_.readToyData("../data/Project2Graphs/Toy-Graphs/tourism.csv");
                                    cout << "Total time:" << float(clock() - begin_time) / CLOCKS_PER_SEC << "s"
                                         << endl;
                                    // call to algorithm menu
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
                    return false; //nunca vai chegar aqui

                case ('2'):
                    cout << endl << "Choose the graph you want to analyse.\n\n"
                         << endl;
                    cout << endl << "Options:\n\t1 - Graph 1\n\t2 - Graph 2\n\t3 - Graph 3\n\tb - back\n\te - Exit" << endl;

                    while (true) {
                        cout << "Choose option:  " << endl;
                        getline(cin, input2);

                        if (input.size() > 1) {
                            cout << endl << "Please, only type one of the characters in the options described above."
                                 << endl;
                        } else {
                            clock_t begin_time = 0;
                            switch (input2[0]) {
                                case ('1'):
                                    cout << "---------------------------------" << endl;
                                    cout << "EXECUTION TIMES:" << endl;
                                    begin_time = clock();
                                    d_.readRealData("../data/Project2Graphs/Real-world Graphs/graph1");
                                    cout << "Total time:" << float(clock() - begin_time) / CLOCKS_PER_SEC << "s"
                                         << endl;
                                    // call to algorithm menu
                                    return false;
                                case ('2'):
                                    cout << "---------------------------------" << endl;
                                    cout << "EXECUTION TIMES:" << endl;
                                    begin_time = clock();
                                    d_.readRealData("../data/Project2Graphs/Real-world Graphs/graph2");
                                    cout << "Total time:" << float(clock() - begin_time) / CLOCKS_PER_SEC << "s"
                                         << endl;
                                    // call to algorithm menu
                                    return false;
                                case ('3'):
                                    cout << "---------------------------------" << endl;
                                    cout << "EXECUTION TIMES:" << endl;
                                    begin_time = clock();
                                    d_.readRealData("../data/Project2Graphs/Real-world Graphs/graph3");
                                    cout << "Total time:" << float(clock() - begin_time) / CLOCKS_PER_SEC << "s"
                                         << endl;
                                    // call to algorithm menu
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
                case ('3'):
                    cout << endl
                         << "Choose the number of vertexes of the fully connected graph you want to analyse.\n\n"
                         << endl;
                    cout << endl << "Options:\n\t1 - 25 vertexes\n\t2 - 50 vertexes\n\t3 - 75 vertexes"
                         << "\n\t4 - 100 vertexes\n\t5 - 200 vertexes\n\t6 - 300 vertexes"
                         << "\n\t7 - 400 vertexes\n\t8 - 500 vertexes\n\t9 - 600 vertexes"
                         << "\n\t10 - 700 vertexes\n\t11 -  800 vertexes\n\t12 -  900 vertexes"
                         << "\n\tb - back\n\te - Exit" << endl;

                    while (true) {
                        cout << "Choose option:  " << endl;
                        getline(cin, input2);

                        vector<int> options = {25, 50, 75, 100, 200, 300, 400, 500, 600, 700, 800, 900};
                        if (input2 == "b") return false;
                        else if (input2 == "e") {
                            cout << endl << "Exiting program..." << endl;
                            return true;
                        } else {
                            int option;
                            try {
                                option = stoi(input2);
                            }
                            catch (invalid_argument &e) {
                                cout << endl << "Not a valid option" << endl;
                                continue;
                            }
                            if (option > 0 && option <= 12) {
                                cout << "---------------------------------" << endl;
                                cout << "EXECUTION TIMES:" << endl;
                                const clock_t begin_time = clock();
                                int n_vertexes = options[option - 1];
                                d_.readFullyConnectedData(
                                        "../data/Project2Graphs/Extra_Fully_Connected_Graphs/edges_" +
                                        to_string(n_vertexes) + ".csv");
                                cout << "Total time:" << float(clock() - begin_time) / CLOCKS_PER_SEC << "s"
                                     << endl;
                                // call to algorithm menu
                                return false;
                            }
                            else {
                                cout << endl << "Please, only choose one of the options described above." << endl;
                            }
                        }
                    }

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


//main menu devia ver "permissões" dos diferentes tipos de graph. P.ex Real-World não pode ser corrido pelo nosso alg
/**
 * Função imprime o menu principal do programa e permite ir para os outros "sub"-menus, com as funcionalidades específicas.
 *
 * COMPLEXIDADE: O(n).
 */
bool Interface::mainMenu() {
    while (true) {
        cout << endl << "=========ALGORITHM MENU=========" << endl;
        cout << endl;

        cout << "I want to get informations regarding:" << endl;
        cout << endl
             << "Options:\n\t1 - Brute-Force/Backtracking Algorithm [T2.1]\n\t2 - Triangular Approximation Heuristic [T2.2]\n\t3 - Other Heuristic [T2.3]\n\tb - Back\n\te - Exit"
             << endl;
        string input;
        cout << "Choose option:  ";
        cout << endl;
        getline(cin, input);
        if (input.size() > 1) {
            cout << endl << "Please, only type one of the characters in the options described above." << endl;
        } else {

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


bool Interface::credits() const {
    cout << endl << "=========CREDITS=========" << endl;
    cout << endl;
    cout << "Made by:" << endl;
    cout << "Tomas Gaspar, up202108828" << endl;
    cout << "Guilherme Monteiro, up202108668" << endl;
    cout << "Sofia Sa, up202108676" << endl;
    cout << endl << endl << "Options:\n\tb - Back\n\te - Exit" << endl;
    string input;
    while (true) {
        cout << "Choose option:  ";
        cout << endl;
        getline(cin, input);
        if (input.size() > 1) {
            cout << endl << "Please, only type one of the characters in the options described above." << endl;
        } else {

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

