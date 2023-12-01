//
// Created by summe on 12/1/2023.
//
#include "Graph.h"
#ifndef AO3_TRAWLER_ADJACENCYLIST_H
#define AO3_TRAWLER_ADJACENCYLIST_H


class AdjacencyList : public Graph{
protected:
    std::unordered_map<int, std::vector<std::pair<int, int>>> theList;
    //       work     connected works    id   tag
    std::unordered_map<int, int> outDegree;
    // the int contains the outdegree for a given id

public:
    AdjacencyList();

    void insertEdge(int from, int to, int tag);

    std::vector<int> bfs();

    std::vector<int> getNodes();

    // returns path between two points
    std::vector<std::pair<int, int>> pathBtwnPoints(int from, int to);
};


#endif //AO3_TRAWLER_ADJACENCYLIST_H
