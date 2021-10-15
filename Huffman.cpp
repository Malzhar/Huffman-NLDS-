#include "Huffman.h"
#include <iostream>
#include <fstream> 
#include <iomanip>

Huffman::Huffman() {
	root = arr[0]; 
}

Huffman::~Huffman() {

}

void Huffman::displayHelp() {
// This function displays the appropriate command line inputs that are valid. 

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
// To Encode a file:
//	1. Start by making sure that the file given is valid and can be opened.
//	2. Create an array of 256 nodes.
//	3. Parse through the file and count the increment the weight of the char's & and put them at the proper index in the node array.
//	4. Build the Huffman Tree:
//		a. Find the two lowest weighted nodes in the entire node array.
// 		b. Create an internal node:
//			i. Weight of the internal node is the sum of the two lowest weighted nodes.
// 			ii. Internal node left child points to the lowest index node & right child points to the next lowest index node. 
// 			iii. Once internal node is created and set appropriately, point the min2 node point to NULL. 
//	5. Traverse the Huffman Tree to create/store the variable length bit strings in a string array.
//	6. Then we need to write those variable length bits strings to an output file.  
//
	ifstream in;												// how we can get input from a file, "in" is the name we have chosen to use. 
	in.open(inputFile, ios::binary);							// opening the given input file

	if (!in.good()) {											// checking the input file for validity. If the file is not valid 
		printf("File not found\n");								// output an error message and then exit. 
		exit(1);
	}

	char symbol;
	for (int i = 0; i < 256; i++) {
		arr[i] = new node;										// creating 256 nodes, i.e. arr[0]...arr[255] are a new node
		arr[i]->weight = 0;										// initializing the weight(count) of each new node to 0.
		arr[i]->symbol = i;										// intializing the symbol to represent 1 ASCII symbol where i represents the ascii value of the character in decimal. 
		arr[i]->left = NULL;									// each node's left and right child is initialized to NULL since they arent connected to anything yet. 
		arr[i]->right = NULL;
	}
	in.get(symbol);												// need to get the next char.  

	while (!in.eof()) {
		arr[(unsigned char)symbol]->weight++;					// Go to the next char and increment the weight.
		in.get(symbol);
	}
	in.close();													// Close the file. 

// Build a Huffman Tree

	int smallestIndex = 0;										// Variable to hold the postion of the smallest weighted node.
	int secondSmallestIndex = 0;								// Variable to hold the postion of the next smallest weighted node.
	int iterations = 0;											// Variable to count the amount of times we are iterated through the loop.

	while (iterations < 255) {
		int smallest = INT_MAX;									// Variable to hold the weight value of the smallest weighted node.
		int secondSmall = INT_MAX;								// Variable to hold the weight value of the next smallest weighted node. 
		for (int i = 0; i < 256; i++) {							// Checking for the SMALLEST node in the node array. 
			if (arr[i] == NULL) {								// If he index we are at is NULL, then skip this index and go to the next one.
				continue;
			}
			if (arr[i]->weight < smallest) {					// If the weight of the current node is smaller than the current smallest node:
				smallest = arr[i]->weight;						// Make the smallest weight be equal to the current node's weight.
				smallestIndex = i; 	 							// Save the current position of the node to be used to assign the internal nodes left child.
			}
		}
		for (int i = 0; i < 256; i++) {							// Checking for the SECOND SMALLEST weighted node in the node array. 
			if (i == smallestIndex) {
				continue;
			}

			if (arr[i] == NULL) {								// If he index we are at is NULL, then skip this index and go to the next one.
				continue;
			}

			if (arr[i]->weight < secondSmall) {					// If the weight of the current node is less than the secondSmall:
				secondSmall = arr[i]->weight;					// Make the second smallest weight equal to the current node. 
				secondSmallestIndex = i;						// Save the current position of the node to be used to assign the internal nodes right child. 
			}
		}

		if (smallestIndex > secondSmallestIndex) {				// Need to make sure that the smallest index is the actual smallest index. If it is not, need to swap the index's.
			int temp;											// Variable to hold one of the index's, so that a swap can be made.
			temp = smallestIndex;
			smallestIndex = secondSmallestIndex;				// Since secondSmallestIndex < smallestIndex, they need to be swapped.
			secondSmallestIndex = temp;
		}
// Once we have found the two smallest weights in the array of nodes:
//	1. Create an interal node whose weight is the sum of the two smallest weights.
//	2. Internal nodes left child is the smallest index of the two lowest weighted values.
//	3. Internal nodes right child is the next smallest index of the two lowest weighted values. 

		node* internalNode = new node;							// Making a new internal node that acts as the parent to the two lowest weighted nodes.
		internalNode->weight = (smallest + secondSmall);		// The weight of the internal node is the sum of the two lowest weighted nodes. 
		internalNode->left = arr[smallestIndex];
		internalNode->right = arr[secondSmallestIndex];
		arr[smallestIndex] = internalNode;						// Connect the internal node to the lowest index in node array. 
		arr[secondSmallestIndex] = NULL;						// Make second highest index point to NULL
		iterations++;											// increment the iterations. 
	}
	node* root = arr[0];
	inorderTraversal(root);
	for (int i = 0; i < 256; i++) {
		cout << i << " " << arr_s[i] << endl;
	}
}
	


