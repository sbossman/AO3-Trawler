//
// Created by summe on 11/24/2023.
//

#include "Graph.h"
Graph::Graph() {
    v = 0;
    e = 0;
}

void Graph::insertEdge(int to, int from, int tag) {
    auto foundFrom = theList.find(from);
    auto foundTo = theList.find(to);

    // inserts the vertice if it doesn't already exist
    if(foundTo == theList.end()){
        v++;
        theList[to] = {};
        outDegree[to] = 0;
    }
    if(foundFrom == theList.end()){
        v++;
        theList[from] = {};
        outDegree[from] = 0;
    }

    // finds out if the edge already exists
    auto inList = theList[from].begin();
    for(; inList != theList[from].end(); inList++){
        if(inList->first == to)
            return;
    }

    // inserts the edge into the map
    theList[from].push_back({to, tag});
    outDegree[from]++;
    e++;
}

std::vector<int> Graph::bfs(){
    auto iter = theList.begin();
    std::vector<int> vertices; // ngl figuring wtf this is might take a sec
    std::set<int> visited;
    std::queue<int> vertexQueue;

    vertexQueue.push(iter->first);
    visited.insert(iter->first);

    while(!vertexQueue.empty()){
        int front = vertexQueue.front();
        vertices.push_back(front);

        std::vector<int> connected = theList[front];
        for(int i = 0; i < connected; i++){
            // check if it's already in the queue
            // add it to the queue
        }
    }
    return vertices;
}

void Graph::printBFS(){
    std::vector<int> bfsResult = bfs();
    for(int i = 0; i < bfsResult.size(); i++){
        std::cout << bfsResult[i] << std::endl;
    }
}