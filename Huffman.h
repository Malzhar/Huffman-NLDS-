#pragma once

#include <string>

using namespace std;


class Huffman {

public:

	Huffman();
	~Huffman(); 
	void MakeTreeBuilder(string inputFile, string outputFile);
	void EncodeFile(string inputFile, string outputFile);
	void DecodeFile(string inputFile, string outputFile);
	void EncodeFileWithTree(string inputFile, string TreeFile, string outputFile);
	void displayHelp();

private:

//Creating a node in a binary tree:
// a. Every node has a left and right child.
// b. Every node has a symbol, i.e. character value
// c. Every node has a weight, i.e. frequency of char occurences. 
	struct node {
		char symbol;
		int weight;
		node* left;
		node* right;
	};

	node* arr[256];
	node* root = arr[0]; 
	string path;					// Variable that is going to hold the bit string. 
	string arr_s[256];  
	int arr_i[510]; 
	void inorderTraversal(node* p); 
};