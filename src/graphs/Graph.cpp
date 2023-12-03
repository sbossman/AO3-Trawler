//
// Created by summe on 11/24/2023.
//

#include "Graph.h"
Graph::Graph() {
    v = 0;
    e = 0;
}


void Graph::printBFS(){
    std::vector<int> bfsResult = bfs();
    for(int i = 0; i < bfsResult.size(); i++){
        std::cout << bfsResult[i] << std::endl;
    }
}

void Graph::printNodes() {
    std::vector<int> nodes = getNodes();
    for(int i = 0; i < nodes.size(); i++){
        std::cout << nodes[i] << std::endl;
    }
}

int Graph::getNumVertices(){
    return v;
}