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

using namespace std;


std::vector<int> delta_encoding(std::vector<int> arr){
    int temp1 = arr[0];
    int n = arr.size();
    for(int i=1;i<n;i++){
       int temp2 = arr[i]; 
       arr[i] -= temp1;
       temp1 = temp2;
    }
    return arr;
}

int main(){
    ifstream infile("./Workload/Workload4MB/100_100.txt", ios::binary);
    std::vector<int> data;
    
    int element;
    while (infile >> element)
    {
        data.push_back(element);
    }
    
    auto start_pq_f = std::chrono::high_resolution_clock::now();
    std::vector<int>encoded_data = delta_encoding(data);
    auto stop_pq_f = std::chrono::high_resolution_clock::now();
    auto duration_pq_f = std::chrono::duration_cast<std::chrono::nanoseconds>(stop_pq_f - start_pq_f);
    unsigned long long point_query_time_f = duration_pq_f.count();
    std::cout << "Time taken to perform Delta Encoding = " << point_query_time_f << " nanoseconds" << endl;


    std::ofstream output_file("./Delta_Encoding/EncodedData/4MB/100_100.txt");

    // declare the output iterator before creating the ofstream object
    std::ostream_iterator<int> output_iterator(output_file, "\n");

    // pass the output iterator to the std::copy function
    std::copy(std::begin(encoded_data), std::end(encoded_data), output_iterator);

    output_file.close();
    return 0;
}