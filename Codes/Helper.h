#ifndef HELPER_H
#define HELPER_H
#include "Helper.h"
#include <vector>
#include <string>

using namespace std;

void calculateAccuracy(vector<int> workload, vector<int> decoded);
int get_file_size(string filename);
void compression_ratio(string workload_path, string encoded_path);
vector<int> read_data(string path);

#endif
