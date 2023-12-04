//
// Created by summe on 11/26/2023.
//

#include "FicCSV.h"

FicCSV::FicCSV(std::string edgelist) {
    this->edgelist = edgelist;
    std::ofstream file("../src/components/toggle.txt");
    file<<"N";
    file.close();
}

FicCSV::FicCSV(std::string edgelist, std::string tagKey, std::string ficKey) {
    this->edgelist = edgelist;
    addTagKey(tagKey);
    addFicKey(ficKey);
}

void FicCSV::insertEdges(Graph &graph) {
    std::ifstream edgeListFile(edgelist);
    if (!edgeListFile.is_open()) {
        std::cout << "FILE NOT OPEN(2)" << std::endl;
    }

    std::string line;
    std::string word;
    while(getline(edgeListFile, line)){
        std::vector <std::string> row;
        word = "";
        // Parses individual line of csv
        for (unsigned int i = 0; i < line.size(); i++) {
            if (line[i] == ',') {
                row.push_back(word);
                word = "";
            } else {
                word += line[i];
            }
        }
        row.push_back(word);

        int from = stoi(row[0]);
        int to = stoi(row[1]);
        int tag = stoi(row[2]);

        graph.insertEdge(from, to, tag);
    }
}

void FicCSV::addFicKey(std::string ficKey) {
    std::ifstream ficKeyFile(ficKey);

    if (!ficKeyFile.is_open())
        std::cout << "FILE NOT OPEN(3)" << std::endl;

    std::string line;
    std::string word;
    while(getline(ficKeyFile, line)){
        std::vector <std::string> row;
        word = "";
        // Parses individual line of csv
        for (unsigned int i = 0; i < line.size(); i++) {
            if (line[i] == ',') {
                row.push_back(word);
                word = "";
            } else {
                word += line[i];
            }
        }
        row.push_back(word);

        int key = stoi(row[0]);
        std::string title = row[1];

        ficTitles[key] = title;
    }
}

void FicCSV::addTagKey(std::string tagKey) {
    std::ifstream tagKeyFile(tagKey);

    if (!tagKeyFile.is_open())
        std::cout << "FILE NOT OPEN(4)" << std::endl;

    std::string line;
    std::string word;
    while(getline(tagKeyFile, line)){
        std::vector <std::string> row;
        word = "";
        // Parses individual line of csv
        for (unsigned int i = 0; i < line.size(); i++) {
            if (line[i] == ',') {
                row.push_back(word);
                word = "";
            } else {
                word += line[i];
            }
        }
        row.push_back(word);

        int key = stoi(row[0]);
        std::string tag = row[1];

        tags[key] = tag;
    }
}


std::vector<std::string> FicCSV::translate(std::vector<int> nodes){
    std::vector<std::string> ficList;

    for(int i = 0; i < nodes.size(); i++){
        int id = nodes[i];
        if(ficTitles.find(id) == ficTitles.end())
            ficList.push_back(std::to_string(id));
        else
            ficList.push_back(ficTitles[id]);
    }
    return ficList;
}

std::vector<std::string> FicCSV::getNodes(Graph& graph) {
    return translate(graph.getNodes());
}

void FicCSV::printNodes(Graph& graph) {
    std::vector<std::string> ficList = getNodes(graph);
    for(int i = 0; i < ficList.size(); i++){
        std::cout << ficList[i] << std::endl;
    }
}

std::vector<std::pair<std::string, std::string>> FicCSV::pathBtwnPoints(std::string from, std::string to, Graph& graph){
    int fromId = -1;
    int toId = -1;

    auto iter = ficTitles.begin();
    for(; iter != ficTitles.end(); iter++){
        if(iter->second == from)
            fromId = iter->first;
        if(iter->second == to)
            toId = iter->first;
    }
    if(fromId == -1) {
        std::cout << "COULD NOT FIND FROM STRING" << std::endl;
        return {};
    }
    if(toId == -1){
        std::cout << "COULD NOT FIND TO STRING" << std::endl;
        return {};
    }

    auto pathIds = graph.pathBtwnPoints(fromId, toId);
    std::vector<std::pair<std::string, std::string>> path = {};
    for(int i = 0; i < pathIds.size(); i++){
        std::pair<int, int> curr = pathIds[i];
        std::string title = ficTitles[curr.first];
        std::string tag = tags[curr.second];
        path.push_back({title, tag});
    }
    return path;

}
void FicCSV::printPath(std::string from, std::string to, Graph& graph){
    auto path = pathBtwnPoints(from, to, graph);
    std::cout << from << std::endl;
    for(int i = 0; i < path.size(); i++){
        std::cout << path[i].second << " --> " << path[i].first << std::endl;
    }
}

