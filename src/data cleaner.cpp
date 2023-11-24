#include <algorithm>
#include <iostream>
#include <fstream>
#include <unordered_map>
#include <unordered_set>
#include <string>
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


int main() {
	regex validAlphanum("^[a-zA-Z0-9_!+()&@#'?\":\\[|\\]!.;/ \\-]+,[a-zA-Z0-9_!+()@#&'?\":|!\\[|\\].;/ \\-]+$"); //a regex for letters, numbers, and acceptable symbols, THEN A COMMA, 
																												 //then another set of letters, numbers, and acceptable symbols
	ifstream inputFile;
	inputFile.open("rawTaglist.csv");
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
}
