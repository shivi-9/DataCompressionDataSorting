#include <fstream>
#include <vector>
#include <iostream>
#include <random>
#include <set>
#include <algorithm>
#include <functional>
#include <chrono>
#include <utility>

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
    ifstream infile("./workload.txt", ios::binary);
    std::vector<int> data;
    
    int element;
    while (infile >> element)
    {
        data.push_back(element);
    }
    
    auto start_pq_f = std::chrono::high_resolution_clock::now();
    std::vector<int>encoded_data = delta_encoding(data);
    auto stop_pq_f = std::chrono::high_resolution_clock::now();
    auto duration_pq_f = std::chrono::duration_cast<std::chrono::microseconds>(stop_pq_f - start_pq_f);
    unsigned long long point_query_time_f = duration_pq_f.count();
    std::cout << "Time taken to perform Delta Encoding = " << point_query_time_f << " microseconds" << endl;


    std::ofstream output_file("./encoded_data_delta.txt");

    std::ostream_iterator<int> output_iterator(output_file, "\n");
    std::copy(std::begin(encoded_data), std::end(encoded_data), output_iterator);
    output_file.close();
    return 0;
}