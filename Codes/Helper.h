#ifndef HELPER_H
#define HELPER_H
#include "Helper.h"
#include <vector>
#include <string>

using namespace std;

void calculateAccuracy(vector<int> workload, vector<int> decoded); // Function to calculate the accuracy of decoded data compared to the original data
int get_file_size(string filename); // Function to get the size of a file in bytes
void compression_ratio(string workload_path, string encoded_path); // Function to calculate the compression ratio of a file
vector<int> read_data(string path); // Function to read data from a file and return as a vector of integers

#endif
