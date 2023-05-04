#include "Delta.h"
#include "Huffman.h"
#include "LZ77.h"
#include "RLE.h"
// #include "Snappy.h"
#include <iostream>
#include <cstring>

int main(int argc, char *argv[]){
    if(strcmp(argv[3], "1") == 0){
        delta(argv[1], argv[2]);
    }
    else if(strcmp(argv[3], "2") == 0){
        huffman(argv[1], argv[2]);
    }
    else if(strcmp(argv[3], "3") == 0){
        lz77(argv[1], argv[2]);
    }
    else if(strcmp(argv[3], "4") == 0){
        rle(argv[1], argv[2]);
    }
    // else if(strcmp(argv[3], "5") == 0){
    //     snappy(argv[1], argv[2]);
    // }
    else {
        cout << "Invalid Input" << endl;
    }
    return 0;
}