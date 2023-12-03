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
protected:
    int v; // number of vertexes
    int e; // number of edges
    // the int contains the outdegree for a given id

public:
    Graph();
    virtual void insertEdge(int from, int to, int tag) = 0;

    virtual std::vector<int> bfs() = 0;
    void printBFS();

    virtual std::vector<int> getNodes() = 0;
    void printNodes();

    // returns path between two points
    virtual std::vector<std::pair<int, int>> pathBtwnPoints(int from, int to) = 0;

    int getNumVertices();
};


#endif //AO3_TRAWLER_GRAPH_H
