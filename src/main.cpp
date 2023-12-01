#include <iostream>
#include <chrono>
#include "Graph.h"
#include "FicCSV.h"

int main() {
    std::string path = "./data/";
    std::string edgelist = "EdgeList.csv";
    std::string tags = "IntToTagTranslator.csv";
    std::string titles = "IntToTitleTranslator.csv";

    auto start = std::chrono::high_resolution_clock::now();

    FicCSV fics(path + edgelist);
    fics.addFicKey(path + titles);
    std::cout << "FINISHED ADDING FIC KEY" << std::endl;
    fics.addTagKey(path + tags);
    std::cout << "FINISHED ADDING TAG KEY" << std::endl;
    auto keysDone = std::chrono::high_resolution_clock::now();

    std::cout << std::endl;

    std::cout << "---ADJACENCY LIST---" << std::endl;
    AdjacencyList adjList;
    fics.insertEdges(adjList);
    std::cout << "Completed creating adjacency list" << std::endl;
    auto adjListMade = std::chrono::high_resolution_clock::now();
    std::cout << "Pathing" << std::endl;
    fics.printPath("All the Young Dudes", "Deku? I think he's some pro...", adjList);
    auto adjListPath = std::chrono::high_resolution_clock::now();
    std::cout << std::endl;

    std::cout << "---ADJACENCY MATRIX---" << std::endl;
    AdjacencyMatrix adjMatrix = AdjacencyMatrix(8636);
    fics.insertEdges(adjMatrix);
    std::cout << "Completed creating adjacency matrix" << std::endl;
    auto adjMatrixMade = std::chrono::high_resolution_clock::now();
    std::cout << "Pathing" << std::endl;
    fics.printPath("All the Young Dudes", "Deku? I think he's some pro...", adjMatrix);
    auto adjMatrixPath = std::chrono::high_resolution_clock::now();
    std::cout << std::endl;

    std::cout << "---TIMES---" << std::endl;
    int duration = (std::chrono::duration_cast<std::chrono::seconds>(std::chrono::high_resolution_clock::now() - start)).count();

    int adjListTime = (std::chrono::duration_cast<std::chrono::seconds>(adjListMade - keysDone)).count();
    int adjMatrixTime = (std::chrono::duration_cast<std::chrono::seconds>(adjMatrixMade - adjListPath)).count();

    std::cout << "Total time: " << (duration/60) << ":" << (duration%60) << std::endl;
    std::cout << "Adjacency List Time: " << (adjListTime/60) << ":" << (adjListTime%60) << std::endl;
    std::cout << "Adjacency Matrix Time: " << (adjMatrixTime/60) << ":" << (adjMatrixTime%60) << std::endl;


    return 0;
}
