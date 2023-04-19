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
    ifstream infile("./encoded_data_delta.txt", ios::binary);
    std::vector<int> data;
    
    int element;
    while (infile >> element)
    {
        data.push_back(element);
    }
    std::vector<int>encoded_data = delta_decoding(data);

    std::ofstream output_file("./decoded_data_delta.txt");

    std::ostream_iterator<int> output_iterator(output_file, "\n");
    std::copy(std::begin(encoded_data), std::end(encoded_data), output_iterator);
    output_file.close();
    return 0;
}
