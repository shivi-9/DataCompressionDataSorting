#include <iostream>
#include <fstream>
#include <chrono>
#include <snappy.h>

int main() {
    // Read input from file
    std::ifstream input("./Workload/workload.txt", std::ios::binary);
    std::string data((std::istreambuf_iterator<char>(input)),
                     std::istreambuf_iterator<char>());
    input.close();

    // Encode data
    std::string encoded;
    auto start = std::chrono::high_resolution_clock::now();
    snappy::Compress(data.data(), data.size(), &encoded);
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);

    // Save encoded data to file
    std::ofstream output("./SnappyAlgo/encoded.txt", std::ios::binary);
    output.write(encoded.data(), encoded.size());
    output.close();

    // Print duration
    std::cout << "Encoding took " << duration.count() << " nanoseconds." << std::endl;

    return 0; 
}