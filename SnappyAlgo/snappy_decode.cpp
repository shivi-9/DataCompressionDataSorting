#include <iostream>
#include <fstream>
#include <chrono>
#include <snappy.h>

int main() {
    // Read input from file
    std::ifstream input("./SnappyAlgo/encoded.txt", std::ios::binary);
    std::string encoded((std::istreambuf_iterator<char>(input)),
                        std::istreambuf_iterator<char>());
    input.close();

    // Decode data
    std::string decoded;
    auto start = std::chrono::high_resolution_clock::now();
    snappy::Uncompress(encoded.data(), encoded.size(), &decoded);
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

    // Save decoded data to file
    std::ofstream output("./SnappyAlgo/decoded.txt", std::ios::binary);
    output.write(decoded.data(), decoded.size());
    output.close();

    // Print duration
    std::cout << "Decoding took " << duration.count() << " microseconds." << std::endl;

    return 0;
}