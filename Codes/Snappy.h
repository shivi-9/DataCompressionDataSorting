#ifndef SNAPPY_H
#define SNAPPY_H
#include "Snappy.h"
#include <vector>
#include <string>

using namespace std;

string int_vector_to_string(vector<int> vec);
void snappy(string workload_path, string encoded_path);

#endif