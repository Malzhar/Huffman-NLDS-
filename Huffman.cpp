#include "Huffman.h"
#include <iostream>


void Huffman::DisplayHelp() {
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

void Huffman::EncodeFile(string inputFile, string outputFile) {}

void Huffman::DecodeFile(string inputFile, string outputFile) {}

void Huffman::EncodeFileWithTree(string inputFile, string TreeFile, string outputFile) {}

void Huffman::MakeTreeBuilder(string inputFile, string outputFile) {}


