//
// Created by summe on 11/26/2023.
//
#pragma once
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <map>

#include "Graph.h"

#ifndef AO3_TRAWLER_FICCSV_H
#define AO3_TRAWLER_FICCSV_H


class FicCSV : private Graph{
private:
    std::map<int, std::string> tags;
    std::map<int, std::string> ficTitles;



public:
    FicCSV(std::string edgelist);
    FicCSV(std::string edgelist, std::string tagKey, std::string ficKey);

    void addTagKey(std::string tagKey);
    void addFicKey(std::string ficKey);

    void printNodesOrig();

    std::vector<std::string> translate(std::vector<int> nodes);
    std::vector<std::string> getNodes();
    void printNodes();

    std::map<std::string, std::vector<std::pair<std::string, std::string>>> getAdjList();
    void printAdjList();

    std::vector<std::pair<std::string, std::string>> pathBtwnPoints1(std::string from, std::string to);
    void printPath(std::string from, std::string to);
};


#endif //AO3_TRAWLER_FICCSV_H
