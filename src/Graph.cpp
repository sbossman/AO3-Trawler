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
    std::vector<int> vertexQueue;


    vertexQueue.push_back(iter->first);
    visited.insert(iter->first);

    // TO DO: wrap in loop
    while(!vertexQueue.empty()){
        int front = vertexQueue[0];
        vertices.push_back(front);
        visited.insert(front);

        std::vector<std::pair<int, int>> connected = theList[front];

        // goes through connected nodes and adds them to queue
        for(int i = 0; i < connected.size(); i++){
            int val = connected[i].first;
            // std::cout << "VAL: " << val << std::endl;

            bool inQueue = std::find(vertexQueue.begin(), vertexQueue.end(), val) != vertexQueue.end();
            bool inVisited = std::find(visited.begin(), visited.end(), val) != visited.end();

            // std::cout << "IN QUEUE: " << inQueue << "\t IN VISITED: " << inVisited << std::endl;
            if(!inVisited && !inQueue){ // if not in queue
                vertexQueue.push_back(val);
            }
        }
        vertexQueue.erase(vertexQueue.begin());
        // remove item from vertex front
    }
    return vertices;
}

void Graph::printBFS(){
    std::vector<int> bfsResult = bfs();
    for(int i = 0; i < bfsResult.size(); i++){
        std::cout << bfsResult[i] << std::endl;
    }
}

std::vector<int> Graph::listNodes() {
    std::vector<int> nodes;

    auto iter = theList.begin();
    for(; iter != theList.end(); iter++){
        nodes.push_back(iter->first);
    }

    return nodes;
}

void Graph::printNodes() {
    std::vector<int> nodes = listNodes();
    for(int i = 0; i < nodes.size(); i++){
        std::cout << nodes[i] << std::endl;
    }
}