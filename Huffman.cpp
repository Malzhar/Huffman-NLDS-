#include "Huffman.h"
#include <iostream>
#include <fstream> 
#include <iomanip>

Huffman::Huffman() {
	//root = NULL;
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

	ifstream in;
	ofstream out;
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

	in.get(symbol);
	while (!in.eof()) {
		arr[(unsigned char)symbol]->weight++;					// Go to the next char and increment the weight.
		in.get(symbol);
	}
	in.close();													// Close the file. 

// Build a Huffman Tree

	int smallestIndex = 0;										// Variable to hold the postion of the smallest weighted node.
	int secondSmallestIndex = 0;								// Variable to hold the postion of the next smallest weighted node.
	int iterations = 0;											// Variable to count the amount of times we are iterated through the loop.
	int counter = 0;

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
		arr_i[counter] = smallestIndex;
		arr_i[counter + 1] = secondSmallestIndex;

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
		counter += 2;
	}

	node* root = arr[0];
	inorderTraversal(root);										// Traverse Tree to get sequences. 

	in.open(inputFile, ios::binary);
	if (!in.good()) {
		printf("File not found\n");
		exit(1);
	}
	out.open(outputFile, ios::binary);
	if (!out.good()) {											// Checking that output 
		printf("File not found\n");
		exit(1);
	}

	string buffer = "";
	while (!in.eof()) {

		in.get(symbol);											// Get the next symbol 
		buffer.append(arr_s[symbol]);							// Append the bitstring to the buffer

		while (buffer.length() > 7) {
			unsigned char b = 0;

			if (buffer[0] == '1') b |= (1 << 7);					// 128
			if (buffer[1] == '1') b |= (1 << 6);					// 64
			if (buffer[2] == '1') b |= (1 << 5);					// 32
			if (buffer[3] == '1') b |= (1 << 4);					// 16
			if (buffer[4] == '1') b |= (1 << 3);					// 8
			if (buffer[5] == '1') b |= (1 << 2);					// 4 
			if (buffer[6] == '1') b |= (1 << 1);					// 2
			if (buffer[7] == '1') b |= (1 << 0);					// 1

			out.put(b);											// Write the char to the file. 
			buffer.erase(0, 8);									// Erasing the 8-bits 
		}
	}

	if (buffer.length() > 0) {									// Buffer still have bits in it after end of file is reached. 
		for (int i = 0; i < 256; i++) {							// Loop through entire bitstring array
			if (7 < arr_s[i].length()) {						// if bit string is greater than 7
				buffer.append(arr_s[i]);						// append to end of the buffer.

				unsigned char b = 0;
				if (buffer[0] == '1') b |= (1 << 7);					
				if (buffer[1] == '1') b |= (1 << 6);					
				if (buffer[2] == '1') b |= (1 << 5);					
				if (buffer[3] == '1') b |= (1 << 4);					
				if (buffer[4] == '1') b |= (1 << 3);					
				if (buffer[5] == '1') b |= (1 << 2);					 
				if (buffer[6] == '1') b |= (1 << 1);					
				if (buffer[7] == '1') b |= (1 << 0);					
				out.put(b);
				buffer.erase(0, buffer.length());
				break;
			}
		}
	}

	in.close();													// Close the input file.

	int treeCounter = 0;										// Counter for writing tree building file. 
	while (treeCounter < 510) {
		out.put((unsigned char)arr_i[treeCounter]);				// Write Tree-building info to end of output file. 
		treeCounter++;
	}
	out.close();												// Close the output file.
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


	char symbol;
	for (int i = 0; i < 256; i++) {
		arr[i] = new node;										// creating 256 nodes, i.e. arr[0]...arr[255] are a new node
		arr[i]->weight = 0;										// initializing the weight(count) of each new node to 0.
		arr[i]->symbol = i;										// intializing the symbol to represent 1 ASCII symbol where i represents the ascii value of the character in decimal. 
		arr[i]->left = NULL;									// each node's left and right child is initialized to NULL since they arent connected to anything yet. 
		arr[i]->right = NULL;
	}

	in.seekg(-510, ios::end);									// Only reading the last 510 bytes in the file.
	unsigned char b;

	for (int i = 0; i < 510; i++) {
		b = in.get();
		decodeArray[i] = (unsigned int)b;						// Getting the sequences for tree building. 
	}

	
	in.close();													// Close the input file. 