void Huffman::DecodeFile(string inputFile, string outputFile) {
// To decode a file:
//	
//

	ifstream in;
	in.open(inputFile, ios::binary);

	if (!in.good()) {
		printf("File not found\n");
		exit(1);
	}
}

void Huffman::EncodeFileWithTree(string inputFile, string TreeFile, string outputFile) {
//To encode a file with a specified tree builder file: 
//	1. Make sure that the give file can be opened.
// 	2. 
// 510-bytes are a sequence of index's, if first 2 indices are 9 & 11, combined nodes at 9 and 11. 

	ifstream in;
	in.open(inputFile, ios::binary);

	if (!in.good()) {
		printf("File not found\n");
		exit(1);
	}
}

void Huffman::MakeTreeBuilder(string inputFile, string outputFile) {
// To make a tree builder:
//	1. Make sure that the given file can be opened. 
//	2. Create an array of 256 nodes.
//	3. Store the weight, char at the appropriate index in the node array. 
//	4. Build the Huffman Tree:
//		a. Find the two lowest weighted nodes in the entire node array.
// 		b. Create an internal node:
//			i. Weight of the internal node is the sum of the two lowest weighted nodes.
// 			ii. Internal node left child points to the lowest index node & right child points to the next lowest index node. 
// 			iii. Once internal node is created and set appropriately, point the min2 node point to NULL. 
// 
//
	 
	ifstream in;
	in.open(inputFile, ios::binary);
	if (!in.good()) {
		printf("File not found\n");
		exit(1);
	}

	char symbol;
	for (int i = 0; i < 256; i++) {
		arr[i] = new node;							// creating 256 nodes, i.e. arr[0]...arr[255] are a new node
		arr[i]->weight = 0;							// initializing the weight(count) of each new node to 0.
		arr[i]->symbol = i;							// intializing the symbol to represent 1 ASCII symbol where i represents the ascii value of the character in decimal. 
		arr[i]->left = NULL;						// each node's left and right child is initialized to NULL since they arent connected to anything yet. 
		arr[i]->right = NULL;
	}
	in.get(symbol);									// need to get the next symbol.

	while (!in.eof()) {
		arr[(unsigned char)symbol]->weight++;		// Go to the next char and increment the weight of the ascii value node
		in.get(symbol);
	}
	in.close();										// Close the file.   
	
// Build Huffman Tree:
	int smallestIndex = 0;							// Variable to hold the postion of the smallest weighted node.
	int secondSmallestIndex = 0;					// Variable to hold the postion of the next smallest weighted node.
	int iterations = 0;								// Variable to count the amount of times we are iterated through the loop.

	while (iterations < 255) {
		int smallest = INT_MAX;						// Variable to hold the weight value of the smallest weighted node.
		int secondSmall = INT_MAX;					// Variable to hold the weight value of the next smallest weighted node. 

		for (int i = 0; i < 256; i++) {				// Checking for the SMALLEST weight in the node array. 

			if (arr[i] == NULL) {					// If he index we are at is NULL, then skip this index and go to the next one.
				continue;
			}

			if (arr[i]->weight < smallest) {		// If the weight of the current node is smaller than the current smallest node:
				smallest = arr[i]->weight;			// Make the smallest weight be equal to the current node's weight.
				smallestIndex = i; 	 				// Save the current position of the node to be used to assign the internal nodes left child.
				arr_i[i] = smallestIndex;			// Storing the min1 index into an integer array for the tree building information. 
			} 
		}	

		for (int i = 0; i < 256; i++) {				// Checking for the SECOND SMALLEST weight in the node array. 

			if (i == smallestIndex) {
				continue; 
			}

			if (arr[i] == NULL) {					// If he index we are at is NULL, then skip this index and go to the next one.
				continue;
			}
	
			if (arr[i]->weight < secondSmall) {		// If the weight of the current node is less than the secondSmall:
				secondSmall = arr[i]->weight;		// Make the second smallest weight equal to the current node.  
				secondSmallestIndex = i;			// Save the current position of the node to be used to assign the internal nodes right child. 
				arr_i[i] = secondSmallestIndex;		// Storing the min2 index into an integer array for the tree building information. 
			} 	 
		}
 

		if (smallestIndex > secondSmallestIndex) {	// Checking that the SMALLEST index is the actual SMALLEST index
			int temp;								// Variable to hold one of the index's, so that a swap can be made.
			temp = smallestIndex;
			smallestIndex = secondSmallestIndex;	// Since secondSmallestIndex < smallestIndex, they need to be swapped.
			secondSmallestIndex = temp;
		}

		// cout << arr_i[smallestIndex] << arr_i[secondSmallestIndex] << endl;
 
		
// Once we have found the two smallest weights in the array of nodes:
//	1. Create an interal node whose weight is the sum of the two smallest weights.
//	2. Internal nodes left child is the smallest index of the two lowest weighted values.
//	3. Internal nodes right child is the next smallest index of the two lowest weighted values. 

			node* internalNode = new node;							// Making a new internal node that acts as the parent to the two lowest weighted nodes.
			internalNode->weight = (smallest + secondSmall);		// The weight of the internal node is the sum of the two lowest weighted nodes. 
			internalNode->left = arr[smallestIndex];				
			internalNode->right = arr[secondSmallestIndex];	 
			arr[smallestIndex] = internalNode;						// Connect internal node to the SMALLEST index.
			arr[secondSmallestIndex] = NULL;						// Make SECOND SMALLEST index NULL.
			iterations++;											// incrementing the iterations. 
	}

	 node* root = arr[0];
	 inorderTraversal(root);

	 ofstream out;
	 out.open(outputFile, ios::binary);

	 if (!out.good()) {
		 printf("File not found\n");
		 exit(1);
	 }
// While the integer array still has values in it, getting writing to the file, once the end of the array is reached. Stop writing and exit
// close the file. 

	 for (int i = 0; i < 256; i++) {
		 out.put(arr_i[i]); 
	}
	 
	 out.close();

	// for (int i = 0; i < 256; i++) {								
	//	 cout << i << " " << arr_s[i] << endl;
	// }
}

void Huffman::inorderTraversal(node* p) {					 
// Bit string creation:
//	1. Use a variable that holds the path that we take to each leaf node.
//	2. Append/pop_back "0's" & "1's" as we are traversing the tree. 		
//	 REMEMBER:
//	 a. LEFT MEANS 0
//	 B. RIGHT MEANS 1
			 
	//Traverse the left subtree
	if (p->left != NULL) {			
		path.append(1, '0');								// Everytime we go left, append a '0' to the string.		 
		inorderTraversal(p->left);	
	}  
	// Traverse the right subtree
	if (p->right != NULL) {			 
		path.append(1, '1');								// Everytime we go right append a '1' to the string.		 
		inorderTraversal(p->right);	
	}  
	if (p->left == NULL && p->right == NULL) {
		arr_s[(unsigned char)p->symbol] = path;				// Storing the bit strings in the string array. 
	} 

	if (p != arr[0]) {
		path.pop_back();									// erase last previously appended char
	}
}
 
// BRAINSTORMING SECTION: 
//	1. Need to rememeber about padding the bit strings:
//		Between 1 - 7 padding bits for an 8-bit byte
//
