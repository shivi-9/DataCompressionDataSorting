#ifndef DELTA_H
#define DELTA_H
#include "Delta.h"
#include <vector>
#include <string>

using namespace std;

vector<int> delta_encoding(vector<int> arr); // performs delta encoding on the input vector 'arr'
vector<int> delta_decoding(vector<int> arr); // performs delta decoding on the input vector 'arr'
void delta(string workload_path, string encoded_path); // performs delta encoding and decoding on the input file 'workload_path' and saves the encoded data to the output file 'encoded_path'

#endif
