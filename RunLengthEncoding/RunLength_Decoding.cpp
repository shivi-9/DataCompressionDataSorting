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
    ifstream infile("./encoded_data.txt", ios::binary);
    std::vector<int> data;
    
    int element;
    while (infile >> element)
    {
        data.push_back(element);
    }
    std::vector<int>encoded_data = runLengthdecode_freq(data);

    std::ofstream output_file("./decoded_data.txt");

    std::ostream_iterator<int> output_iterator(output_file, "\n");
    std::copy(std::begin(encoded_data), std::end(encoded_data), output_iterator);
    output_file.close();
    return 0;
}
