#include <iostream>
#include <vector>
#include <fstream>
#include <chrono>

using namespace std;

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

struct LZ77Token {
    int offset;
    int length;
    unsigned char nextByte;
};

vector<unsigned char> convertIntegersToBytes(const vector<int>& integers) {
    vector<unsigned char> bytes;
    for (int i = 0; i < integers.size(); i++) {
        int n = integers[i];
        bytes.push_back((n >> 24) & 0xFF);
        bytes.push_back((n >> 16) & 0xFF);
        bytes.push_back((n >> 8) & 0xFF);
        bytes.push_back(n & 0xFF);
    }
    return bytes;
}

vector<LZ77Token> compressLZ77(const vector<unsigned char>& input) {
    vector<LZ77Token> output;
    int inputLength = input.size();
    int pos = 0;
    while (pos < inputLength) {
        int maxMatchOffset = -1;
        int maxMatchLength = -1;
        for (int i = 1; i <= pos; i++) {
            int matchLength = 0;
            while (pos + matchLength < inputLength && input[pos + matchLength] == input[pos - i + matchLength]) {
                matchLength++;
            }
            if (matchLength > maxMatchLength) {
                maxMatchLength = matchLength;
                maxMatchOffset = i;
            }
        }
        if (maxMatchLength > 0) {
            LZ77Token token;
            token.offset = maxMatchOffset;
            token.length = maxMatchLength;
            token.nextByte = input[pos + maxMatchLength];
            output.push_back(token);
            pos += maxMatchLength + 1;
        } else {
            LZ77Token token;
            token.offset = 0;
            token.length = 0;
            token.nextByte = input[pos];
            output.push_back(token);
            pos++;
        }
    }
    return output;
}

void writeCompressedDataToFile(const vector<LZ77Token>& compressedData, const string& filename) {
    ofstream outFile(filename);
    if (!outFile.is_open()) {
        cerr << "Failed to open file " << filename << endl;
        return;
    }
    for (int i = 0; i < compressedData.size(); i++) {
        outFile << compressedData[i].offset << "," << compressedData[i].length << "," << (int)compressedData[i].nextByte << endl;
    }
    outFile.close();
}

int main() {
    // Read the workload file 
    vector<int> data = read_data("./Workload/Workload400KB/1_100.txt");

    auto start = std::chrono::high_resolution_clock::now();
    vector<unsigned char> bytes = convertIntegersToBytes(data);
    vector<LZ77Token> output = compressLZ77(bytes);
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
    writeCompressedDataToFile(output, "./LZ77/EncodedData/400KB/1_100.txt");
    // Print duration
    std::cout << "Encoding took " << duration.count() << " nanoseconds." << std::endl;
    return 0;
}