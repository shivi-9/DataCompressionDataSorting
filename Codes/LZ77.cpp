#include <iostream>
#include <vector>
#include <fstream>
#include <chrono>
#include <unordered_map>
#include <string>
#include "LZ77.h"
#include "Helper.h"

using namespace std;

const int WINDOW_SIZE = 2048;
const int MAX_MATCH_LENGTH = 18;

vector<unsigned char> convertIntegersToBytes(vector<int> integers) {
    vector<unsigned char> bytes;
    for (int i = 0; i < integers.size(); i++) {
        int n = integers[i];
        // convert 4 bytes integer into 4 unsigned char bytes 
        bytes.push_back((n >> 24) & 0xFF); // extract the first byte of the integer and push it into the bytes vector
        bytes.push_back((n >> 16) & 0xFF); // extract the second byte of the integer and push it into the bytes vector
        bytes.push_back((n >> 8) & 0xFF); // extract the third byte of the integer and push it into the bytes vector
        bytes.push_back(n & 0xFF); // extract the fourth byte of the integer and push it into the bytes vector
    }
    return bytes;
}

vector<LZ77Token> encode_lz77(vector<unsigned char> input) {
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

void write_encoded_data(vector<LZ77Token> compressedData, string filename) {
    ofstream outFile(filename);
    if (!outFile.is_open()) {
        cerr << "Failed to open file " << filename << endl;
        return;
    }
    // Write each token to the file as a comma-separated string
    for (int i = 0; i < compressedData.size(); i++) {
        // Convert integer values to strings
        string temp_offset = to_string(compressedData[i].offset);
        string temp_len = to_string(compressedData[i].length);
        string temp_byte = to_string((int)compressedData[i].nextByte);
        // Concatenate strings into a single line
        string temp = temp_offset + ", " + temp_len + "," + temp_byte + "\n";
        // Write the line to the file
        outFile << compressedData[i].offset << "," << compressedData[i].length << "," << (int)compressedData[i].nextByte << endl;
    }
    // Close the file
    outFile.close();
}


// Converts a vector of bytes to a vector of integers
vector<int> convertBytesToIntegers(vector<unsigned char> bytes) {
    vector<int> integers;
    // Loops through every 4 bytes and converts them to an integer
    for (int i = 0; i < bytes.size(); i += 4) {
        int n = (bytes[i] << 24) | (bytes[i+1] << 16) | (bytes[i+2] << 8) | bytes[i+3];
        integers.push_back(n);
    }
    return integers;
}

vector<unsigned char> decode(vector<LZ77Token> input) {
    vector<unsigned char> output; // initialize an empty output vector
    for (int i = 0; i < input.size(); i++) { // iterate over all the LZ77 tokens in the input vector
        if (input[i].length > 0) { // check if the token represents a sequence of previously encoded bytes
            int start = output.size() - input[i].offset; // calculate the start index of the sequence in the output vector
            int end = start + input[i].length; // calculate the end index of the sequence in the output vector
            for (int j = start; j < end; j++) { // iterate over the sequence in the output vector and copy it to the end of the output vector
                output.push_back(output[j]);
            }
        }
        output.push_back(input[i].nextByte); // append the next byte to the end of the output vector
    }
    return output; // return the decoded output vector
}

void lz77(string workload_path, string encoded_path) {
    // Read the workload file 
    vector<int> data = read_data(workload_path);

    // Encoding
    auto start = std::chrono::high_resolution_clock::now();
    vector<unsigned char> bytes = convertIntegersToBytes(data);
    vector<LZ77Token> output = encode_lz77(bytes);
    auto end = std::chrono::high_resolution_clock::now();

    // printting the encoding time
    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
    cout << "Encoding took " << duration.count() << " nanoseconds." << endl;

    // writing encoded data to file
    write_encoded_data(output, encoded_path);

    // decoding
    vector<unsigned char> bytes1 = decode(output);
    vector<int> integers = convertBytesToIntegers(bytes1);
    
    // accuracy
    calculateAccuracy(data, integers);

    // compression ratio
    compression_ratio(workload_path, encoded_path);
}