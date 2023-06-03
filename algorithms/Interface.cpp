#include "Interface.h"
#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;


Interface::Interface() : d_(Data()) {}

void Interface::welcomePage() {
    string input;
    while (true) {
        cout << endl << "=========WELCOME PAGE=========" << endl;
        cout << endl << "----> Welcome to our DA 2nd Project! Here, we will show you different ways we handled Travelling Salesperson Problem.";
        cout << endl << "----> Some techniques are more efficient, others more accurate... Let's see! " << endl;
        cout << endl << "\t1 - Read files\n\t2 - Credits\n\te - Exit" << endl;
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
                    cout << "Choose the topic of the graph you want to analyse.\n";
                    cout << endl << "\t1 - Shippings\n\t2 - Stadiums\n\t3 - Tourism\n\tb - back\n\te - Exit"
                         << endl;

                    while (true) {
                        cout << "\nChoose option:  ";
                        cout << endl;
                        getline(cin, input2);
                        cout << endl;
                        if (input2.size() > 1) {
                            cout << endl << "Please, only type one of the characters in the options described above."
                                 << endl;
                        } else {
                            clock_t begin_time = 0;
                            switch (input2[0]) {
                                case ('1'):
                                    cout << "---------------------------------" << endl;
                                    cout << "EXECUTION TIME:" << endl;
                                    begin_time = clock();
                                    d_.readToyData("../data/Toy-Graphs/shipping.csv");
                                    cout << "Total time:" << float(clock() - begin_time) / CLOCKS_PER_SEC << "s"
                                         << endl;
                                    cout << "---------------------------------" << endl;

                                    if (mainMenu(true, false))
                                        return true;
                                    break;
                                case ('2'):
                                    cout << "---------------------------------" << endl;
                                    cout << "EXECUTION TIME:" << endl;
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
                                    cout << "EXECUTION TIME:" << endl;
                                    begin_time = clock();
                                    d_.readToyData("../data/Toy-Graphs/tourism.csv");
                                    cout << "Total time:" << float(clock() - begin_time) / CLOCKS_PER_SEC << "s"
                                         << endl;
                                    cout << "---------------------------------" << endl;
                                    if (mainMenu(true,true))
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
                        }
                        break;
                    }
                    break;
                }
                case ('2'): {
                    cout << endl << "Choose the graph you want to analyse."<< endl;
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
                                    cout << "EXECUTION TIME:" << endl;
                                    begin_time = clock();
                                    d_.readRealData("../data/Real-world Graphs/graph1");
                                    cout << "Total time:" << float(clock() - begin_time) / CLOCKS_PER_SEC << "s"
                                         << endl;
                                    cout << "---------------------------------" << endl;
                                    if (mainMenu(false,true))
                                        return true;
                                    break;
                                case ('2'):
                                    cout << "---------------------------------" << endl;
                                    cout << "EXECUTION TIME:" << endl;
                                    begin_time = clock();
                                    d_.readRealData("../data/Real-world Graphs/graph2");
                                    cout << "Total time:" << float(clock() - begin_time) / CLOCKS_PER_SEC << "s"
                                         << endl;
                                    cout << "---------------------------------" << endl;
                                    if (mainMenu(false,false))
                                        return true;
                                    break;
                                case ('3'):
                                    cout << "---------------------------------" << endl;
                                    cout << "EXECUTION TIME:" << endl;
                                    begin_time = clock();
                                    d_.readRealData("../data/Real-world Graphs/graph3");
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
                         << "Choose the number of vertexes of the fully connected graph you want to analyse."
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
                                cout << "EXECUTION TIME:" << endl;
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

bool Interface::mainMenu(bool isSmall, bool isComplete) {
    double lower_bound = 0;
    while (true) {
        cout << endl;
        cout << endl << "=========ALGORITHM MENU=========" << endl;
        cout << endl;

        cout << "Which algorithm do you want to apply?" << endl;
        cout << endl
             << "\t1 - Brute-Force/Backtracking Algorithm [T2.1]\n\t2 - Triangular Approximation Heuristic [T2.2]\n\t3 - Our Heuristic (Nearest Neighbour) [T2.3]\n\t4 - Find lower bound (MST)\n\t5 - Algorithm summary\n\tb - Back\n\te - Exit"
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
                    lower_bound = total_distance;
                    cout << "Execution time: " << float(clock() - begin_time) / CLOCKS_PER_SEC << "s" << endl;
                    cout << "Path: ";
                    for (int i = 0; i < n; i++) {
                        cout << a[i] << " -> ";
                    }
                    cout << 0 << endl;
                    cout << "Total distance: " << total_distance << endl;
                    getApproximationRatio(lower_bound, total_distance);
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
                    getApproximationRatio(lower_bound, total_distance);
                    cout << "---------------------------------" << endl;
                    cout << endl;
                    if (isComplete) {
                        if (optimization(path, "TA", lower_bound))
                            return true;
                    }
                    else if (displayPage())
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
                    getApproximationRatio(lower_bound, total_distance);
                    cout << "---------------------------------" << endl;
                    cout << endl;
                    if (optimization(path, "NN", lower_bound))
                        return true;
                    break;
                }
                case ('4'): {
                    if (isSmall) {
                        cout << endl << "You can find the optimal solution for this graph by running the backtracking algorithm." << endl;
                        break;
                    }
                    cout << endl << endl << "---------------------------------" << endl;
                    cout << "LOWER BOUND (MST)" << endl;
                    begin_time = clock();
                    lower_bound = d_.getG().prim();
                    cout << "Execution time: " << float(clock() - begin_time) / CLOCKS_PER_SEC << "s" << endl;
                    cout << "Lower bound: " << lower_bound << endl;
                    cout << "---------------------------------" << endl;
                    cout << endl;
                    if (displayPage())
                        return true;
                    break;
                }
                case ('5'): {
                    summary(isSmall, isComplete);
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
    string input;
    while (true){
        cout << endl << "\tb-Back\n\te-Exit"<<endl;
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

bool Interface::optimization(vector<Vertex*> path, string algorithm, double lower_bound) {
    string input;
    while (true){
        cout << endl;
        cout << "=========OPTIMIZATION=========" << endl;
        cout << endl << "\t1 - 2-opt\n\t2 - 3-opt\n\tb - Back\n\te - Exit"<<endl;
        cout << "\nChoose option:" << endl;
        getline(cin, input);
        if (input.size() > 1) {
            cout << endl << "Please, only type one of the characters in the options described above." << endl;
        } else {
            clock_t begin_time;
            double total_distance;
            switch (input[0]) {
                case ('1'): {
                    vector<Vertex*> path2opt = path; //copy of the path
                    cout << "Maximum number of iterations: " << endl;
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
                        cout << algorithm <<" + 2-OPT ALGORITHM (" << max_iter << ((max_iter > 1 )?" iterations)" : " iteration)") << endl;
                        begin_time = clock();
                        total_distance = d_.tsp2opt(path2opt, max_iter);
                        cout << "Execution time: " << float(clock() - begin_time) / CLOCKS_PER_SEC << "s"
                             << endl;
                        cout << "Path: ";
                        for (int i = 0; i < path2opt.size() - 1; i++) {
                            cout << path2opt[i]->getId() << " -> ";
                        }
                        cout << path2opt.back()->getId() << endl;
                        cout << "Total distance: " << total_distance << endl;
                        getApproximationRatio(lower_bound, total_distance);
                        cout << "---------------------------------" << endl;

                        if(displayPage())
                            return true;
                    }
                    break;
                }
                case ('2'): {
                    vector<Vertex*> path3opt = path; //copy of the path
                    cout << "Maximum number of iterations: " << endl;
                    getline(cin, input);
                    int max_iter = 0;
                    try {
                        max_iter = stoi(input);
                    }
                    catch (invalid_argument &e) {
                        cout << endl << "Not a valid number" << endl;
                        return false;

                    }
                    if (max_iter > 0) {
                        cout << endl << endl << "---------------------------------" << endl;
                        cout << algorithm <<" + 3-OPT ALGORITHM (" << max_iter << ((max_iter > 1 )?" iterations)" : " iteration)") << endl;
                        begin_time = clock();
                        total_distance = d_.tsp3opt(path3opt, max_iter);
                        cout << "Execution time: " << float(clock() - begin_time) / CLOCKS_PER_SEC << "s"
                             << endl;
                        cout << "Path: ";
                        for (int i = 0; i < path3opt.size() - 1; i++) {
                            cout << path3opt[i]->getId() << " -> ";
                        }
                        cout << path3opt.back()->getId() << endl;
                        cout << "Total distance: " << total_distance << endl;
                        getApproximationRatio(lower_bound, total_distance);
                        cout << "---------------------------------" << endl;

                        if(displayPage())
                            return true;
                    }
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

void Interface::getApproximationRatio(double lower_bound, double dist){
    if (lower_bound != 0) {
        double ratio = dist / lower_bound;
        cout << "Approximation: " << round(ratio * 1000.0) / 1000.0 << "x" << endl;
    }
}

void Interface::summary(bool isSmall, bool isComplete) {
    cout << endl;
    double lower_bound;
    clock_t begin_time;
    struct stat {
        string name;
        double dist;
        float time;
        double ratio;
    };
    vector<stat> stats;

    string input;
    int iterations2opt = 0;
    while (true) {
        cout << "Maximum number of iterations for 2-opt (0 if don't want to run 2-opt): " << endl;
        getline(cin, input);
        try {
            iterations2opt = stoi(input);
        }
        catch (invalid_argument &e) {
            cout << endl << "Not a valid number" << endl;
            continue;
        }
        break;
    }
    int iterations3opt = 0;
    while (true) {
        cout << "Maximum number of iterations for 3-opt (0 if don't want to run 3-opt): " << endl;
        getline(cin, input);
        try {
            iterations3opt = stoi(input);
        }
        catch (invalid_argument &e) {
            cout << endl << "Not a valid number" << endl;
            continue;
        }
        break;
    }
    cout << endl << "Running algorithms..." << endl;
    //lowerbound/backtracking
    if (isSmall) {
        cout << endl << "Backtracking algorithm is running...";
        stat s;
        unsigned int n = d_.getG().getNumVertex();
        int a[n];
        begin_time = clock();
        lower_bound = d_.tspBT(n, a);
        s = {"Backtracking", lower_bound, float(clock() - begin_time) / CLOCKS_PER_SEC, 1};
        stats.push_back(s);
        cout << "Done." << endl;
    } else {
        cout << endl << "Lower Bound algorithm is running...";
        stat s;
        begin_time = clock();
        lower_bound = d_.getG().prim();
        s = {"Lower Bound", lower_bound, float(clock() - begin_time) / CLOCKS_PER_SEC, 1};
        stats.push_back(s);
        cout << "Done." << endl;
    }
    //TA
    if (isSmall && !isComplete) {
        cout << endl << "TA algorithm not available for this graph." << endl;
    } else {
        cout << "TA algorithm is running...";
        stat s;
        vector<Vertex *> path;
        begin_time = clock();
        double total_distance = d_.tspTriangle(path);
        s = {"TA", total_distance, float(clock() - begin_time) / CLOCKS_PER_SEC, round ((total_distance / lower_bound) * 1000.0) / 1000.0};
        stats.push_back(s);
        cout << "Done." << endl;
        //2opt
        if(isComplete){
            if(iterations2opt > 0){
                cout << "TA + 2-OPT algorithm is running...";
                vector<Vertex *> path2opt = path; //copy of the path
                begin_time = clock();
                total_distance = d_.tsp2opt(path2opt, iterations2opt);
                s = {"TA + 2-OPT", total_distance, float(clock() - begin_time) / CLOCKS_PER_SEC, round ((total_distance / lower_bound) * 1000.0) / 1000.0};
                stats.push_back(s);
                cout << "Done." << endl;
            }
            if(iterations3opt > 0){
                cout << "TA + 3-OPT algorithm is running...";
                vector<Vertex *> path3opt = path; //copy of the path
                begin_time = clock();
                total_distance = d_.tsp3opt(path3opt, iterations3opt);
                s = {"TA + 3-OPT", total_distance, float(clock() - begin_time) / CLOCKS_PER_SEC, round ((total_distance / lower_bound) * 1000.0) / 1000.0};
                stats.push_back(s);
                cout << "Done." << endl;
            }
        }
    }

    //NN
    if(!isComplete) {
        cout << endl << "NN algorithm not available for this graph." << endl;
    } else {
        cout << "NN algorithm is running...";
        stat s;
        vector<Vertex *> path;
        begin_time = clock();
        path = d_.tspNearestNeighbour();
        float time = float(clock() - begin_time) / CLOCKS_PER_SEC;
        double total_distance = d_.getPathDist(path);
        s = {"NN", total_distance, time, round ((total_distance / lower_bound) * 1000.0) / 1000.0};
        stats.push_back(s);
        cout << "Done." << endl;
        //2opt
        if(iterations2opt > 0){
            cout << "NN + 2-OPT algorithm is running...";
            vector<Vertex *> path2opt = path; //copy of the path
            begin_time = clock();
            total_distance = d_.tsp2opt(path2opt, iterations2opt);
            s = {"NN + 2-OPT", total_distance, float(clock() - begin_time) / CLOCKS_PER_SEC, round ((total_distance / lower_bound) * 1000.0) / 1000.0};
            stats.push_back(s);
            cout << "Done." << endl;
        }
        if(iterations3opt > 0){
            cout << "NN + 3-OPT algorithm is running...";
            vector<Vertex *> path3opt = path; //copy of the path
            begin_time = clock();
            total_distance = d_.tsp3opt(path3opt, iterations3opt);
            s = {"NN + 3-OPT", total_distance, float(clock() - begin_time) / CLOCKS_PER_SEC, round ((total_distance / lower_bound) * 1000.0) / 1000.0};
            stats.push_back(s);
            cout << "Done." << endl;
        }
    }

    //DRAW TABLE
    cout << endl << setfill('=') << setw(30)<< "=" << "SUMMARY" << setw(31) << "=" << endl;
    cout << endl;
    cout << left << setfill(' ') << setw(15) << "Algorithm" << " |" <<  setw(15) << " Distance" << " |" << setw(15) << " Time" << " |" << setw(15) << " Approximation" << " |" << endl;
    cout << setfill('-') << setw(16) << "-" << "+" << setfill('-') << setw(16) << "-" << "+" << setfill('-') << setw(16) << "-" << "+" << setfill('-') << setw(16) << "-" << "+" << endl;
    for (auto &s : stats) {
        ostringstream t, a;
        t << s.time << "s";
        a << s.ratio << "x";
        cout << left << setfill(' ') << setw(15) << s.name << " |" << right << setw(15) << s.dist << " |" << setw(15) << t.str() << " |" << setw(15) << a.str() << " |" << endl;
        cout << setfill('-') << setw(16) << "-" << "+" << setfill('-') << setw(16) << "-" << "+" << setfill('-') << setw(16) << "-" << "+" << setfill('-') << setw(16) << "-" << "+" << endl;
    }
    cout << endl;
    cout << setfill('=') << setw(68) << "=" << endl;
}
