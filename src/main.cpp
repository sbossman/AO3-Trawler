#include <iostream>
#include "Graph.h"

int main() {
    Graph g;
    g.insertEdge(0, 1, 1);
    g.insertEdge(2, 3, 2);
    g.insertEdge(0, 2, 1);
    g.insertEdge(0, 3, 1);

    g.printBFS();
    std::string startTitle = "";
    std::string endTitle = "";
    std::cout << "HELLO WORLD" << std::endl;
    return 0;
}
