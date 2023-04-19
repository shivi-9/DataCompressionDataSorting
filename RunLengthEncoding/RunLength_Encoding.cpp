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


std::vector<int> runLengthEncode_freq(std::vector<int> input) {
    int count = 1;
    int currentValue = input[0];
    std::vector<int> output;

    for (int i = 1; i < input.size(); i++) {
        if (input[i] == currentValue) {
            count++;
        } else {
            output.push_back(count);
            output.push_back(currentValue);
            count = 1;
            currentValue = input[i];
        }
    }

    // Add the last integer sequence
    output.push_back(count);
    output.push_back(currentValue);

    return output;
}

int main(){
    ifstream infile("./workload.txt", ios::binary);
    std::vector<int> data;
    
    int element;
    while (infile >> element)
    {
        data.push_back(element);
    }
    std::vector<int>encoded_data = runLengthEncode_freq(data);

    std::ofstream output_file("./encoded_data.txt");

    std::ostream_iterator<int> output_iterator(output_file, "\n");
    std::copy(std::begin(encoded_data), std::end(encoded_data), output_iterator);
    output_file.close();
    return 0;
}