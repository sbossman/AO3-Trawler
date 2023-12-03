#include <iostream>
#include <chrono>
#include "graphs/Graph.h"
#include "FicCSV.h"

int main() {
    std::string path = "./data/";
    std::string edgelist = "ReducedEdgeList.csv";
    std::string tags = "IntToTagTranslator.csv";
    std::string titles = "IntToTitleTranslator.csv";

    FicCSV fics(path + edgelist);
    fics.addFicKey(path + titles);
    std::cout << "FINISHED ADDING FIC KEY" << std::endl;
    fics.addTagKey(path + tags);
    std::cout << "FINISHED ADDING TAG KEY" << std::endl;

    std::vector<std::string> pathAndStuff = fics.createGraphThenPath("All the Young Dudes", "Deku? I think he's some pro...");
    std::string alPath = pathAndStuff[0];
    std::string amPath = pathAndStuff[1];
    std::string duration = pathAndStuff[2];
    std::string alMakeTime = pathAndStuff[3];
    std::string amMakeTime = pathAndStuff[4];
    std::string alPathTime = pathAndStuff[5];
    std::string amPathime = pathAndStuff[6];


    return 0;
}
