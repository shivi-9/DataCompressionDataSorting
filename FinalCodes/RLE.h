#ifndef RLE_H
#define RLE_H
#include "RLE.h"
#include <vector>
#include <string>

using namespace std;

vector<int> runLengthEncode_freq(vector<int> input);
vector<int> runLengthdecode_freq(vector<int> input);
void rle(string workload_path, string encoded_path);

#endif