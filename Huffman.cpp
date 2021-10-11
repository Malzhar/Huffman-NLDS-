#include "Huffman.h"
#include <iostream>
#include <fstream> 
#include <iomanip>


void Huffman::displayHelp() {
	cout << "The -m switch determines the mode, and will be one of:\n"
		 << "-me encode a file\n"
		 << "-md decode a file\n"
		 << "-mt build a tree-builder from a file\n"
		 << "-met encode a file with a specified tree-builder file\n"
		 << "-m followed by anything other than e, d, t or, et is not valid\n"
		 << "To specify the input file: -i:<filename>\n"
		 << "To specify the output file: -o:<filename>\n"
		 << "To specify the tree-builder input file: -t<filename>\n"
		 << "To ask for help: -h or -? or -help" << endl;


}

void Huffman::EncodeFile(string inputFile, string outputFile) {

	//cout << "Made it into the EncodeFile function!" << endl; 

// Trying to take an inputfile, encode it and put the encoded version into an output file. In order to do this
// we need to take input from the command line using ifstream. We need to make sure that the given input file is valid
// and if it is then we can continue. if not we need to output an error message and exit. If the file can be opened 
// then we need to scan through the file and count the frequency(occurences) of each character(symbol) in the file. 
// The number of occurences is essentially the weight of each character. We need to know the weight because we want to 
// know how many times each of the symbols appears in the file. Once we have scanned through the entire file, we can
// use the number of occurences to build a collection of nodes where each node represents the symbol and the 
// weight(count) of that symbol. 
//  
//   
// 

	ifstream in;						// how we can get input from a file, "in" is the name we have chosen to use. 
	in.open(inputFile, ios::binary);	// opening the given input file

	if (!in.good()) {					// checking the input file for validity. If the file is not valid 
		printf("File not found\n");		// we output an error message and then exit. 
		exit(1); 
	}

	cout << "We were able to open the file" << endl; 

// If we have made it here then we know that the given file is valid. Therefore, we can go ahead and create an array
// of 256 nodes. Each node has a left and right child pointer, a character(symbol) and weight(the amount of times that
// each give character(symbol) has appeared in the input file)  
						
	char symbol;
 
	for (int i = 0; i < 256; i++) {
		arr[i] = new node;			// creating 256 nodes, i.e. arr[0]...arr[255] are a new node
		arr[i]->weight = 0;			// initializing the weight(count) of each new node to 0.
		arr[i]->symbol = i;			// intializing the symbol to represent 1 ASCII symbol where i represents the ascii value of the character in decimal. 
		arr[i]->left = NULL;		// each node's left and right child is initialized to NULL since they arent connected to anything yet. 
		arr[i]->right = NULL; 
	}
	in.get(symbol);					// need to get the next symbol.  


// WHILE we have not reached the end of the file, scan through the entire file char by char.
// For every char that we come across, increase the weight of the char.     
	while (!in.eof()) {
		arr[(unsigned char)symbol]->weight++;	// Go to the next char and increment the weight of the ascii value node
		in.get(symbol); 
	}
	in.close(); 
	 
	for (int i = 0; i < 32; i++) {
		cout << setw(3) << i << setw(7) << arr[i] << " || "
			<< setw(3) << i + 32 << setw(7) << arr[i + 32] << " || "
			<< setw(3) << i + 64 << setw(7) << arr[i + 64] << " || "
			<< setw(3) << i + 96 << setw(7) << arr[i + 96] << " || "
			<< setw(3) << i + 128 << setw(7) << arr[i + 128] << " || "
			<< setw(3) << i + 160 << setw(7) << arr[i + 160] << " || "
			<< setw(3) << i + 192 << setw(7) << arr[i + 192] << " || "
			<< setw(3) << i + 224 << setw(7) << arr[i + 224] << endl;
	}
}

void Huffman::DecodeFile(string inputFile, string outputFile) {
	cout << "You are getting into the DecodeFile function!" << endl;

	ifstream in;						 
	in.open(inputFile, ios::binary);

	if (!in.good()) {				 
		printf("File not found\n");  
		exit(1);
	}
}

void Huffman::EncodeFileWithTree(string inputFile, string TreeFile, string outputFile) {
	cout << "You are getting into the EncodeFileWithTree function" << endl;

	ifstream in;						 
	in.open(inputFile, ios::binary);

	if (!in.good()) {				 
		printf("File not found\n");  
		exit(1);
	}
}

