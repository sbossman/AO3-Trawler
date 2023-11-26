//
// Created by summe on 11/24/2023.
//

#pragma once

#include <unordered_map>
#include <vector>
#include <unordered_set>
#include <queue>
#include <algorithm>
#include <iostream>

#ifndef AO3_TRAWLER_GRAPH_H
#define AO3_TRAWLER_GRAPH_H

struct Path{
    int from;
    int curr;
    std::vector<std::pair<int, int>> path;
    // how we got to curr| node|tag

    Path(int from){
        this->from = from;
        curr = from;
        path = {};
    }

    Path(Path prev, int curr, int tag){
        from = prev.from;
        this->curr = curr;
        path = prev.path;
        path.push_back({curr, tag});
    }
};

class Graph {
private:
    int v; // number of vertexes
    int e; // number of edges

protected:
    std::unordered_map<int, std::vector<std::pair<int, int>>> theList;
    //       work     connected works    id   tag
    std::unordered_map<int, int> outDegree;
    // the int contains the outdegree for a given id

public:
    Graph();

    void insertEdge(int from, int to, int tag);

    std::vector<int> bfs();
    void printBFS();

    std::vector<int> getNodes();
    void printNodes();

    // returns path between two points
    std::vector<std::pair<int, int>> pathBtwnPoints1(int from, int to);

    // TO DO: include way to find quickest route btwn two fics
};


#endif //AO3_TRAWLER_GRAPH_H
