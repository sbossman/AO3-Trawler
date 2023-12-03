#include <iostream>
#include "FicCSV.h"

int main() {
    std::string path = "./data/";
    std::string edgelist = "ReducedEdgeList.csv";
    std::string tags = "IntToTagTranslator.csv";
    std::string titles = "IntToTitleTranslator.csv";

    FicCSV fics(path + edgelist);
    fics.addFicKey(path + titles);
    fics.addTagKey(path + tags);

    std::string from;
    std::string to;

    std::string frontEndPath = "./front-end/src/components/";
    std::string infileName = "fictitles.txt";
    std::string outfileName = "ficsinfo.txt";

    std::ifstream infile(frontEndPath + infileName);
    if(!infile.is_open()){
        std::cout << "FILE NOT OPEN" << std::endl;
    }
    std::string contents;
    getline(infile, contents);
    int i = 0;
    while(contents[i] != ',') {
        from += contents[i];
        i++;
    }
    i++;
    while(i < contents.size()){
        to += contents[i];
        i++;
    }
    std::cout << from << std::endl;
    std::cout << to << std::endl;

    fics.writePathToFrontend(from, to, frontEndPath + outfileName);
    return 0;
}
