#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include "Helper.h"

using namespace std;

void calculateAccuracy(vector<int> workload, vector<int> decoded) {
    int numBytesMatched = 0;
    int numBytesTotal = workload.size();
    
    for(int i = 0; i < workload.size(); i++) {
        if(workload[i] == decoded[i]){
            numBytesMatched ++;
        }
    }

    double accuracy = (double)numBytesMatched / numBytesTotal * 100;

    cout << "Accuracy: " << accuracy << "%" << endl;
}

int get_file_size(string filename){
    FILE *p_file = NULL;
    p_file = fopen(filename.c_str(),"rb");
    fseek(p_file,0,SEEK_END);
    int size = ftell(p_file);
    fclose(p_file);
    return size;
}

void compression_ratio(string workload_path, string encoded_path){
    int workload_size = get_file_size(workload_path);
    int encoded_size = get_file_size(encoded_path);
    float compression_ratio = (1-(workload_size * 1.0 / encoded_size * 1.0)) * 100;
    std::cout<<"Compresssion ratio is "<<compression_ratio <<"%"<<endl;
}

vector<int> read_data(string path){
    vector<int> data;
    ifstream inputFile(path);
    int num;
    while (inputFile >> num) {
        data.push_back(num);
    }

    inputFile.close();
    return data;
}