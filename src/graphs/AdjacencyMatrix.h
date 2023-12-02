//
// Created by summe on 12/1/2023.
//
#include "Graph.h"

#ifndef AO3_TRAWLER_ADJACENCYMATRIX_H
#define AO3_TRAWLER_ADJACENCYMATRIX_H


class AdjacencyMatrix : public Graph{
protected:
    std::vector<std::vector<int>> matrix;

public:
    AdjacencyMatrix(int vertices);

    void insertEdge(int from, int to, int tag);

    std::vector<int> bfs();
    std::vector<int> getNodes();

    std::vector<std::pair<int, int>> pathBtwnPoints(int from, int to);

    void printMatrix();


};


#endif //AO3_TRAWLER_ADJACENCYMATRIX_H
