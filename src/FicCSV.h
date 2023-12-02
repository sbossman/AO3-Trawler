//
// Created by summe on 11/26/2023.
//
#pragma once
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <map>

#include "./graphs/Graph.h"
#include "./graphs/AdjacencyList.h"
#include "./graphs/AdjacencyMatrix.h"

#ifndef AO3_TRAWLER_FICCSV_H
#define AO3_TRAWLER_FICCSV_H


class FicCSV{
private:
    std::string edgelist;
    std::map<int, std::string> tags;
    std::map<int, std::string> ficTitles;

public:
    FicCSV(std::string edgelist);
    FicCSV(std::string edgelist, std::string tagKey, std::string ficKey);

    void insertEdges(Graph& graph);
    void addTagKey(std::string tagKey);
    void addFicKey(std::string ficKey);

    std::vector<std::string> translate(std::vector<int> nodes);
    std::vector<std::string> getNodes(Graph& graph);
    void printNodes(Graph& graph);

//    std::map<std::string, std::vector<std::pair<std::string, std::string>>> getAdjList();
//    void printAdjList();

    std::vector<std::pair<std::string, std::string>> pathBtwnPoints(std::string from, std::string to, Graph& graph);
    void printPath(std::string from, std::string to, Graph& graph);
};


#endif //AO3_TRAWLER_FICCSV_H
