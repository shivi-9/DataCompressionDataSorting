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
#include <sstream>
using namespace std;


std::vector<int> runLengthdecode_freq(std::vector<int> input) {
    
    std::vector<int> output;

    for (int i = 0; i < input.size(); i=i+2) {
        int size = input[i+1]; 
        int value = input[i];
        for (int j = 0; j < size; j++) {
            output.push_back(value) ;
        }
    }
    return output;
}

int main(){
    ifstream infile("./RunLengthEncoding/EncodedData/40KB/100_100.txt", ios::binary);
    std::vector<string> data;
    std::vector<int> data_int;
    string element;
    while (infile >> element)
    {
        data.push_back(element);
    }
    for(int i=0; i<data.size(); i++){

        std::stringstream ss(data[i]);
        string str; 

    // Use while loop to check the getline() function condition.  
        while (getline(ss, str, ',')) 
            // `str` is used to store the token string while ' ' whitespace is used as the delimiter.
            data_int.push_back(stoi(str));
        if(data_int.size()%2!=0)
            data_int.push_back(1);    
        
    }
    
    auto start_pq_f = std::chrono::high_resolution_clock::now();
    std::vector<int>encoded_data = runLengthdecode_freq(data_int);
    auto stop_pq_f = std::chrono::high_resolution_clock::now();
    auto duration_pq_f = std::chrono::duration_cast<std::chrono::nanoseconds>(stop_pq_f - start_pq_f);
    unsigned long long point_query_time_f = duration_pq_f.count();
    std::cout << "Time taken to perform to decode runLengthEncode = " << point_query_time_f << " nanoseconds" << endl;

    std::ofstream output_file("./RunLengthEncoding/DecodedData/40KB/100_100.txt");

    std::ostream_iterator<int> output_iterator(output_file, "\n");
    std::copy(std::begin(encoded_data), std::end(encoded_data), output_iterator);
    output_file.close();
    return 0;
}
