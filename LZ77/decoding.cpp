#include <iostream>
#include <vector>
#include <fstream>
#include <chrono>

using namespace std;

struct LZ77Token {
    int offset;
    int length;
    unsigned char nextByte;
};

vector<int> convertBytesToIntegers(const vector<unsigned char>& bytes) {
    vector<int> integers;
    for (int i = 0; i < bytes.size(); i += 4) {
        int n = (bytes[i] << 24) | (bytes[i+1] << 16) | (bytes[i+2] << 8) | bytes[i+3];
        integers.push_back(n);
    }
    return integers;
}

vector<unsigned char> decompressLZ77(const vector<LZ77Token>& input) {
    vector<unsigned char> output;
    for (int i = 0; i < input.size(); i++) {
        if (input[i].length > 0) {
            int start = output.size() - input[i].offset;
            int end = start + input[i].length;
            for (int j = start; j < end; j++) {
                output.push_back(output[j]);
            }
        }
        output.push_back(input[i].nextByte);
    }
    return output;
}

vector<LZ77Token> readCompressedDataFromFile(const string& filename) {
    vector<LZ77Token> compressedData;
    ifstream inFile(filename);
    if (!inFile.is_open()) {
        cerr << "Failed to open file " << filename << endl;
        return compressedData;
    }
    string line;
    while (getline(inFile, line)) {
        int offset, length, nextByte;
        if (sscanf(line.c_str(), "%d,%d,%d", &offset, &length, &nextByte) == 3) {
            LZ77Token token;
            token.offset = offset;
            token.length = length;
            token.nextByte = (unsigned char)nextByte;
            compressedData.push_back(token);
        } else {
            cerr << "Invalid input line: " << line << endl;
        }
    }
    inFile.close();
    return compressedData;
}

void writeDecompressedDataToFile(const string& filename, const vector<int>& data) {
    ofstream outFile(filename);
    if (!outFile.is_open()) {
        cerr << "Failed to open file " << filename << endl;
        return;
    }
    for (int i = 0; i < data.size(); i++) {
        outFile << data[i] << "\n";
    }
    outFile.close();
}

int main() {
    vector<LZ77Token> compressedData = readCompressedDataFromFile("./LZ77/EncodedData/40KB/50_1.txt");
    auto start = std::chrono::high_resolution_clock::now();
    vector<unsigned char> bytes = decompressLZ77(compressedData);
    vector<int> integers = convertBytesToIntegers(bytes);
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
    writeDecompressedDataToFile("./LZ77/DecodedData/40KB/50_1.txt", integers);
    // Print duration
    std::cout << "Encoding took " << duration.count() << " nanoseconds." << std::endl;
    return 0;
}
