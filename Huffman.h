#pragma once

#include <string>

using namespace std;
class Huffman {

public:

	void MakeTreeBuilder(string inputFile, string outputFile);
	void EncodeFile(string inputFile, string outputFile);
	void DecodeFile(string inputFile, string outputFile);
	void EncodeFileWithTree(string inputFile, string TreeFile, string outputFile);
	void displayHelp();


private:

	struct node {

		char symb;
		int weight; 
		node* left;
		node* right; 

	};

};