void Huffman::MakeTreeBuilder(string inputFile, string outputFile) {
	cout << "You are getting into the MakeTreeBuilder function" << endl; 

	ifstream in;						 
	in.open(inputFile, ios::binary);

	if (!in.good()) {				 
		printf("File not found\n");  
		exit(1);
	}

	char symbol;

	for (int i = 0; i < 256; i++) {
		arr[i] = new node;			// creating 256 nodes, i.e. arr[0]...arr[255] are a new node
		arr[i]->weight = 0;			// initializing the weight(count) of each new node to 0.
		arr[i]->symbol = i;			// intializing the symbol to represent 1 ASCII symbol where i represents the ascii value of the character in decimal. 
		arr[i]->left = NULL;		// each node's left and right child is initialized to NULL since they arent connected to anything yet. 
		arr[i]->right = NULL;
	}
	in.get(symbol);					// need to get the next symbol.

// WHILE we have not reached the end of the file, scan through the entire file char by char.
// For every char that we come across, increase the weight of the char.
	while (!in.eof()) {
		arr[(unsigned char)symbol]->weight++;	// Go to the next char and increment the weight of the ascii value node
		in.get(symbol);
	}
	in.close();

	// Now that we have reached the end of the file and have made our 256 nodes, we can start the building of our Huffman tree.
	// To build a Huffman tree:
	// a.) Start with the leaves of the tree.
	// b.) Find the 2 nodes that hold the smallest weights and save the weights and indexs.
	//		i.) To find the two smallest weights and their indexs:
	//			Loop back through the 256 nodes and compare the current weight to the smallest weight. 
	//			If the weight at the current node is smaller than the current smallest weight, then the current node is the smallest weight
	//			save the weight and the index of that node. 		 
	// c.) Once the two lowest weighted nodes are found. Create an internal node whose weight is the sum of the two lowest weights and whose
	//	   left child points to the lowest index node and right child points to the next lowest weighted node. 
	// d.) Make the higher index node point to NULL.
	//
	//

	int smallest = 0;				// Variable to hold the weight value of the smallest weighted node.
	int secondSmall = 0;			// Variable to hold the weight value of the next smallest weighted node. 
	int smallestIndex;				// Variable to hold the postion of the smallest weighted node.
	int secondSmallestIndex;		// Variable to hold the postion of the next smallest weighted node.

	// While the is more than one singular node in the entire array of nodes, keep looping through to find the lowest weight values to create
	// a subtree
	// while(the array has more than 1 node) {}
	for (int i = 0; i < 256; i++) {
		// If the weight of the current node is smaller than the current smallest node:   
		if (arr[i]->weight < smallest) {
			secondSmall = smallest;				// Make the current smallest weight the second smallest.
			smallest = arr[i]->weight;			// Make the smallest weight be equal to the current node's weight.
			smallestIndex = i; 	 				// Save the current position of the node to be used to assign the internal nodes left child.
		}
		// Else, if the weight of the current node is less than the secondSmall:
		else if (arr[i]->weight < secondSmall) {
			secondSmall = arr[i]->weight;		// Make the second smallest weight equal to the current node. 
			secondSmallestIndex = i;			// Save the current position of the node to be used to assign the internal nodes right child. 
		}
		// Need to make sure that the smallest index is the actual smallest index. If it is not, need to swap the index's. 
		if (smallestIndex > secondSmallestIndex) {
			int temp;								// Variable to hold one of the index's, so that a swap can be made.
			temp = smallestIndex;					
			smallestIndex = secondSmallestIndex;	// Since secondSmallestIndex < smallestIndex, they need to be swapped.
			secondSmallestIndex = temp; 

		}
		// Once we have found the two smallest weights in the array of nodes:
		// 1.) Create an interal node whose weight is the sum of the two smallest weights.
		// 2.) Internal nodes left child is the smallest index of the two lowest weighted values.
		// 3.) Internal nodes right child is the next smallest index of the two lowest weighted values. 
		// 
		node* internalNode = new node;							// Making a new internal node that acts as the parent to the two lowest weighted nodes.
		internalNode->weight = smallest + secondSmall;			// The weight of the internal node is the sum of the two lowest weighted nodes. 
		internalNode->left = arr[smallestIndex];				// Need to point the left child of the internal node to.......
		internalNode->right = arr[secondSmallestIndex];			// Need to point the right child of the internal node to.......

	}


}


