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


std::vector<int> runLengthdecode_freq(std::vector<int> input) {
    
    std::vector<int> output;

    for (int i = 0; i < input.size(); i=i+2) {
        int size = input[i]; 
        int value = input[i+1];
        for (int j = 0; j < size; j++) {
            output.push_back(value) ;
        }
    }
    return output;
}

int main(){
    ifstream infile("./RunLengthEncoding/encoded_data_rle_100k.txt", ios::binary);
    std::vector<int> data;
    
    int element;
    while (infile >> element)
    {
        data.push_back(element);
    }

    auto start_time = std::chrono::high_resolution_clock::now(); // start measuring time
    std::vector<int> encoded_data = runLengthdecode_freq(data);
    auto end_time = std::chrono::high_resolution_clock::now(); // stop measuring time

    auto elapsed_time = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time).count(); // calculate elapsed time in microseconds

    std::ofstream output_file("./RunLengthEncoding/decoded_data_rle_100k.txt");
    std::ostream_iterator<int> output_iterator(output_file, "\n");
    std::copy(std::begin(encoded_data), std::end(encoded_data), output_iterator);
    output_file.close();

    std::cout << "Decoding took " << elapsed_time << " microseconds." << std::endl; // print elapsed time in microseconds
    return 0;
}
