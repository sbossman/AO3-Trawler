#include <iostream>
#include "Graph.h"

int main() {
    Graph g;
    g.insertEdge(0, 1, 1);
    g.insertEdge(1, 0, 1);
    g.insertEdge(2, 3, 2);
    g.insertEdge(3, 2, 2);
    g.insertEdge(0, 2, 1);
    g.insertEdge(2, 0, 1);
    g.insertEdge(0, 3, 1);
    g.insertEdge(3, 0, 1);

    std::cout << "PRINTING NODES" << std::endl;
    g.printNodes();
    std::cout << std::endl;

    std::cout << "PRINTING BFS" << std::endl;
    g.printBFS();
    std::string startTitle = "";
    std::string endTitle = "";
    return 0;
}
