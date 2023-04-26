#include <iostream>
#include <vector>
#include <bitset>
#include <fstream>

// Function to decode integer data using LZ77 with bitset
std::vector<int> decodeLZ77(std::vector<std::bitset<32>> encodedData)
{
    std::vector<int> decodedData;
    int windowSize=8;
    int bufferSize=4;

    // Initialize search buffer and lookahead buffer
    std::vector<int> searchBuffer(windowSize, -1);
    std::vector<int> lookaheadBuffer(bufferSize, -1);

    int searchIndex = 0;
    int lookaheadIndex = 0;

    // Decode first byte
    decodedData.push_back(encodedData[0].to_ulong());

    for (int i = 1; i < encodedData.size(); i++) {
        // Extract token from bitset
        int tokenValue = encodedData[i].to_ulong();
        int offset = (tokenValue >> 16) & 0xff;
        int length = (tokenValue >> 8) & 0xff;
        int nextByte = tokenValue & 0xff;

        // Copy matching data from search buffer to lookahead buffer
        for (int j = 0; j < length; j++) {
            lookaheadBuffer[lookaheadIndex % bufferSize] = searchBuffer[(searchIndex - offset + j) % windowSize];
            decodedData.push_back(lookaheadBuffer[lookaheadIndex % bufferSize]);
            lookaheadIndex++;
            searchIndex++;
        }

        // Add next byte to lookahead buffer and decoded data
        lookaheadBuffer[lookaheadIndex % bufferSize] = nextByte;
        decodedData.push_back(nextByte);
        lookaheadIndex++;

        // Slide search buffer
        searchIndex = (searchIndex - length) % windowSize;
        for (int j = 0; j < length; j++) {
            searchBuffer[searchIndex] = lookaheadBuffer[(lookaheadIndex - length + j) % bufferSize];
            searchIndex = (searchIndex + 1) % windowSize;
        }
    }

    return decodedData;
}

// Example usage
int main()
{
    std::ifstream infile("./encod.txt", std::ios::binary);
    std::vector<std::bitset<32>> data;
    std::bitset<32> element;
    while (infile >> element)
    {
        data.push_back(element);
    }

    auto start = std::chrono::high_resolution_clock::now();
    std::vector<int> decodedData = decodeLZ77(data);
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);

    std::ofstream output_file("./decoded_data_LZ77.txt");

    std::ostream_iterator<int> output_iterator(output_file, "\n");
    std::copy(std::begin(decodedData), std::end(decodedData), output_iterator);
    output_file.close();
    return 0;
}

