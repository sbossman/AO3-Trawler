//
// Created by summe on 11/24/2023.
//

#pragma once

#include <map>
#include <vector>
#include <set>
#include <queue>
#include <algorithm>
#include <iostream>

#ifndef AO3_TRAWLER_GRAPH_H
#define AO3_TRAWLER_GRAPH_H


class Graph {
private:
    int v; // number of vertexes
    int e; // number of edges
    std::map<int, std::vector<std::pair<int, int>>> theList;
    //       work     connected works    id   tag
    std::map<int, int> outDegree;
    // the int contains the outdegree for a given id

public:
    Graph();

    void insertEdge(int from, int to, int tag);

    std::vector<int> bfs();
    void printBFS();

    std::vector<int> listNodes();
    void printNodes();

    // TO DO: include way to find quickest route btwn two fics
};


#endif //AO3_TRAWLER_GRAPH_H
