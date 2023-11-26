#include <iostream>
#include "Graph.h"
#include "FicCSV.h"

int main() {
    std::string path = "./tests/";
    std::string edgelist = "cEdgelist.csv";
    std::string tags = "cTags.csv";
    std::string titles = "cTitles.csv";
    FicCSV fics(path + edgelist);
    std::cout << "FINISHED FIC EDGELIST" << std::endl;
    fics.addFicKey(path + titles);
    std::cout << "FINISHED ADDING FIC KEY" << std::endl;
    fics.addTagKey(path + tags);
    std::cout << "FINISHED ADDING TAG KEY" << std::endl;

    std::cout << "PRINTING ALL NODES" << std::endl;
    fics.printNodes();
    std::cout << std::endl;

    std::cout << "PRINTING ADJACENCY LIST" << std::endl;
    fics.printAdjList();
    std::cout << std::endl;

    std::cout << "PATHING (there is path)" << std::endl;
    fics.printPath("B", "G");
    std::cout << std::endl;

    std::cout << "PATHING (there is NO path)" << std::endl;
    fics.printPath("B", "J");
    std::cout << std::endl;

    return 0;
}
