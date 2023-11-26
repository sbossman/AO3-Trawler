//
// Created by summe on 11/26/2023.
//
#pragma once
#include <string>
#include <vector>
#include <ifstream>
#include <iostream>

#ifndef AO3_TRAWLER_FICCSV_H
#define AO3_TRAWLER_FICCSV_H


class FicCSV {
private:
    std::string edgeListFile;
    std::string tagKeyFile;
    std::string ficKeyFile;


public:
    FicCSV(std::string edgelist, std::string tagKey, std::string ficKey);
};


#endif //AO3_TRAWLER_FICCSV_H
