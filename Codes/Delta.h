#ifndef DELTA_H
#define DELTA_H
#include "Delta.h"
#include <vector>
#include <string>

using namespace std;

vector<int> delta_encoding(vector<int> arr);
vector<int> delta_decoding(vector<int> arr);
void delta(string workload_path, string encoded_path);

#endif
