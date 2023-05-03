#include <iostream>
#include <fstream>
#include <chrono>
#include <snappy.h>
#include <sstream>
#include "Helper.h"
#include "Snappy.h"

using namespace std;

string int_vector_to_string(vector<int> vec) {
    ostringstream oss;
    for (auto i : vec) {
        oss << i << " ";
    }
    return oss.str();
}

void snappy(string workload_path, string encoded_path) {
    // Read input from file
    vector<int> workload = read_data(workload_path);
    string data = int_vector_to_string(workload);
    
    // Encode data
    string encoded;
    auto start = chrono::high_resolution_clock::now();
    snappy::Compress(data.data(), data.size(), &encoded);
    auto end = chrono::high_resolution_clock::now();

    // Print duration
    auto duration = chrono::duration_cast<chrono::nanoseconds>(end - start);
    cout << "Encoding took " << duration.count() << " nanoseconds." << endl;

    // Save encoded data to file
    ofstream output(encoded_path);
    output.write(encoded.data(), encoded.size());
    output.close();

    // decoding
    string decoded;
    snappy::Uncompress(encoded.data(), encoded.size(), &decoded);
    
    // accuracy
    calculateAccuracy(data, decoded);

    // compression ratio
    compression_ratio(workload_path, encoded_path);
}