std::vector<std::string> FicCSV::createGraphThenPath(std::string from, std::string to){
    auto startTime = std::chrono::high_resolution_clock::now();

    // ADJACENCY LIST //
    // Creation
    AdjacencyList adjList;
    insertEdges(adjList);
    auto adjListMadeTime = std::chrono::high_resolution_clock::now();

    // pathing
    auto adjListPath = pathBtwnPoints(from, to, adjList);
    std::string adjListPathStr = from;
    for(int i = 0; i < adjListPath.size(); i++){
        adjListPathStr += " -> " + adjListPath[i].second + " -> " + adjListPath[i].first;
    }
    std::cout << "Pathed (AL)" << std::endl;
    auto adjListPathTime = std::chrono::high_resolution_clock::now();


    // ADJACENCY MATRIX
    AdjacencyMatrix adjMatrix = AdjacencyMatrix(ficTitles.size() + 1);
    std::cout << "Matrix empty but made" << std::endl;
    insertEdges(adjMatrix);
    std::cout << "Inserted all edges in  AdjMatrix" << std::endl;
    auto adjMatrixMadeTime = std::chrono::high_resolution_clock::now();
    auto adjMatrixPath = pathBtwnPoints(from, to, adjMatrix);
    std::string adjMatrixPathStr = from;
    for(int i = 0; i < adjMatrixPath.size(); i++){
        adjMatrixPathStr += " -> " + adjMatrixPath[i].second + " -> " + adjMatrixPath[i].first;
    }
    std::cout << "Pathed (AM)" << std::endl;
    auto adjMatrixPathTime = std::chrono::high_resolution_clock::now();

    // TIMING
    int duration = (std::chrono::duration_cast<std::chrono::seconds>(std::chrono::high_resolution_clock::now() - startTime)).count();

    int alMakeTime = (std::chrono::duration_cast<std::chrono::seconds>(adjListMadeTime - startTime)).count();
    int alPathTime = (std::chrono::duration_cast<std::chrono::seconds>(adjListPathTime - adjListMadeTime)).count();
    int amMakeTime = (std::chrono::duration_cast<std::chrono::seconds>(adjMatrixMadeTime - adjListPathTime)).count();
    int amPathTime = (std::chrono::duration_cast<std::chrono::seconds>(adjMatrixPathTime - adjMatrixMadeTime)).count();
    // returns Adjacency matrix path, adjacency list path
    //         total time, pathing times, matrix times
    //         as vector of strings
    std::cout << "Returning vector" << std::endl;
    std::vector<std::string> returnVector;
    returnVector.push_back(adjListPathStr);
    returnVector.push_back(adjMatrixPathStr);
    returnVector.push_back(std::to_string(duration));
    returnVector.push_back(std::to_string(alMakeTime));
    returnVector.push_back(std::to_string(amMakeTime));
    returnVector.push_back(std::to_string(alPathTime));
    returnVector.push_back(std::to_string(amPathTime));
    return returnVector;
}

void FicCSV::writePathToFrontend(std::string from, std::string to, std::string filePath){
    std::vector<std::string> info = createGraphThenPath(from, to);

    if(info[0] == from){
        info[0] = "NOT CONNECTED, NO PATH FOUND";
        info[1] = "NOT CONNECTED, NO PATH FOUND";
    }
    // OUTPUT FILE PRETTY
    info[0] = "Adjacency List Path: " + info[0];
    info[1] = "Adjacency Matrix Path: " + info[1];
    info[2] = "Total Duration: " + info[2]+" seconds";
    info[3] = "Adjacency List Creation Time: " + info[3]+" seconds";
    info[4] = "Adjacency Matrix Creation Time: " + info[4]+" seconds";
    info[5] = "Adjacency List Path Time: " + info[5]+" seconds";
    info[6] = "Adjacency Matrix Path Time: " + info[6]+" seconds";
    

    std::ofstream file(filePath);
    for(int i = 0; i < info.size(); i++){
        std::string line = info[i];
        for(int j = 0; j < line.size(); j++){
            file << line[j];
        }
        file << ",";
    }
    file.close();

    std::ofstream file2("../src/components/toggle.txt");
    file2<<"Y";
    file2.close();
}