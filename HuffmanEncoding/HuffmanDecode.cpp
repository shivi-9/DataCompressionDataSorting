#include <iostream>
#include <fstream>
#include <unordered_map>

using namespace std;

// Function to decode the Huffman encoded data using the code map
void decode(string encodedData, unordered_map<string, int> codeMap) {
    string currentCode = "";
    string decodedData = "";
    for (char& c : encodedData) {
        currentCode += c;
        if (codeMap.find(currentCode) != codeMap.end()) {
            decodedData += to_string(codeMap[currentCode]) + " ";
            currentCode = "";
        }
    }
    cout << "Decoded data: " << decodedData << endl;
}

// Function to read the encoded data and code map from a file
void readEncodedDataAndCodeMap(string& encodedData, unordered_map<string, int>& codeMap) {
    ifstream infile("./HuffmanEncoding/encoded_data.txt");
    if (infile.is_open()) {
        bool isCodeMap = true;
        string line;
        while (getline(infile, line)) {
            if (isCodeMap) {
                isCodeMap = false;
                continue;
            }
            encodedData += line;
        }
        infile.close();
        infile.open("./HuffmanEncoding/encoded_data.txt");
        isCodeMap = true;
        while (getline(infile, line)) {
            if (isCodeMap) {
                isCodeMap = false;
                continue;
            }
            int spaceIndex = line.find(" ");
            string code = line.substr(spaceIndex + 1);
            int data = stoi(line.substr(0, spaceIndex));
            codeMap[code] = data;
        }
        infile.close();
    }
    else {
        cerr << "Unable to open file" << endl;
    }
}

int main() {
    unordered_map<string, int> codeMap;
    string encodedData = "";
    readEncodedDataAndCodeMap(encodedData, codeMap);
    decode(encodedData, codeMap);
    return 0;
}
