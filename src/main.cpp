#include <iostream>
#include "Graph.h"
#include "FicCSV.h"

int main() {
    std::string path = "./tests/";
    std::string edgelist = "bEdgelist.csv";
    std::string tags = "bTags.csv";
    std::string titles = "bTitles.csv";
    FicCSV fics(path + edgelist);
    fics.addFicKey(path + titles);
    fics.addTagKey(path + tags);
    std::cout << "PRINTING ALL NODES" << std::endl;
    fics.printNodes();

    std::cout << "PRINTING ADJACENCY LIST" << std::endl;
    fics.printAdjList();
    return 0;
}
