#ifndef LZ77_H
#define LZ77_H
#include "LZ77.h"
#include <vector>

using namespace std;

struct LZ77Token {
    int offset; 
    int length; 
    unsigned char nextByte;
};

vector<unsigned char> convertIntegersToBytes(vector<int> integers); // Function to convert a vector of integers to a vector of bytes
vector<LZ77Token> encode(const vector<unsigned char>& input); // Function to encode a vector of bytes using LZ77 algorithm
void write_encoded_data(vector<LZ77Token> compressedData, string filename); // Function to write encoded data to a file
vector<int> convertBytesToIntegers(vector<unsigned char> bytes); // Function to convert a vector of bytes to a vector of integers
vector<unsigned char> decode(vector<LZ77Token> input); // Function to decode an LZ77-encoded vector of tokens to its original byte sequence
void lz77(string workload_path, string encoded_path); // Function to perform LZ77 compression and write the compressed data to a file

#endif