//
// Created by Guilherme Monteiro on 01/05/2023.
//

#ifndef DA_PROJECT2_DATA_H
#define DA_PROJECT2_DATA_H

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

class Data {

public:
    bool readToyData(string filename);
    bool readRealData(string filename);

};


bool Data::readStations(string filename) {
    ifstream input(filename);
    string labels = "Name,District,Municipality,Township,Line";
    if (input.is_open()){
        string l;
        getline(input, l);
        if(l == labels) {
            int id = 1;
            string name, district, municipality, township, line;
            string field;
            vector<string> fields;
            char quote_char = '"';
            while (getline(input, l)) {
                stringstream iss(l);
                while (getline(iss, field, ',')){
                    fields.push_back(field);
                    if (field[0] == quote_char && field.back() != quote_char){
                        getline(iss, field, '"');
                        fields.back() += "," + field + '"';         //add a comma, because it is part of the input and was lost because of the getline
                        getline(iss, field, ',');       //consume the comma
                    }
                }

                name = fields[0];
                district = fields[1];
                municipality = fields[2];
                township = fields[3];
                line = fields[4];

                districts.insert(district);
                municipalities.insert(municipality);

                if(names.insert({name,id}).second){      //(names.insert(name).second) return false if element already exists
                    Station* station = new Station(name,district,municipality,township,line);
                    Vertex* v = new Vertex(id);
                    v->setStation(station);
                    g.addVertex(v);
                    id++;
                }
                fields.clear();
            }
            stations = filename;
            return true;
        } else cout << "\nFile content for " << filename << " is incorrect. Please submit the right file.\n";
    } else cout << "\nCould not open " << filename << endl;
    return false;
}

bool Data::readNetwork(std::string filename) {
    ifstream input(filename);
    string labels = "Station_A,Station_B,Capacity,Service";
    if (input.is_open()){
        string l;
        getline(input, l);
        if(l == labels) {
            string station_A, station_B, capacity, service;
            int counter = 1;
            string field;
            vector<string> fields;
            char quote_char = '"';

            while (getline(input, l)) {
                stringstream iss(l);
                Vertex* vA = nullptr; Vertex* vB = nullptr;

                while (getline(iss, field, ',')){
                    fields.push_back(field);
                    if (field[0] == quote_char && field.back() != quote_char){
                        getline(iss, field, '"');
                        fields.back() += "," + field + '"';         //add a comma, because it is part of the input and was lost because of the getline
                        getline(iss, field, ',');       //consume the comma
                    }
                }
                station_A = fields[0];
                station_B = fields[1];
                capacity = fields[2];
                service = fields[3];
                counter++;
                for (auto v : g.getVertexSet()){ // find vertex
                    Station* s = v->getStation();
                    if(s->getName() == station_A) vA = v;
                    else if(s->getName() == station_B) vB = v;
                    if(vA != nullptr && vB != nullptr) break; // both vertex were found.
                }
                fields.clear();

                if(!g.addBidirectionalEdge(vA, vB, stod(capacity), service)){
                    cout << "\nOn line " << (counter) <<", there are stations that do not exist.\n";
                }
            }
            network = filename;
            return true;
        } else cout << "\nFile content for " << filename << " is incorrect. Please submit the right file.\n";
    } else cout << "\nCould not open " << filename << endl;
    return false;
}


#endif //DA_PROJECT2_DATA_H
