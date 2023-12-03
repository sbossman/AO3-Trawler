//
// Created by summe on 12/1/2023.
//

#include "AdjacencyMatrix.h"

AdjacencyMatrix::AdjacencyMatrix(int vertices) {
    v = vertices;
    for(int i = 0; i < vertices; i++){
        std::vector<int> temp;
        for(int j = 0; j < vertices; j++)
            temp.push_back(-1);
        matrix.push_back(temp);
    }
}

void AdjacencyMatrix::insertEdge(int from, int to, int tag) {
    if(matrix[from][to] == -1) {
        matrix[from][to] = tag;
        e++;
    }
}

std::vector<int> AdjacencyMatrix::bfs() {
    std::vector<int> vertices;
    std::unordered_set<int> visited;
    std::vector<int> vertexQueue;
    int ind = 0;

    while(vertices.size() != matrix.size()){
        bool alreadyVisited = std::find(visited.begin(), visited.end(), ind) == visited.end();
        if(alreadyVisited)
            continue;

        vertexQueue.push_back(ind);
        visited.insert(ind);

        while(!vertexQueue.empty()){
            int front = vertexQueue[0];

            vertices.push_back(front);

            for(int i = 0; i < v; i++){
                bool inVisited = visited.find(i) != visited.end();
                if(matrix[front][i] != -1 && !inVisited){
                    vertexQueue.push_back(i);
                    visited.insert(i);
                }
            }
            vertexQueue.erase(vertexQueue.begin());
        }

        ind++;
    }

    return vertices;
}

std::vector<int> AdjacencyMatrix::getNodes(){
    std::vector<int> nodes;

    for(int i = 0; i < matrix.size(); i++){
        nodes.push_back(i);
    }

    return nodes;
}

std::vector<std::pair<int, int>> AdjacencyMatrix::pathBtwnPoints(int from, int to) {
    std::unordered_set<int> visited;
    std::vector<Path> pathQueue;

    visited.insert(from);
    pathQueue.push_back(Path(from));

    while(!pathQueue.empty()){
        Path frontPath = pathQueue[0];
        if(frontPath.curr == to){
            return frontPath.path;
        }

        for(int i = 0; i < matrix.size(); i++){
            int title = i;
            int tag = matrix[frontPath.curr][i];

            bool inVisited = visited.find(title) != visited.end();
            if(tag != -1 && !inVisited){
                visited.insert(title);
                Path current = Path(frontPath, title, tag);
                pathQueue.push_back(current);
            }
        }
        pathQueue.erase(pathQueue.begin());
    }
    return {};
}

void AdjacencyMatrix::printMatrix() {
    for(int i = 0; i < matrix.size(); i++){
        for(int j = 0; j < matrix[i].size(); j++)
            std::cout << matrix[i][j] << "\t";
        std::cout << std::endl;
    }
}