//
// Created by summe on 11/26/2023.
//

#include "FicCSV.h"

FicCSV::FicCSV(std::string edgelist) {

    std::ifstream edgeListFile(edgelist);
    if (!edgeListFile.is_open()) {
        std::cout << "FILE NOT OPEN" << std::endl;
    }

    std::string line;
    std::string word;
    while(getline(edgeListFile, line)){
        std::vector <std::string> row;
        word = "";
        // Parses individual line of csv
        for (unsigned int i = 0; i < line.size(); i++) {
            if (line[i] == ',') {
                row.push_back(word);
                word = "";
            } else {
                word += line[i];
            }
        }
        row.push_back(word);

        int from = stoi(row[0]);
        int to = stoi(row[1]);
        int tag = stoi(row[2]);

        Graph::insertEdge(from, to, tag);
    }
}

void FicCSV::addFicKey(std::string ficKey) {
    std::ifstream ficKeyFile(ficKey);

    if (!ficKeyFile.is_open())
        std::cout << "FILE NOT OPEN" << std::endl;

    std::string line;
    std::string word;
    while(getline(ficKeyFile, line)){
        std::vector <std::string> row;
        word = "";
        // Parses individual line of csv
        for (unsigned int i = 0; i < line.size(); i++) {
            if (line[i] == ',') {
                row.push_back(word);
                word = "";
            } else {
                word += line[i];
            }
        }
        row.push_back(word);

        int key = stoi(row[0]);
        std::string title = row[1];

        ficTitles[key] = title;
    }
}

void FicCSV::addTagKey(std::string tagKey) {
    std::ifstream tagKeyFile(tagKey);

    if (!tagKeyFile.is_open())
        std::cout << "FILE NOT OPEN" << std::endl;

    std::string line;
    std::string word;
    while(getline(tagKeyFile, line)){
        std::vector <std::string> row;
        word = "";
        // Parses individual line of csv
        for (unsigned int i = 0; i < line.size(); i++) {
            if (line[i] == ',') {
                row.push_back(word);
                word = "";
            } else {
                word += line[i];
            }
        }
        row.push_back(word);

        int key = stoi(row[0]);
        std::string tag = row[1];

        tags[key] = tag;
    }
}

void FicCSV::printNodesOrig() {
    Graph::printNodes();
}

std::vector<std::string> FicCSV::translate(std::vector<int> nodes){
    std::vector<std::string> ficList;

    for(int i = 0; i < nodes.size(); i++){
        int id = nodes[i];
        if(ficTitles.find(id) == ficTitles.end())
            ficList.push_back(std::to_string(id));
        else
            ficList.push_back(ficTitles[id]);
    }
    return ficList;
}

std::vector<std::string> FicCSV::getNodes() {
    return translate(Graph::getNodes());
}

void FicCSV::printNodes() {
    std::vector<std::string> ficList = getNodes();
    for(int i = 0; i < ficList.size(); i++){
        std::cout << ficList[i] << std::endl;
    }
}

std::map<std::string, std::vector<std::pair<std::string, std::string>>> FicCSV::getAdjList(){
    std::map<std::string, std::vector<std::pair<std::string, std::string>>> adjList;
    auto iter = Graph::theList.begin();
    for(; iter != Graph::theList.end(); iter++){
        std::string key = ficTitles[iter->first];
        std::vector<std::pair<std::string, std::string>> values;
        for(int i = 0; i < iter->second.size(); i++){
            std::pair<int, int> curr = iter->second[i];
            std::string to = ficTitles[curr.first];
            std::string tag = tags[curr.second];
            std::pair<std::string, std::string> p = {to, tag};
            values.push_back(p);
        }
        adjList[key] = values;
    }
    return adjList;
}

void FicCSV::printAdjList() {
    std::map<std::string, std::vector<std::pair<std::string, std::string>>> adjList = getAdjList();
    auto iter = adjList.begin();
    for(; iter != adjList.end(); iter++){
        std::cout << iter->first << std::endl;
        std::vector<std::pair<std::string, std::string>> values = iter->second;
        for(int i = 0; i < iter->second.size(); i++){
            std::pair<std::string, std::string> curr = values[i];
            std::cout << "\t" << curr.second << ": " << curr.first << std::endl;
        }
    }
}