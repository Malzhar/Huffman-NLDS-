#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>

using namespace std;

int main(int argc, char* argv[]) {  



    ifstream in; //this can be any name that we want.
    in.open(argv[1], ios::binary);
    if (!in.good()) {
        printf("File not found\n");
        exit(1);
    }

    char next;
    int arr[256];
    int total = 0;
    int count = 0;
    for (int i = 0; i < 256; i++) {
        arr[i] = count;
    }

    in.get(next);

    while (!in.eof()) {
        //while we havent reached the end of the file, go to the next char and increment the count of the char.

        arr[(unsigned char)next]++;
        total++;

        in.get(next);
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
    cout << "Total: " + total << endl;

    return 0;
}