//Build the Huffman Tree:

	int iterations = 0;
	int counter = 0;

	while (iterations < 255) {

		node* decodeNode = new node;
		decodeNode->left = arr[decodeArray[counter]];			// left child is the min1 index.
		decodeNode->right = arr[decodeArray[counter + 1]];		// right child is the min2 index.
		arr[decodeArray[counter]] = decodeNode;					// moving the nodes into the min1 node.
		arr[decodeArray[counter + 1]] = NULL;					// setting the min2 index to null. 
		counter += 2;
		iterations++;
	}

	root = arr[0];

	ifstream inin;
	inin.open(inputFile, ios::binary);							// Re-open at the begining of the input file. 
	if (!inin.good()) {
		printf("File not found\n");
		exit(1);
	}
	inin.seekg(0, ios::end);
	int length = inin.tellg();
	length = length - 511;

	inin.seekg(0, ios::beg); 

	ofstream out1;
	out1.open(outputFile, ios::binary);
	if (!out1.good()) {
		printf("File not found\n");
		exit(1);
	}
	unsigned char bit;
	node* p = root;

	while (length > 0) {												

		bit = inin.get();												// Get the next symbol in the encoded file. 

	// If buffer[0] = 1, go right, else go left.
	// (bit & 0x80) ? p->right : p->left;

		if (bit & 0x80) {
			p = p->right;
			if (p->right == NULL && p->left == NULL) { out1.put(p->symbol); p = root; }
		}
		else {
			p = p->left;
			if (p->right == NULL && p->left == NULL) { out1.put(p->symbol); p = root; }
		}
		// If buffer[1] = 1 go right, else go left. 
		// (bit & 0x40) ? p->right : p->left;


		if (bit & 0x40) {
			p = p->right;
			if (p->right == NULL && p->left == NULL) { out1.put(p->symbol); p = root; }
		}
		else {
			p = p->left;
			if (p->right == NULL && p->left == NULL) { out1.put(p->symbol); p = root; }
		}

		// If buffer[2] = 1 go right, else go left. 
		// (bit & 0x20) ? p->right : p->left;


		if (bit & 0x20) {
			p = p->right;
			if (p->right == NULL && p->left == NULL) { out1.put(p->symbol); p = root; }
		}
		else {
			p = p->left;
			if (p->right == NULL && p->left == NULL) { out1.put(p->symbol); p = root; }
		}

		// If buffer[3] = 1 go right, else go left.
		// (bit & 0x10) ? p->right : p->left;


		if (bit & 0x10) {
			p = p->right;
			if (p->right == NULL && p->left == NULL) { out1.put(p->symbol); p = root; }
		}
		else {
			p = p->left;
			if (p->right == NULL && p->left == NULL) { out1.put(p->symbol); p = root; }
		}

		// If buffer[4] = 1 go right, else go left.
		// (bit & 0x08) ? p->right : p->left;

		if (bit & 0x08) {
			p = p->right;
			if (p->right == NULL && p->left == NULL) { out1.put(p->symbol); p = root; }
		}
		else {
			p = p->left;
			if (p->right == NULL && p->left == NULL) { out1.put(p->symbol); p = root; }
		}

		// If buffer[5] = 1 go right, else go left. 
		// (bit & 0x04) ? p->right : p->left;

		if (bit & 0x04) {
			p = p->right;
			if (p->right == NULL && p->left == NULL) { out1.put(p->symbol); p = root; }

		}

		else {
			p = p->left;
			if (p->right == NULL && p->left == NULL) { out1.put(p->symbol); p = root; }
		}

		// If buffer[6] = 1 go right, else go left.
		// (bit & 0x02) ? p->right : p->left;

		if (bit & 0x02) {
			p = p->right;
			if (p->right == NULL && p->left == NULL) { out1.put(p->symbol); p = root; }
		}
		else {
			p = p->left;
			if (p->right == NULL && p->left == NULL) { out1.put(p->symbol); p = root; }
		}

		// If buffer[7] = 1 go right, else go left.
		// (bit & 0x01) ? p->right : p->left;

		if (bit & 0x01) {
			p = p->right;
			if (p->right == NULL && p->left == NULL) { out1.put(p->symbol); p = root; }
		}
		else {
			p = p->left;
			if (p->right == NULL && p->left == NULL) { out1.put(p->symbol); p = root; }
		}

		length--;
	}
	inin.close();
	out1.close();
}

