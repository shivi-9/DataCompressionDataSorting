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

int get_file_size(std::string filename) // path to file
{
    FILE *p_file = NULL;
    p_file = fopen(filename.c_str(),"rb");
    fseek(p_file,0,SEEK_END);
    int size = ftell(p_file);
    fclose(p_file);
    return size;
}

int main(){

    int file1 = get_file_size("./RunLengthEncoding/EncodedData/4MB/25_25.txt");
    // cout << file1 << endl;
    int file2 = get_file_size("./Workload/Workload4MB/25_25.txt");
    // cout << file2 << endl;
    float compression_ratio = (1-(file1 * 1.0 / file2 * 1.0)) * 100;
    std::cout<<"Compresssion ratio is "<<compression_ratio <<"%"<<endl;

}