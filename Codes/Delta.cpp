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
#include "Delta.h"

using namespace std;

/* This function takes in a vector of integers 'arr' and performs delta encoding on it.
   Delta encoding is a lossless data compression technique that stores the difference 
   between successive values in a sequence. The first element of the sequence is stored
   as it is, and the difference between the subsequent elements and their previous elements 
   is stored instead of the actual values. This function uses two temporary variables, 
   'temp1' and 'temp2', to keep track of the previous and current elements in the sequence
   respectively. The loop starts from the second element of the vector and subtracts the 
   previous element from the current element, and then updates 'temp1' and 'temp2'.
   The resulting vector 'arr' is the delta-encoded version of the original input vector */
vector<int> delta_encoding(vector<int> arr){
    int temp1 = arr[0];
    int n = arr.size();
    
    for(int i=1;i<n;i++){
       int temp2 = arr[i]; 
       arr[i] -= temp1;
       temp1 = temp2;
    }
    return arr;
}

/* This function takes in a vector of integers 'arr' and performs delta decoding on it.
   Delta decoding is the reverse process of delta encoding and reconstructs the original 
   sequence from the delta-encoded version. The first element of the sequence is stored 
   as it is, and the subsequent elements are obtained by adding the corresponding delta 
   values to the previous elements. This function uses two temporary variables, 'temp1' 
   and 'temp2', to keep track of the previous and current elements in the sequence respectively.
   The loop starts from the second element of the vector and adds the previous element to 
   the current delta value, and then updates 'temp1' and 'temp2'. The resulting vector 'arr' 
   is the delta-decoded version of the original input vector. */
vector<int> delta_decoding(vector<int> arr){
    int temp1 = arr[0];
    int n = arr.size();
    for(int i=1;i<n;i++){ 
       arr[i] += temp1;
       temp1 = arr[i];
    }
   return arr;
}

void delta(string workload_path, string encoded_path){
    // reading the workload
    vector<int> workload = read_data(workload_path);
    
    // Encoding
    auto start_pq_f = std::chrono::high_resolution_clock::now();
    vector<int>encoded_data = delta_encoding(workload);
    auto stop_pq_f = std::chrono::high_resolution_clock::now();

    // printing time
    auto duration_pq_f = std::chrono::duration_cast<std::chrono::nanoseconds>(stop_pq_f - start_pq_f);
    unsigned long long point_query_time_f = duration_pq_f.count();
    cout << "Time taken to perform Delta Encoding = " << point_query_time_f << " nanoseconds" << endl;

    // saving encoded data
    ofstream output_file(encoded_path);
    ostream_iterator<int> output_iterator(output_file, "\n");
    copy(begin(encoded_data), end(encoded_data), output_iterator);
    output_file.close();

    // decoding
    vector<int>decoded_data = delta_decoding(encoded_data);
    
    // accuracy
    calculateAccuracy(workload, decoded_data);

    // compression ratio
    compression_ratio(workload_path, encoded_path);
}