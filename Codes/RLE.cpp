#include <fstream>
#include <vector>
#include <iostream>
#include <random>
#include <set>
#include <algorithm>
#include <functional>
#include <chrono>
#include <utility>
#include <iterator>
#include "Helper.h"
#include "RLE.h"

using namespace std;

vector<int> runLengthEncode_freq(vector<int> input) {
    int count = 1;
    int currentValue = input[0];
    vector<int> output;

    // Loop through the input vector starting from the second element
    for (int i = 1; i < input.size(); i++) {
        // If the current element is the same as the previous element, increment the count
        if (input[i] == currentValue) {
            count++;
        } 
        // Otherwise, add the previous value and its count to the output vector
        // Reset the count to 1 and update the current value to the current element
        else {
            output.push_back(currentValue);
            output.push_back(count);
            count = 1;
            currentValue = input[i];
        }
    }

    // Add the last integer sequence to the output vector
    output.push_back(currentValue);
    output.push_back(count);

    return output;
}

vector<int> runLengthdecode_freq(vector<int> input) {
    vector<int> output;
    // iterate through the input vector
    for (int i = 0; i < input.size(); i=i+2) {
        // get the size of the sequence
        int size = input[i+1];
        // get the value that should be repeated
        int value = input[i];
        // repeat the value size times and add to the output vector
        for (int j = 0; j < size; j++) {
            output.push_back(value) ;
        }
        }
    return output;
}

void rle(string workload_path, string encoded_path){
    // reading the workload
    vector<int> data = read_data(workload_path);
    
    // encoding
    auto start_pq_f = chrono::high_resolution_clock::now();
    vector<int>encoded_data = runLengthEncode_freq(data);
    auto stop_pq_f = chrono::high_resolution_clock::now();

    // printing time
    auto duration_pq_f = chrono::duration_cast<chrono::nanoseconds>(stop_pq_f - start_pq_f);
    unsigned long long point_query_time_f = duration_pq_f.count();
    cout << "Time taken to perform runLengthEncode = " << point_query_time_f << " nanoseconds" << endl;

    // writing encoded data to a file
    ofstream output_file(encoded_path);
    ostream_iterator<int> output_iterator(output_file, "\n");
    for(int i=0; i<encoded_data.size(); i=i+2){
        if(encoded_data[i+1]==1)
            output_file<<encoded_data[i]<<"\n";
        else{
            output_file<<encoded_data[i]<<","<<encoded_data[i+1]<<"\n";
        }    
    }
    output_file.close();
    
    // decoding
    vector<int>decoded_data = runLengthdecode_freq(encoded_data);
    
    // accuracy
    calculateAccuracy(data, decoded_data);

    // compression ratio
    compression_ratio(workload_path, encoded_path);
}