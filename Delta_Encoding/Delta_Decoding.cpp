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


std::vector<int> delta_decoding(std::vector<int> arr){
    
    int temp1 = arr[0];
    int n = arr.size();
    for(int i=1;i<n;i++){ 
       arr[i] += temp1;
       temp1 = arr[i];
    }
   return arr;
}

int main(){
    ifstream infile("./Delta_Encoding/EncodedData/4MB/100_100.txt", ios::binary);
    std::vector<int> data;
    
    int element;
    while (infile >> element)
    {
        data.push_back(element);
    }
    infile.close();

    // Record start time
    auto start_time = std::chrono::high_resolution_clock::now();
    
    std::vector<int>encoded_data = delta_decoding(data);

    // Record end time
    auto end_time = std::chrono::high_resolution_clock::now();
    
    // Calculate elapsed time in microseconds
    auto elapsed_time = std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time).count();
    std::cout << "Decoding time: " << elapsed_time << " nanoseconds" << std::endl;

    std::ofstream output_file("./Delta_Encoding/DecodedData/4MB/100_100.txt", ios::binary);


    std::ostream_iterator<int> output_iterator(output_file, "\n");
    std::copy(std::begin(encoded_data), std::end(encoded_data), output_iterator);
    output_file.close();

    
    return 0;
}
