//
// Created by summe on 12/1/2023.
//

#include "AdjacencyList.h"
AdjacencyList::AdjacencyList() : Graph() {};

void AdjacencyList::insertEdge(int from, int to, int tag) {
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

    // inserts the edge into the map
    theList[from].push_back({to, tag});
    outDegree[from]++;
    e++;
}

std::vector<int> AdjacencyList::bfs() {
    auto iter = theList.begin();
    std::vector<int> vertices;
    std::unordered_set<int> visited;
    std::vector<int> vertexQueue;

    while(visited.size() != theList.size()){
        bool alreadyVisited = std::find(visited.begin(), visited.end(), iter->first) != visited.end();

        if(alreadyVisited)
            continue;
        vertexQueue.push_back(iter->first);
        visited.insert(iter->first);

        // TO DO: wrap in loop
        while(!vertexQueue.empty()){
            int front = vertexQueue[0];
            vertices.push_back(front);
            // visited.insert(front);

            std::vector<std::pair<int, int>> connected = theList[front];

            // goes through connected nodes and adds them to queue
            for(int i = 0; i < connected.size(); i++){
                int val = connected[i].first;
                // std::cout << "VAL: " << val << std::endl;

                bool inVisited = visited.find(val) != visited.end();

                // std::cout << "IN QUEUE: " << inQueue << "\t IN VISITED: " << inVisited << std::endl;
                if(!inVisited){ // if not in queue
                    vertexQueue.push_back(val);
                    visited.insert(val);
                }
            }
            vertexQueue.erase(vertexQueue.begin());
            // remove item from vertex front
        }

        iter++;
    }

    return vertices;
}

std::vector<int> AdjacencyList::getNodes() {
    std::vector<int> nodes;

    auto iter = theList.begin();
    for(; iter != theList.end(); iter++){
        nodes.push_back(iter->first);
    }

    return nodes;
}

std::vector<std::pair<int, int>> AdjacencyList::pathBtwnPoints(int from, int to) {
    /*
     * FINDING PATH BETWEEN TWO POINTS USING BFS
     * 1. Do BFS like usual
     * 2. Except now each point added to the vector has a fun little
     *    thing basically tracking the path it got there through
     * 3. Return that path
     */
    std::unordered_set<int> visited;
    std::vector<Path> pathQueue; // Path.curr is the vertex we're looking for
    // std::vector<int> vertexQueue; //

    visited.insert(from);
    pathQueue.push_back(Path(from));

    while(!pathQueue.empty()){
        Path frontPath = pathQueue[0];
        if(frontPath.curr == to){
            return frontPath.path;
        }

        std::vector<std::pair<int, int>> connected = theList[frontPath.curr];

        for(int i = 0; i < connected.size(); i++){
            int title = connected[i].first;
            int tag = connected[i].second;

            bool inVisited = visited.find(title) != visited.end();
            if(!inVisited){
                visited.insert(title);
                Path current = Path(frontPath, title, tag);
                pathQueue.push_back(current);
            }

        }
        pathQueue.erase(pathQueue.begin());
    }

    return {};
}