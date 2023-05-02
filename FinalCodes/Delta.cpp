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