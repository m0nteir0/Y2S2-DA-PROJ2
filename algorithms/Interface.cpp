#include "Interface.h"
#include <iostream>
#include <iomanip>

using namespace std;


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
        cout << endl << "----> Welcome to our DA 2nd Project! Here, we will show you different ways we handled Travelling Salesperson Problem.";
        cout << endl << "----> Some techniques are more efficient, others more accurate... Let's see! \u1F600 " << endl;
        cout << "\t_________________";
        cout << endl << "\t| 1 - Read files\t|\n\t| 2 - Credits\t|\n\t| e - Exit\t|" << endl;
        cout << "\t_________________";
        cout << "\nChoose option:  ";
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
    string input;

    while (true) {
        d_.getG().clearGraph();
        cout << endl << "=========READ FILES=========" << endl;
        cout << endl;
        cout << "Which files do you want to read?" << endl;
        cout << endl
             << "\t1 - Toy graphs\n\t2 - Real world graphs\n\t3 - Fully connected graphs\n\tb - Back\n\te - Exit"
             << endl;

        cout << "\nChoose option: ";
        cout << endl;
        getline(cin, input);
        if (input.size() > 1) {
            cout << endl << "Please, only type one of the characters in the options described above." << endl;
        } else {
            string input2;
            switch (input[0]) {
                case ('1'): {
                    cout << endl <<"---------------------------------" << endl;
                    cout << "Choose the topic of the graph you want to analyse.\n\n";
                    cout << endl << "\t1 - Shippings\n\t2 - Stadiums\n\t3 - Tourism\n\tb - back\n\te - Exit"
                         << endl;

                    while (true) {
                        cout << "\nChoose option:  ";
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
                                    d_.readToyData("../data/Toy-Graphs/shipping.csv");
                                    cout << "Total time:" << float(clock() - begin_time) / CLOCKS_PER_SEC << "s"
                                         << endl;
                                    cout << "---------------------------------" << endl;

                                    if (mainMenu(true, false))
                                        return true;
                                    break;
                                    //return false;
                                case ('2'):
                                    cout << "---------------------------------" << endl;
                                    cout << "EXECUTION TIMES:" << endl;
                                    begin_time = clock();
                                    d_.readToyData("../data/Toy-Graphs/stadiums.csv");
                                    cout << "Total time:" << float(clock() - begin_time) / CLOCKS_PER_SEC << "s"
                                         << endl;
                                    cout << "---------------------------------" << endl;
                                    if (mainMenu(true,true))
                                        return true;
                                    break;
                                case ('3'):
                                    cout << "---------------------------------" << endl;
                                    cout << "EXECUTION TIMES:" << endl;
                                    begin_time = clock();
                                    d_.readToyData("../data/Toy-Graphs/tourism.csv");
                                    cout << "Total time:" << float(clock() - begin_time) / CLOCKS_PER_SEC << "s"
                                         << endl;
                                    cout << "---------------------------------" << endl;
                                    if (mainMenu(true,true))
                                        return true;
                                    break;
                                case 'b':
                                    break;
                                case 'e':
                                    cout << endl << "Exiting program..." << endl;
                                    return true;
                                default:
                                    cout << endl << "Not a valid option" << endl;
                            }
                        }
                        break;
                    }
                    break;
                }
                case ('2'): {
                    cout << endl << "Choose the graph you want to analyse.\n\n"
                         << endl;
                    cout << endl << "\t1 - Graph 1\n\t2 - Graph 2\n\t3 - Graph 3\n\tb - back\n\te - Exit"
                         << endl;

                    while (true) {
                        cout << "\nChoose option:  " << endl;
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
                                    d_.readRealData("../data/Real-World-Graphs/graph1");
                                    cout << "Total time:" << float(clock() - begin_time) / CLOCKS_PER_SEC << "s"
                                         << endl;
                                    cout << "---------------------------------" << endl;
                                    if (mainMenu(false,true))
                                        return true;
                                    break;
                                case ('2'):
                                    cout << "---------------------------------" << endl;
                                    cout << "EXECUTION TIMES:" << endl;
                                    begin_time = clock();
                                    d_.readRealData("../data/Real-World-Graphs/graph2");
                                    cout << "Total time:" << float(clock() - begin_time) / CLOCKS_PER_SEC << "s"
                                         << endl;
                                    cout << "---------------------------------" << endl;
                                    if (mainMenu(false,false))
                                        return true;
                                    break;
                                case ('3'):
                                    cout << "---------------------------------" << endl;
                                    cout << "EXECUTION TIMES:" << endl;
                                    begin_time = clock();
                                    d_.readRealData("../data/Real-World-Graphs/graph3");
                                    cout << "Total time:" << float(clock() - begin_time) / CLOCKS_PER_SEC << "s"
                                         << endl;
                                    cout << "---------------------------------" << endl;
                                    if (mainMenu(false,false))
                                        return true;
                                    break;
                                case ('b'):
                                    break;
                                case ('e'):
                                    cout << endl << "Exiting program..." << endl;
                                    return true;
                                default:
                                    cout << endl << "Not a valid option" << endl;
                            }
                            break;
                        }
                    }
                    break;
                }
                case ('3'): {
                    cout << endl
                         << "Choose the number of vertexes of the fully connected graph you want to analyse.\n\n"
                         << endl;
                    cout << endl << "\t1 - 25 vertexes\n\t2 - 50 vertexes\n\t3 - 75 vertexes"
                         << "\n\t4 - 100 vertexes\n\t5 - 200 vertexes\n\t6 - 300 vertexes"
                         << "\n\t7 - 400 vertexes\n\t8 - 500 vertexes\n\t9 - 600 vertexes"
                         << "\n\t10 - 700 vertexes\n\t11 -  800 vertexes\n\t12 -  900 vertexes"
                         << "\n\tb - back\n\te - Exit" << endl;

                    while (true) {
                        cout << "\nChoose option:  " << endl;
                        getline(cin, input2);

                        vector<int> options = {25, 50, 75, 100, 200, 300, 400, 500, 600, 700, 800, 900};
                        if (input2 == "b")
                            break;
                            //return false;
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
                                        "../data/Extra_Fully_Connected_Graphs/edges_" +
                                        to_string(n_vertexes) + ".csv");
                                cout << "Total time:" << float(clock() - begin_time) / CLOCKS_PER_SEC << "s"
                                     << endl;
                                cout << "---------------------------------" << endl;
                                if (mainMenu(false,true))
                                    return true;
                                break;
                            } else {
                                cout << endl << "Please, only choose one of the options described above." << endl;
                            }
                            break;
                        }
                    }
                    break;
                }
                case ('b'):
                    break;
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
bool Interface::mainMenu(bool isSmall, bool isComplete) {
    while (true) {
        cout << endl << "=========ALGORITHM MENU=========" << endl;
        cout << endl;

        cout << "I want to get informations regarding:" << endl;
        cout << endl
             << "\t1 - Brute-Force/Backtracking Algorithm [T2.1]\n\t2 - Triangular Approximation Heuristic [T2.2]\n\t3 - Our Heuristic (Nearest Neighbour + 2-opt) [T2.3]\n\tb - Back\n\te - Exit"
             << endl;
        string input;
        cout << "\nChoose option:  ";
        cout << endl;
        getline(cin, input);
        if (input.size() > 1) {
            cout << endl << "Please, only type one of the characters in the options described above." << endl;
        } else {
            double total_distance;
            clock_t begin_time;
            switch (input[0]) {
                case ('1'): {
                    if (!isSmall) {
                        cout << endl << "This algorithm is only available for small graphs." << endl;
                        break;
                    }
                    unsigned int n = d_.getG().getNumVertex();
                    int a[n];
                    cout << endl << endl << "---------------------------------" << endl;
                    cout << "BACKTRACKING ALGORITHM" << endl;
                    begin_time = clock();
                    total_distance = d_.tspBT(n, a);
                    cout << "Execution time: " << float(clock() - begin_time) / CLOCKS_PER_SEC << "s" << endl;
                    cout << "Path: ";
                    for (int i = 0; i < n; i++) {
                        cout << a[i] << " -> ";
                    }
                    cout << 0 << endl;
                    cout << "Total distance: " << total_distance << endl;
                    cout << "---------------------------------" << endl;
                    if (displayPage())
                        return true;
                    break;
                }
                case ('2'): {
                    if (isSmall && !isComplete) {
                        cout << endl << "This algorithm is not available for this graph." << endl;
                        break;
                    }
                    vector<Vertex *> path;
                    cout << endl << endl << "---------------------------------" << endl;
                    cout << "TRIANGULAR APPROXIMATION ALGORITHM" << endl;
                    begin_time = clock();
                    total_distance = d_.tspTriangle(path);
                    cout << "Execution time: " << float(clock() - begin_time) / CLOCKS_PER_SEC << "s" << endl;
                    cout << "Path: ";
                    for (int i = 0; i < path.size() - 1; i++) {
                        cout << path[i]->getId() << " -> ";
                    }
                    cout << path.back()->getId() << endl;
                    cout << "Total distance: " << total_distance << endl;
                    cout << "---------------------------------" << endl;
                    cout << endl;
                    cout << "Do you want to see the optimized results after applying a 2-opt algorithm? (y/n)" << endl;
                    string input;
                    getline(cin, input);
                    if (input == "y") {
                        cout << "Please write the maximum number of iterations: " << endl;
                        getline(cin, input);
                        int max_iter = 0;
                        try {
                            max_iter = stoi(input);
                        }
                        catch (invalid_argument &e) {
                            cout << endl << "Not a valid number" << endl;

                        }
                        if (max_iter > 0) {
                            cout << endl << endl << "---------------------------------" << endl;
                            cout << "2-OPT ALGORITHM" << endl;
                            begin_time = clock();
                            total_distance = d_.tsp2opt(path, max_iter);
                            cout << "Execution time: " << float(clock() - begin_time) / CLOCKS_PER_SEC << "s" << endl;
                            cout << "Path: ";
                            for (int i = 0; i < path.size() - 1; i++) {
                                cout << path[i]->getId() << " -> ";
                            }
                            cout << path.back()->getId() << endl;
                            cout << "Total distance: " << total_distance << endl;
                            cout << "---------------------------------" << endl;
                        }
                    }

                    if (displayPage())
                        return true;
                    break;
                }

                case ('3'): {
                    if (!isComplete) {
                        cout << endl << "This algorithm is not available for this graph." << endl;
                        break;
                    }
                    vector<Vertex*> path;
                    cout << endl << endl << "---------------------------------" << endl;
                    cout << "NEAREST NEIGHBOR ALGORITHM" << endl;
                    begin_time = clock();
                    path =  d_.tspNearestNeighbour();
                    cout << "Execution time: " << float(clock() - begin_time) / CLOCKS_PER_SEC << "s" << endl;
                    cout << "Path: ";
                    for (int i = 0; i < path.size()-1; i++) {
                        cout << path[i]->getId() << " -> ";
                    }
                    cout << path.back()->getId() << endl;
                    total_distance = d_.getPathDist(path);
                    cout << "Total distance: " << total_distance << endl;
                    cout << "---------------------------------" << endl;
                    cout << endl;
                    cout << "Do you want to see the optimized results after applying a 2-opt algorithm? (y/n)" << endl;
                    string input;
                    getline(cin, input);
                    if (input == "y") {
                        cout << "Please write the maximum number of iterations: " << endl;
                        getline(cin, input);
                        int max_iter = 0;
                        try {
                            max_iter = stoi(input);
                        }
                        catch (invalid_argument &e) {
                            cout << endl << "Not a valid number" << endl;

                        }
                        if (max_iter > 0) {
                            cout << endl << endl << "---------------------------------" << endl;
                            cout << "2-OPT ALGORITHM" << endl;
                            begin_time = clock();
                            total_distance = d_.tsp2opt(path, max_iter);
                            cout << "Execution time: " << float(clock() - begin_time) / CLOCKS_PER_SEC << "s" << endl;
                            cout << "Path: ";
                            for (int i = 0; i < path.size() - 1; i++) {
                                cout << path[i]->getId() << " -> ";
                            }
                            cout << path.back()->getId() << endl;
                            cout << "Total distance: " << total_distance << endl;
                            cout << "---------------------------------" << endl;
                        }
                    }
                    if (displayPage())
                        return true;
                    break;
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

bool Interface::displayPage() const {
    cout << endl << endl;
    cout << endl << "\tb-Back\n\te-Exit"<<endl;
    string input;
    while (true){
        cout << "\nChoose option:" << endl;
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



bool Interface::credits() const {
    cout << endl << "=========CREDITS=========" << endl;
    cout << endl;
    cout << "Made by:" << endl;
    cout << "Tomas Gaspar, up202108828" << endl;
    cout << "Guilherme Monteiro, up202108668" << endl;
    cout << "Sofia Sa, up202108676" << endl;
    cout << endl << endl << "\tb - Back\n\te - Exit" << endl;
    string input;
    while (true) {
        cout << "\nChoose option:  ";
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

