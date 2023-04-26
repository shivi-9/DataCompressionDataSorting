#include <iostream>
#include <vector>
#include <fstream>
#include <chrono>
#include <unordered_map>
#include <string>

using namespace std;

const int WINDOW_SIZE = 2048;
const int MAX_MATCH_LENGTH = 18;

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
    unordered_map<string, int> patternTable; // Hash table to store previously seen patterns
    while (pos < inputLength) {
        int maxMatchOffset = 0;
        int maxMatchLength = 0;
        // Search for the longest match within the sliding window
        for (int i = 1; i <= min(pos, WINDOW_SIZE); i++) {
            int matchLength = 0;
            // Compute the length of the match
            while (pos + matchLength < inputLength && matchLength < MAX_MATCH_LENGTH && input[pos + matchLength] == input[pos - i + matchLength]) {
                matchLength++;
            }
            // Update the maximum match if a longer match is found
            if (matchLength > maxMatchLength) {
                maxMatchLength = matchLength;
                maxMatchOffset = i;
            }
        }
        // If a match is found, add a token to the output and move the position forward
        if (maxMatchLength > 0) {
            LZ77Token token;
            token.offset = maxMatchOffset;
            token.length = maxMatchLength;
            token.nextByte = input[pos + maxMatchLength];
            output.push_back(token);
            pos += maxMatchLength + 1;
            // Add the pattern to the pattern table
            string pattern(input.begin() + pos - maxMatchLength - maxMatchOffset, input.begin() + pos - maxMatchOffset);
            patternTable[pattern] = pos - maxMatchLength - maxMatchOffset;
        } else {
            // If no match is found, add a literal token to the output and move the position forward
            LZ77Token token;
            token.offset = 0;
            token.length = 0;
            token.nextByte = input[pos];
            output.push_back(token);
            pos++;
        }
        // If the pattern table is full, clear it to prevent memory issues
        if (patternTable.size() > 1 << 20) {
            patternTable.clear();
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
        string temp_offset = to_string(compressedData[i].offset);
        string temp_len = to_string(compressedData[i].length);
        string temp_byte = to_string((int)compressedData[i].nextByte);
        string temp = temp_offset + ", " + temp_len + "," + temp_byte + "\n";
        outFile << compressedData[i].offset << "," << compressedData[i].length << "," << (int)compressedData[i].nextByte << endl;
    }
    outFile.close();
}

int main() {
    // Read the workload file 
    vector<int> data = read_data("./Workload/Workload40KB/50_1.txt");

    auto start = std::chrono::high_resolution_clock::now();
    vector<unsigned char> bytes = convertIntegersToBytes(data);
    vector<LZ77Token> output = compressLZ77(bytes);
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
    writeCompressedDataToFile(output, "./LZ77/EncodedData/40KB/50_1.txt");
    // Print duration
    std::cout << "Encoding took " << duration.count() << " nanoseconds." << std::endl;
    return 0;
}