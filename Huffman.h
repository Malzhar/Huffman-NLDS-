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

	//Creating a node in a binary tree. every node has a left and right child
	//a character value(i.e. the symbol) and a weight(i.e. the amount of times that the character as appeared in the text)
	struct node {
		char symbol;
		int weight; 
		node* left;
		node* right; 
	};

	//creating an array of 256 nodes: each node has a left and right child, a weight and a symbol. 
	node* arr[256]; 
};