void Huffman::EncodeFileWithTree(string inputFile, string TreeFile, string outputFile) {
	//To encode a file with a specified tree builder file:
	//  1. Create the array of nodes.  
	//	2. Open the Tree building file.
	// 	3. Build the Huffman tree according to tree builder file.
	//  4. Traverse the tree to get the bit strings for encoding the file. 
	//  5. Encode the file, accounting for padding when needed. 
	// 510-bytes are a sequence of index's, if first 2 indices are 9 & 11, combined nodes at 9 and 11. 

	ifstream inTree;
	inTree.open(TreeFile, ios::binary);

	char symbol;
	for (int i = 0; i < 256; i++) {
		arr[i] = new node;										// creating 256 nodes, i.e. arr[0]...arr[255] are a new node
		arr[i]->weight = 0;										// initializing the weight(count) of each new node to 0.
		arr[i]->symbol = i;										// intializing the symbol to represent 1 ASCII symbol where i represents the ascii value of the character in decimal. 
		arr[i]->left = NULL;									// each node's left and right child is initialized to NULL since they arent connected to anything yet. 
		arr[i]->right = NULL;
	}
	 

// Build the Huffman Tree from the specified ".htree" file. 

	inTree.seekg(0, ios::beg);									// Only reading the last 510 bytes in the file.
	unsigned char b;

	for (int i = 0; i < 510; i++) {
		b = inTree.get();
		decodeArray[i] = (unsigned int)b;							// Getting the sequences for tree building. 
	}
	inTree.close();													// Close the Tree File file. 

//Build the Huffman Tree:

	int iterations = 0;
	int counter = 0;

	while (iterations < 255) {

		node* decodeNode = new node;
		decodeNode->left = arr[decodeArray[counter]];			// left child is the min1 index.
		decodeNode->right = arr[decodeArray[counter + 1]];		// right child is the min2 index.
		arr[decodeArray[counter]] = decodeNode;					// moving the nodes into the min1 node.
		arr[decodeArray[counter + 1]] = NULL;					// setting the min2 index to null. 
		counter += 2;
		iterations++;
	}

	node* root = arr[0];
	inorderTraversal(root);										// Traverse Tree to get sequences.

	ifstream in;
	ofstream out; 

	in.open(inputFile, ios::binary);
	if (!in.good()) {
		printf("File not found\n");
		exit(1);
	}

	out.open(outputFile, ios::binary);
	if (!out.good()) {											// Checking that output file can be opened.  
		printf("File not found\n");
		exit(1);
	}

	string buffer = "";
	while (!in.eof()) {

		in.get(symbol);											// Get the next symbol 
		buffer.append(arr_s[symbol]);							// Append the bitstring to the buffer

		while (buffer.length() > 7) {
			unsigned char b = 0;

			if (buffer[0] == '1') b |= (1 << 7);					// 128
			if (buffer[1] == '1') b |= (1 << 6);					// 64
			if (buffer[2] == '1') b |= (1 << 5);					// 32
			if (buffer[3] == '1') b |= (1 << 4);					// 16
			if (buffer[4] == '1') b |= (1 << 3);					// 8
			if (buffer[5] == '1') b |= (1 << 2);					// 4 
			if (buffer[6] == '1') b |= (1 << 1);					// 2
			if (buffer[7] == '1') b |= (1 << 0);					// 1

			out.put(b);											// Write the char to the file. 
			buffer.erase(0, 8);									// Erasing the 8-bits 
		}
	}

	if (buffer.length() > 0) {									// Buffer still have bits in it after end of file is reached. 
		for (int i = 0; i < 256; i++) {							// Loop through entire bitstring array
			if (7 < arr_s[i].length()) {						// if bit string is greater than 7
				buffer.append(arr_s[i]);						// append to end of the buffer.

				unsigned char b = 0;
				if (buffer[0] == '1') b |= (1 << 7);
				if (buffer[1] == '1') b |= (1 << 6);
				if (buffer[2] == '1') b |= (1 << 5);
				if (buffer[3] == '1') b |= (1 << 4);
				if (buffer[4] == '1') b |= (1 << 3);
				if (buffer[5] == '1') b |= (1 << 2);
				if (buffer[6] == '1') b |= (1 << 1);
				if (buffer[7] == '1') b |= (1 << 0);
				out.put(b);
				buffer.erase(0, buffer.length());
				break;
			}
		}
	}

	in.close();													// Close the input file.

	int treeCounter = 0;										// Counter for writing tree building information. 
	while (treeCounter < 510) {
		out.put((unsigned char)arr_i[treeCounter]);				// Write Tree-building info to end of output file. 
		treeCounter++;
	}

	out.close();												// Close the output file.
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
	int iterations2 = 0;

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
			}
		}
		if (smallestIndex > secondSmallestIndex) {	// Checking that the SMALLEST index is the actual SMALLEST index
			int temp;								// Variable to hold one of the index's, so that a swap can be made.
			temp = smallestIndex;
			smallestIndex = secondSmallestIndex;	// Since secondSmallestIndex < smallestIndex, they need to be swapped.
			secondSmallestIndex = temp;
		}

		arr_i[iterations2] = smallestIndex;
		arr_i[iterations2 + 1] = secondSmallestIndex;


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
		iterations2 += 2;
	}

	ofstream out;
	out.open(outputFile, ios::binary);
	if (!out.good()) {
		printf("File not found\n");
		exit(1);
	}

	for (int i = 0; i < 510; i++) {
		out.put((unsigned char)arr_i[i]);			// Writing tree-building info to the file. 
	}

	out.close();									// Closing the output file. 
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