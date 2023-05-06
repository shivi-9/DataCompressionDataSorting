#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include "Helper.h"

using namespace std;

// Function to calculate accuracy of decoded data compared to the original data
void calculateAccuracy(vector<int> workload, vector<int> decoded) {
    int numBytesMatched = 0;
    int numBytesTotal = workload.size();

    // Iterate through the vectors and count the number of matching bytes
    for(long unsigned int i = 0; i < workload.size(); i++) {
        if(workload[i] == decoded[i]){
            numBytesMatched ++;
        }
    }

    // Calculate the accuracy percentage
    double accuracy = (double)numBytesMatched / numBytesTotal * 100;

    // Print the accuracy
    cout << "Accuracy: " << accuracy << "%" << endl;
}

// Function to get the size of a file in bytes
int get_file_size(string filename){
    FILE *p_file = NULL;
    p_file = fopen(filename.c_str(),"r");
    fseek(p_file,0,SEEK_END);
    int size = ftell(p_file);
    fclose(p_file);
    return size;
}

// Function to calculate the compression ratio of a file
void compression_ratio(string workload_path, string encoded_path){
    // Get the sizes of the original and compressed files
    int workload_size = get_file_size(workload_path);
    int encoded_size = get_file_size(encoded_path);

    // Calculate the compression ratio
    float compression_ratio = (1-(encoded_size * 1.0 / workload_size * 1.0)) * 100;

    // Print the compression ratio
    std::cout<<"Compresssion ratio is "<<compression_ratio <<"%"<<endl;
}

// Function to read data from a file and return as a vector of integers
vector<int> read_data(string path){
    vector<int> data;
    ifstream inputFile(path);

    // Read integers from the input file and store in the vector
    int num;
    while (inputFile >> num) {
        data.push_back(num);
    }

    // Close the input file and return the vector
    inputFile.close();
    return data;
}