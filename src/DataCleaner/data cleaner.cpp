#include <algorithm>
#include <iostream>
#include <fstream>
#include <unordered_map>
#include <unordered_set>
#include <string>
#include <limits>
#include <vector>
#include <regex>
using namespace std;

//checks if the passed in string is not in the passed in set, returns true if it's not in the set.
bool checkUnique(unordered_set<string>& inputSet, string inputString) {
	if (inputSet.find(inputString) == inputSet.end()) {
		return true;
	}
	else {
		return false;
	}
}

//returns a pair based on the input string, where .first is the edge and .second is the tag
pair<string, string> getEdgeTag(string input) {
	int commaOnePos = input.find(',');
	int commaTwoPos = input.find(',', commaOnePos + 1);
	string edge = input.substr(0, commaTwoPos);
	string tag = input.substr(commaTwoPos + 1, input.size() - commaTwoPos - 1);
	return { edge, tag };
}


int main() {
	int inputSelection;
	string input;
	cout << "1. Raw to edgelist" << endl << "2. Optimize existing edgelist" << endl << "3. Verify uniqueness of csv" << endl;
	cout << "Selection: ";
	cin >> input;
	inputSelection = stoi(input);

	if (inputSelection == 1) {
		regex validAlphanum("^[a-zA-Z0-9_!+()&@#'?\":\\[|\\]!.;/ \\-]+,[a-zA-Z0-9_!+()@#&'?\":|!\\[|\\].;/ \\-]+$"); //a regex for letters, numbers, and acceptable symbols, THEN A COMMA, 
		//then another set of letters, numbers, and acceptable symbols
		ifstream inputFile;
		inputFile.open("RawTaglist.csv");
		if (inputFile.is_open()) {
			cout << "Commencing the input scan." << endl;
			int titleCounter = 0;
			int tagCounter = 0;
			int commaIndex;
			int mappedTagValue;
			int mappedTitleValue;
			unordered_map<int, string> intToTitle; // a translation table from key to name of the work
			unordered_map<int, string> intToTag; // a translation table from key to name of the tag
			unordered_map<string, int> tagToInt;

			unordered_map<int, vector<int>> sharedTagmap; // a map where each key represents all the works with that tag
			//key -> an int from intToTag, representing a tag.
			//value -> a list of numbers, where each number is a title from intToTitle, representing a title. all numbers in the list are connected to each other.

			unordered_set<string> allTitles;
			unordered_set<string> allTags;
			string inputLine;
			string title;
			string tag;
			bool uniqueTitle;
			bool uniqueTag;
			getline(inputFile, inputLine); //burn the header of the file

			//------------------- READING THE RAW DATA -------------------//
			int counter = 0;
			while (getline(inputFile, inputLine)) { // take in a line
				if (regex_match(inputLine, validAlphanum)) { // if the line is valid to be taken as input
					commaIndex = inputLine.find(',');
					title = inputLine.substr(0, commaIndex); // cut up the input line to get the title
					tag = inputLine.substr(commaIndex + 1, inputLine.size() - commaIndex); //cut up the input line to get the tag
					uniqueTitle = checkUnique(allTitles, title);
					uniqueTag = checkUnique(allTags, tag);
					if (uniqueTitle) {
						allTitles.insert(title); //put title into set of all titles
						intToTitle[titleCounter] = title; //give it a spot on the int to title map
						titleCounter++;
					}
					if (uniqueTag) {
						allTags.insert(tag); //put tag into set of all tags
						intToTag[tagCounter] = tag; //give it a spot on the int to tag map
						tagToInt[tag] = tagCounter;
						tagCounter++;
					}
					mappedTagValue = tagToInt[tag]; //get int val of current tag
					mappedTitleValue = titleCounter - 1; //get int val of current title
					sharedTagmap[mappedTagValue].push_back(mappedTitleValue); //add the int representing the title to the list of ints keyed by the int representing the tag
				}
			}
			inputFile.close();

			cout << "Input scanning complete." << endl;


			//------------------- OUTPUTTING THE EDGE LIST -------------------//
			ofstream outputEdgeFile;
			outputEdgeFile.open("EdgeList.csv");
			if (outputEdgeFile.is_open()) {
				cout << "Commencing edge list generation." << endl;
				auto sharedIter = sharedTagmap.begin();
				int sharedCounter = 0;
				auto listIterLinear = sharedTagmap[0].begin();
				auto listIterSquare = sharedTagmap[0].begin();
				int tenPercentThreshold = sharedTagmap.size() / 10;
				while (sharedIter != sharedTagmap.end()) { //iterate each key in the map
					listIterLinear = sharedIter->second.begin();
					while (listIterLinear != sharedIter->second.end()) { //iterate each key's vector
						listIterSquare = sharedIter->second.begin();
						while (listIterSquare != sharedIter->second.end()) { // iterate each key's vector per element in the vector (n^2)
							if (listIterLinear != listIterSquare) {
								outputEdgeFile << *listIterLinear << "," << *listIterSquare << "," << sharedIter->first << endl;
							}
							listIterSquare++;
						}
						listIterLinear++;
					}
					sharedIter++;
					sharedCounter++;
					if (sharedCounter % 100 == 0) {
						cout << "Tag " << sharedCounter << " complete." << endl;
					}
					if (sharedCounter == tenPercentThreshold) {
						cout << "!!!!!! TEN PERCENT COMPLETE !!!!!!" << endl;
					}
					if (sharedCounter == (3 * tenPercentThreshold)) {
						cout << "!!!!!! THIRTY PERCENT COMPLETE !!!!!!" << endl;
					}
					if (sharedCounter == (5 * tenPercentThreshold)) {
						cout << "!!!!!! FIFTY PERCENT COMPLETE !!!!!!" << endl;
					}
					if (sharedCounter == (7 * tenPercentThreshold)) {
						cout << "!!!!!! SEVENTY PERCENT COMPLETE !!!!!!" << endl;
					}
				}
			}
			outputEdgeFile.close();
			cout << "Edge file output complete." << endl;

			//------------------- OUTPUTTING THE TAG TRANSLATION KEY -------------------//
			ofstream outputIntToTag;
			outputIntToTag.open("IntToTagTranslator.csv");
			if (outputIntToTag.is_open()) {
				int tagTranslatorCounter = 0;
				while (tagTranslatorCounter < intToTag.size()) {
					outputIntToTag << tagTranslatorCounter << "," << intToTag[tagTranslatorCounter] << endl;
					tagTranslatorCounter++;
				}
			}
			outputIntToTag.close();
			cout << "Tag translation key generation complete." << endl;

			//------------------- OUTPUTTING THE TITLE TRANSLATION KEY -------------------//
			ofstream outputIntToTitle;
			outputIntToTitle.open("IntToTitleTranslator.csv");
			if (outputIntToTitle.is_open()) {
				int titleTranslatorCounter = 0;
				while (titleTranslatorCounter < intToTitle.size()) {
					outputIntToTitle << titleTranslatorCounter << "," << intToTitle[titleTranslatorCounter] << endl;
					titleTranslatorCounter++;
				}
			}
			outputIntToTitle.close();
			cout << "Title translation key generation complete." << endl;

			return 1;
		}
		else {
			cout << "Warning. RawTaglist.csv not found. Please provide a RawTaglist.csv file first." << endl;
			cout << "A RawTaglist.csv file can be produced by using the sitemap.txt file provided in the source code on the Webscraper.io web extension." << endl;
			cout << "The RawTaglist.csv file can then be provided to the program by placing it in the file alongside the source code." << endl;
			return -1;
		}
	}

	if (inputSelection == 2) {

		ifstream inputFile;
		inputFile.open("EdgeList.csv");

		ofstream outputFile;
		outputFile.open("ReducedEdgeList.csv");

		unordered_set<string> existingEdges;
		string edge;
		string tag;
		string lastTag;
		string inputLine;
		pair<string, string> parsedInput;

		cout << "How large would you like the reduced file to be? Write 'MAX' if you want to process the whole file." << endl;
		cin >> input;
		if (input == "MAX") {
			inputSelection = INT_MAX;
		}
		else {
			inputSelection = stoi(input);
		}

		if (inputFile.is_open()) {
			while (true) {
				if (!getline(inputFile, inputLine)) {
					break;
				}
				parsedInput = getEdgeTag(inputLine);
				edge = parsedInput.first;
				tag = parsedInput.second;
				if (lastTag != tag && existingEdges.size() > inputSelection) {
					break;
				}
				if (existingEdges.find(edge) == existingEdges.end()) { //if the edge is not currently in the set
					existingEdges.insert(edge);
					outputFile << edge << "," << tag << endl;
				}
				lastTag = tag;
			}
			cout << "Optimization complete." << endl;
			cout << "Note, reduced file may be marginally larger than the number of lines specified above as tags must be processed completely and cannot be interrupted during processing." << endl;
			return 2;
		}
		else {
			cout << "Warning. EdgeList.csv not found. Please run command 1 to produce an edge list file first." << endl;
			return -1;
		}
	}

	if (inputSelection == 3) {
		string edge;
		string tag;
		string inputLine;
		pair<string, string> parsedInput;
		unordered_set<string> existingEdges;
		bool stillUnique = true;
		int lineCounter = 0;
		ifstream inputFile;
		cout << "Verify 1. EdgeList.csv or 2. ReducedEdgeList.csv?" << endl;
		cout << "Selection: ";
		cin >> input;
		inputSelection = stoi(input);
		
		if (inputSelection == 1) {
			inputFile.open("EdgeList.csv");
		}

		if (inputSelection == 2) {
			inputFile.open("ReducedEdgeList.csv");
		}

		if (inputFile.is_open()) {
			while (stillUnique && getline(inputFile, inputLine)) {
				lineCounter++;
				parsedInput = getEdgeTag(inputLine);
				edge = parsedInput.first;
				if (existingEdges.find(edge) == existingEdges.end()) { //if the edge is not currently in the set
					existingEdges.insert(edge);
				}
				else {
					stillUnique = false;
				}
			}

			if (!stillUnique) {
				cout << "Warning. File not unique. Parallel edge found on line " << lineCounter << endl;
				cout << "Violating line: " << inputLine << endl;
				return 3;
			}
			else {
				cout << "File is completely unique." << endl;
				cout << "Set size: " << existingEdges.size() << endl;
				return 3;
			}
		}
		else {
			cout << "invalid selection, or file not found." << endl;
			return -1;
		}
	}


	return 4;
}
