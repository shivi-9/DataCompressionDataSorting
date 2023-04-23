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
            output.push_back(currentValue);
            output.push_back(count);
            count = 1;
            currentValue = input[i];
        }
    }

    // Add the last integer sequence
    output.push_back(currentValue);
    output.push_back(count);

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

    auto start_pq_f = std::chrono::high_resolution_clock::now();
     std::vector<int>encoded_data = runLengthEncode_freq(data);
    auto stop_pq_f = std::chrono::high_resolution_clock::now();
    auto duration_pq_f = std::chrono::duration_cast<std::chrono::nanoseconds>(stop_pq_f - start_pq_f);
    unsigned long long point_query_time_f = duration_pq_f.count();
    std::cout << "Time taken to perform runLengthEncode = " << point_query_time_f << " nanoseconds" << endl;

   

    std::ofstream output_file("./encoded_data.txt");

    std::ostream_iterator<int> output_iterator(output_file, "\n");
    
    for(int i=0; i<encoded_data.size(); i=i+2){
        if(encoded_data[i+1]==1)
            output_file<<encoded_data[i]<<"\n";
        else{
            output_file<<encoded_data[i]<<","<<encoded_data[i+1]<<"\n";
        }    
    }

    output_file.close();
    return 0;
}