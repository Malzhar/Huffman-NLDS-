#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include "Huffman.h"


using namespace std;

int main(int argc, char* argv[]) {

    Huffman* myHuff = new Huffman(); 
    ifstream in; 

//Mode 1 -- Show Help: Displays the proper usage options to the user and exits. 

    string temp0(argv[1]); 

    if (temp0 == "-h" || temp0 == "-?" || temp0 == "-help") { 
        myHuff->displayHelp(); 
        exit(1); 

    }
    string temp1(argv[2]);
//Mode 2 -- Encode Directly From Input File and placing it into an output file or a specified output file
   
    //if there is only 3 arguments to be passed then the file2 has not been specified. We need to take file1, remove its extension and append .huf to the end of it.
    //if file2 is omitted and file1 doesnt have an extension, then we append .huf to the end of file1
    //if file2 is specified use its name as-supplied even if there is no extension.
    //file1 & file2 cannot refer to the same file. 

    //file2 has not been specified, check if file1 has an extension or not,
    //if file1 has an extension we need to take the name of file1, remove its extension and append .huf to the end of the file.
    //if file1 doesn't have an extension need to append .huf to the end of it. 
    
    if (argc == 3) {


    }
    else if (argc == 4) {

    }

    string temp2(argv[3]);
    string temp3(argv[4]);

    return 0;
}