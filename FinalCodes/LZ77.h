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

vector<unsigned char> convertIntegersToBytes(vector<int> integers);
vector<LZ77Token> encode(const vector<unsigned char>& input);
void write_encoded_data(vector<LZ77Token> compressedData, string filename);
vector<int> convertBytesToIntegers(vector<unsigned char> bytes);
vector<unsigned char> decode(vector<LZ77Token> input);
void lz77(string workload_path, string encoded_path);

#endif
