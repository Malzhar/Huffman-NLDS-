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

 

    // MODE 2: 
    // Encode temp and place the output into argv2. Read temp, build a Huffman tree from temp and place it into argv2. argv2's last 510 bytes will be the
    // tree-building information and the remainder of the file will be Huffman-encoded bit stream created from temp. 
    // 
    // Case 1:
    // If argc == 3, then the output file has not been specified.
    //  a.) If temp has no extension, then we append .huf to the end of temp. 
    //  b.) If temp has an extension, then we need to remove the extension and append .huf to the end of temp. 
    // 
    // Case 2:
    // If argc == 4, then the output file has been specified.
    //  a.) Use the name of argv2 as specified, even if the user didn't specify an extension. 
    // 
    // ***temp & argv2 MUST NOT REFER TO THE SAME FILE***
    //  
    // MODE 3: 
    // Decode Huffman-encoded temp into argv2. temp will contain a 510-byte tree-builder block, followed by the Huffman-encoded bit stream for some 
    // original input file. Read the tree-builder block, construct the tree and use it to decode temp, placing result into argv2. 
    // 
    // argv[3] is non-optional for this mode. An output file must be specified. 
    // ***argv2 SHOULD BE BIT-IDENTICAL TO THE ORIGINAL INPUT FILE***
    // 
    // MODE 4: Create A Tree-Building File
    // 
    // Case 1:
    // If argc == 3, then the output file has not been specified.
    //  a.) If temp has no extension, then we append .htree.
    //  b.) If temp has an extension and argv2 has no been specified, then append remove temp extension and appened .htree to the end of temp to make argv2's name. 
    // 
    // Case 2:
    // If argc == 4, then argv2 has been specified. Use the name of the argv2 as given.   
    //
    // MODE 5: Encoding with a specified tree-builder.
    // 
    // argv[0], argv[1], argv[2](temp) -- input file, argv[3](argv2) -- tree file, all required
    // argv[4](argv4) -- output file.
    //  -argv4 is optional and will default to the same name as temp except with a .huff appended to the end of it. 
    // 
    //

    else if (argc == 3) {
        string argv1(argv[1]);
        string argv2(argv[2]);
        // Mode 2: Case 1.
        // Output file has not been specified, need to check if argv2 has an extension:
        //  a.) if no extension, append .huf to end of temp and that becomes argv2
        //  b.) if temp has extension, need to remove the extension and append .huf to the end of temp 
        //          int extension = argv2.find_last_of("."); 
        //

        // check if -i: is a substring(aka a prefix) of argv2, if it is a prefix to argv2 then we can remove the prefix and pass the file to the 
        // the function that we need to. 
        if (argv1 == "-me" && argv2.substr(0, 3) == "-i:") { 
            argv2.erase(0, 3);                                  // Erasing the prefix "-i:"
            myHuff->EncodeFile(argv2, argv2);
            // Check to see if the argv2 has an extension. If there is an extension, we are going to replace the current
            // extension and append a .huf to the end of it. This new text.huf will be the outputFile that the encoded data is stored in.
            // If there is no extension, we simply append .huf to the file
           // int fExtension = argv2.find_last_of(".");   
            //if (fExtension == string::npos) {
            //    argv2.append(".huf"); 
            //} 
            // Making sure that the given file has an extension. 
            //else if (fExtension != string::npos) { 
            //   int i = argv2.rfind(".", argv2.length());        // Find the location of the start of the extension that we want to replace. 
            //    if (i != string::npos) {                        // Variable i just hold the location of the found start of extension
            //        argv2.replace(i, argv2.length(), ".huff");  // Replace the current extension of the file, with the one that we want. 
            //        cout << argv2 << endl;
            //        } 

           // }
            //myHuff->EncodeFile(argv2, argv2);                   //argv2 is going to be the output file since no output file has been specified. 
        }
        // MODE 4: Case 1:
        // If argc == 3, then the output file has not been specified.
        //  a.) If argv2 has no extension, then we append .htree.
        //  b.) If argv2 has an extension and output file has not been specified, then append remove temp extension and appened .htree to the end of temp to make argv2's name.
        else if (argv1 == "-mt" && argv2.substr(0,3) == "-i:") {
            argv2.erase(0, 3);  // Erasing the prefix of the file "-i:"

            int fExtension = argv2.find_last_of(".");
            if (fExtension == string::npos) {
                argv2.append(".htree");
                cout << argv2 << endl;
            }
            else if (fExtension != string::npos) {
                int i = argv2.rfind(".", argv2.length());
                if (i != string::npos) {
                    argv2.replace(i, argv2.length(), ".htree");
                    cout << argv2 << endl;
                }
            }
            myHuff->MakeTreeBuilder(argv2, argv2);          //argv2 is going to be the output file since no output file has been specified. 
            exit(1);
        }

    }

    else if (argc == 4) { 
        string argv1(argv[1]);
        string argv2(argv[2]);
        string argv3(argv[3]);

        // MODE 2: Case 2
        // If argc == 4, then the output file has been specified.
        //  a.) Use the name of argv2 as specified, even if the user didn't specify an extension.
        if (argv1 == "-me" && argv2.substr(0, 3) == "-i:" && argv3.substr(0, 3) == "-o:") {
            argv2.erase(0, 3);
            argv3.erase(0, 3); 
            myHuff->EncodeFile(argv2, argv3);       //Output file has been specified, therefore the encoded argv2 will be outputted into argv3
            exit(1);
        }

        // MODE 3: 
        if (argv1 == "-md" && argv2.substr(0, 3) == "-i:" && argv3.substr(0, 3) == "-o:") {
            argv2.erase(0, 3);
            argv3.erase(0, 3); 
            myHuff->DecodeFile(argv2, argv3); 
            exit(1);
        }

        // MODE 4: Case 2
        // If argc == 4, then argv3, aka the outputFile, has been specified. Use the name argv3 as given.
        else if (argv1 == "-mt" && argv2.substr(0, 3) == "-i:" && argv3.substr(0, 3) == "-o:") {
            argv2.erase(0, 3);
            argv3.erase(0, 3); 

            int fExtension = argv2.find_last_of(".");
            if (fExtension == string::npos) {
                argv2.append(".htree"); 
                cout << argv2 << endl; 
            }
            myHuff->MakeTreeBuilder(argv2, argv3);           
            exit(1);
        }


        // MODE 5: No output file specified. 
        if (argv1 == "-met" && argv2.substr(0, 3) == "-i:" && argv3.substr(0, 3) == "-t:") {
            argv2.erase(0, 3);
            argv3.erase(0, 3); 
            myHuff->EncodeFileWithTree(argv2, argv3, argv2);   // argv2 is the inputFile, argv3 is the tree building file, and argv2 will be the outputFile 
            exit(1);
        }
    }

    // Mode 5: 
    else if (argc == 5) {
        string argv1(argv[1]);
        string argv2(argv[2]);
        string argv3(argv[3]);
        string argv4(argv[4]);

        // MODE 5: The output file has been specified.
        //  1.) argv2 = the inputFile that will be encoded using the 510-byte tree-builder info from argv3. 
        //  2.) argv3 = the 510-byte tree builder
        //  3.) argv4 = last 510-bytes will be the tree-builder info from argv3. 
        // 
        //  a.) argv4 will default to the same name as argv2, aka inputFile, except it will be appended with ".huf" 
        //      -If argv2 has an extension, replace it with ".huf" and make that the name of argv4.  
        //      -If atgv2 has no extension, appended ".huf" to the end of the file and make that the name of argv4
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