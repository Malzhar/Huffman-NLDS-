#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include "Huffman.h"


using namespace std;

int main(int argc, char* argv[]) {

    Huffman* myHuff = new Huffman();
     
    // Mode 1 -- Show Help: Displays the proper usage options to the user and exits

    if (argc == 2) {
        string argv1(argv[1]);
        if (argv1 == "-h" || argv1 == "-?" || argv1 == "-help") {
            myHuff->displayHelp(); 
            exit(1);

        }
    }


// For all MODES:
//  1. Need to check if "-i:" is a substring of the input file, if it is then we remove the pre-fix and pass the file to the appropriate function.
//  2. If appropraite for the specified function:
//      a. Check if "-o:" or "-t:" is a substring of the file, if it is then we remove the pre-fix and pass the file to the appropraite function. 
//  3. Need to check if an extension either exists or does not exist: 
//      a. If one does exist then it needs to be removed and the appropriate extension needs to be
//         appended to the end of the file. 
//      b. If one does not exist, then the appropriate extension needs to be appended to the end of the file. 
 
 
   

 
// MODES 2a & 4a: 
//  Output file has not been specified, need to check if argv2 has an extension:
//   a.) If their is no extension, append .huf(2a) or .htree(4a) to the end of the input file and that will become 
//       the output file name.
//   b.) If input file has an extension, remove the extension and append either .hug (2a) or .htree (4a) to the end
//       of the input file and that will be the name of the output file. 

    else if (argc == 3) {
        string argv1(argv[1]);
        string argv2(argv[2]);
        string outputFile; 
// MODE 2a: Output file has not been specified. 

        if (argv1 == "-me" && argv2.substr(0, 3) == "-i:") {    // check if "-i:" is a substring of argv2
            argv2.erase(0, 3);                                  // Erasing the prefix "-i:"
            outputFile = argv2; 
// Check to see if the argv2 (file) has an extension:
//  1. If there is an extension, remove current extension and append ".huf" to the end of it.
//  2. If there is no extension, append ".huf" to the end of it.   
        
            int fExtension = outputFile.find_last_of(".");           // Checking to see if the file has an extension
            if (fExtension == string::npos) {                   // If there is no ".", then there is no extension,
                outputFile.append(".huf");                           // append ".huf" to the end of the file. 
 
            }  
            else if (fExtension != string::npos) { 
               int i = outputFile.rfind(".", outputFile.length());        // Find the location of the start of the extension that we want to replace. 
               if (i != string::npos) {                         // Variable i just hold the location of the found start of extension
                   outputFile.replace(i, outputFile.length(), ".huf");    // Replace the current extension of the file, with the one that we want. 

               }
            }

           myHuff->EncodeFile(argv2, outputFile);                   //argv2 is going to be the output file since no output file has been specified. 
        }
// MODE 4a: Output file has not been specified. 

        else if (argv1 == "-mt" && argv2.substr(0, 3) == "-i:") {
            argv2.erase(0, 3);                                      // Erasing the prefix of the file "-i:"
            outputFile = argv2; 

// Check to see if the argv2 (file) has an extension:
//  1. If there is an extension, remove current extension and append ".htree" to the end of it.
//  2. If there is no extension, append ".htree" to the end of it.

            int fExtension = outputFile.find_last_of(".");

            if (fExtension == string::npos) {
                outputFile.append(".htree");
            }

            else if (fExtension != string::npos) {
                int i = outputFile.rfind(".", outputFile.length());

                if (i != string::npos) {
                    outputFile.replace(i, outputFile.length(), ".htree"); 
                }
            }
            myHuff->MakeTreeBuilder(argv2, outputFile);              //argv2 is going to be the output file since no output file has been specified. 
            exit(1);
        }

    }

// MODES 2b, 3, 4b & 5a:
//  1. The output file has been specified, use the name of the output file specified. 
//  2. 5a is the exception, no output file has been specified there is just a fourth argument, the tree file. 

    else if (argc == 4) {
        string argv1(argv[1]);
        string argv2(argv[2]);
        string argv3(argv[3]);
        string outputFile; 

// MODE 2b: Output file has been specified. 
//  a. Use the name of argv2 as specified, even if the user didn't specify an extension.
//  b. The name of argv3 will be the name of the output file. 

        if (argv1 == "-me" && argv2.substr(0, 3) == "-i:" && argv3.substr(0, 3) == "-o:") {
            argv2.erase(0, 3);
            argv3.erase(0, 3);
            myHuff->EncodeFile(argv2, argv3);                           //Output file has been specified, therefore the encoded argv2 will be outputted into argv3
            exit(1);
        }

// MODE 3: 
        if (argv1 == "-md" && argv2.substr(0, 3) == "-i:" && argv3.substr(0, 3) == "-o:") {
            argv2.erase(0, 3);
            argv3.erase(0, 3);
            myHuff->DecodeFile(argv2, argv3);
            exit(1);
        }

// MODE 4b: Output file has been specified. 
//  a. Use the name of argv2 as specified, even if the user didn't specify an extension. 
//  b. The name of argv3 will be the name of the output file. 

        else if (argv1 == "-mt" && argv2.substr(0, 3) == "-i:" && argv3.substr(0, 3) == "-o:") {
            argv2.erase(0, 3);
            argv3.erase(0, 3);
            myHuff->MakeTreeBuilder(argv2, argv3);
            exit(1);
        }


// MODE 5a: Outputfile has not been specified. 
//  1. argv2 is the inputFile
//  2. argv3 is the tree building file
//  3. argv2 will be the outputFile

        if (argv1 == "-met" && argv2.substr(0, 3) == "-i:" && argv3.substr(0, 3) == "-t:") {
            argv2.erase(0, 3);
            argv3.erase(0, 3);

            outputFile = argv2; 
            int fExtension = outputFile.find_last_of(".");
            if (fExtension == string::npos) {
                outputFile.append(".huf"); 
            }
            myHuff->EncodeFileWithTree(argv2, argv3, outputFile);   
            exit(1);
        }
    }

// Mode 5b: Output file has been specified. 
//  1. argv2 = the inputFile
//  2. argv3 = the 510-byte tree builder
//  3. argv4 = last 510-bytes will be the tree-builder info from argv3
//   a.) argv4 will default to the same name as argv2, aka inputFile, except it will be appended with ".huf"
//      i.  If argv2 has an extension, replace it with ".huf" and make that the name of argv4.
//      ii. If atgv2 has no extension, appended ".huf" to the end of the file and make that the name of argv4

    else if (argc == 5) {
        string argv1(argv[1]);
        string argv2(argv[2]);
        string argv3(argv[3]);
        string argv4(argv[4]);

        if (argv1 == "-met" && argv2.substr(0, 3) == "-i:" && argv3.substr(0, 3) == "-t:" && argv4.substr(0, 3) == "-o:") {
            argv2.erase(0, 3);
            argv3.erase(0, 3);
            argv4.erase(0, 4);

            myHuff->EncodeFileWithTree(argv2, argv3, argv4);
            exit(1);
        }
    }

    return 0;
}
