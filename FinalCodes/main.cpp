#include "Delta.h"
#include "Huffman.h"
#include "LZ77.h"
#include "RLE.h"
// #include "Snappy.h"
#include <iostream>

int main(int argc, char *argv[]){
    if(argv[2] == "1"){
        delta(argv[0], argv[1]);
    }
    else if(argv[2] == "2"){
        huffman(argv[0], argv[1]);
    }
    else if(argv[2] == "3"){
        lz77(argv[0], argv[1]);
    }
    else if(argv[2] == "4"){
        rle(argv[0], argv[1]);
    }
    // else if(argv[2] == "5"){
    //     snappy(argv[0], argv[1]);
    // }
    else {
        cout << "Invalid Input" << endl;
    }
    return 0;
}