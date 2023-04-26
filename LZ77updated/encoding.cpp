#include <iostream>
#include <vector>
#include <bitset>
#include <fstream>
#include <chrono>

// Structure to represent an LZ77 token
struct LZ77Token {
    int offset;
    int length;
    int nextByte;
};
std::vector<int> read_data(std::string path){
    std::vector<int> data;
    std::ifstream inputFile(path);
    int num;
    while (inputFile >> num) {
        data.push_back(num);
    }

    inputFile.close();

    return data;
}

// Function to encode integer data using LZ77 with bitset
std::vector<std::bitset<32>> encodeLZ77(std::vector<int> data)
{
    std::vector<std::bitset<32>> encodedData;
    int windowSize = 8;
    int bufferSize = 4;

    // Initialize search buffer and lookahead buffer
    std::vector<int> searchBuffer(windowSize, -1);
    std::vector<int> lookaheadBuffer(bufferSize, -1);

    int searchIndex = 0;
    int lookaheadIndex = 0;

    // Encode first byte
    encodedData.push_back(std::bitset<32>(data[0]));

    while (lookaheadIndex < data.size()) {
        // Find longest match in search buffer
        int maxLength = 0;
        int maxOffset = 0;
        int nextByte = data[lookaheadIndex];
        for (int i = 0; i < searchIndex; i++) {
            int length = 0;
            while (length < bufferSize && lookaheadIndex + length < data.size() &&
                   searchBuffer[i + length] == data[lookaheadIndex + length]) {
                length++;
            }
            if (length > maxLength) {
                maxLength = length;
                maxOffset = searchIndex - i;
                nextByte = lookaheadIndex + length < data.size() ? data[lookaheadIndex + length] : -1;
            }
        }

        // Add token to encoded data
        LZ77Token token;
        token.offset = maxOffset;
        token.length = maxLength;
        token.nextByte = nextByte;
        encodedData.push_back(std::bitset<32>((token.offset << 16) | (token.length << 8) | token.nextByte));

        // Slide search buffer and lookahead buffer
        for (int i = 0; i < maxLength; i++) {
            searchBuffer[searchIndex + i] = lookaheadBuffer[lookaheadIndex + i];
        }
        searchIndex += maxLength;
        lookaheadIndex += maxLength;
        if (lookaheadIndex < data.size()) {
            lookaheadBuffer[lookaheadIndex % bufferSize] = data[lookaheadIndex];
            lookaheadIndex++;
        }
    }

    return encodedData;
}

// Example usage
int main()
{
    std::vector<int> data = read_data("./workload1.txt");

    auto start = std::chrono::high_resolution_clock::now();
    std::vector<std::bitset<32>> encodedData = encodeLZ77(data);
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);

    std::ofstream output_file("./encoded_data_LZ77.txt");

    std::ostream_iterator<int> output_iterator(output_file, "\n");
    std::copy(std::begin(encodedData), std::end(encodedData), output_iterator);
    output_file.close();
    return 0;
}
