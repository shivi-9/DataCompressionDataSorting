#include <iostream>
#include <fstream>
#include <chrono>
#include <string>
#include <snappy.h>

using namespace std;

int main()
{
    // Open the workload file
    ifstream infile("./Workload/workload.txt", ios::binary | ios::ate);
    if (!infile)
    {
        cerr << "Error: Could not open input file!" << endl;
        return 1;
    }

    // Determine the size of the file
    streamsize size = infile.tellg();
    infile.seekg(0, ios::beg);

    // Allocate a buffer to hold the file contents
    char* buffer = new char[size];

    // Read the file contents into the buffer
    infile.read(buffer, size);

    // Close the input file
    infile.close();

    // Compress the data
    string compressed_data;
    auto start_time = chrono::high_resolution_clock::now();
    snappy::Compress(buffer, size, &compressed_data);
    auto end_time = chrono::high_resolution_clock::now();

    // Save the compressed data to a file
    ofstream outfile("compressed.txt", ios::binary | ios::trunc);
    if (!outfile)
    {
        cerr << "Error: Could not open output file!" << endl;
        return 1;
    }
    outfile.write(compressed_data.c_str(), compressed_data.size());
    outfile.close();

    // Calculate the time taken to compress the data
    auto encode_time = chrono::duration_cast<chrono::milliseconds>(end_time - start_time).count();

    // Print the compression ratio and the time taken to encode the data
    cout << "Compression ratio: " << (double)compressed_data.size() / size << endl;
    cout << "Time taken to encode: " << encode_time << " milliseconds" << endl;

    // Free the buffer
    delete[] buffer;

    return 0;
}
