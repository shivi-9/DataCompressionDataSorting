#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <bitset>
#include <map>
#include <chrono>
#include <algorithm>
#include "Helper.h"
#include "Huffman.h"

using namespace std;

// function to get frequency map of the input data
map<int, double> get_frequency(vector<int> data){
    map<int, double> frequency_map;
    int total_size = data.size(); 

    // sort the data
    sort(data.begin(), data.end());

    // calculate frequency of each integer in the data
    for (int i = 0; i < total_size; i++) {
        int current_int = data[i];

        if (frequency_map.find(current_int) == frequency_map.end()) {
            frequency_map[current_int] = 1.0 / total_size;
        } 
        else {
            frequency_map[current_int] += 1.0 / total_size;
        }
    }

    return frequency_map;
}

// function to build Huffman tree based on the frequency map
Node* buildHuffmanTree(const map<int, double>& freqMap) {
    // create a priority queue to store nodes in non-decreasing order of their frequency
    priority_queue<Node*, vector<Node*>, Compare> pq;
    // create a node for each integer and add it to the priority queue
    for (auto& p : freqMap) {
        Node* node = new Node(p.first, p.second);
        pq.push(node);
    }

    // build the Huffman tree by merging the two nodes with the smallest frequency until only one node remains
    while (pq.size() > 1) {
        Node* left = pq.top(); pq.pop();
        Node* right = pq.top(); pq.pop();
        Node* parent = new Node(-1, left->frequency + right->frequency);
        parent->left = left;
        parent->right = right;
        pq.push(parent);
    }
    return pq.top();
}

// helper function to generate codes for each integer in the Huffman tree
void generateCodesHelper(Node* node, string code, map<int, string>& codes) {
    if (node == nullptr) return;
    // if the node represents an integer, add its code to the map
    if (node->value != -1) codes[node->value] = code;
    // recursively generate codes for the left and right children of the node
    generateCodesHelper(node->left, code + "0", codes);
    generateCodesHelper(node->right, code + "1", codes);
}

// function to generate codes for each integer in the Huffman tree
map<int, string> generateCodes(Node* root) {
    map<int, string> codes;
    generateCodesHelper(root, "", codes);
    return codes;
}

// function to encode the input data using the generated codes
string encode(const vector<int>& data, const map<int, string>& codes) {
    string encoded = "";
    for (int i = 0; i < data.size(); i++) {
        encoded += codes.at(data[i]);
    }
    return encoded;
}

// function to write the encoded data to a binary file
void write_encoded_data(string encodedData, string path_file){
    ofstream outfile(path_file);
    
    // Check if the file was successfully opened
    if (!outfile) {
        cerr << "Error: could not open file" << endl;
    }

    // convert the encoded data to binary form
    int numBytes = encodedData.size() / 8;
    string result(numBytes, '\0');
    for (int i = 0; i < numBytes; i++) {
        bitset<8> bits(encodedData.substr(i * 8, 8));
        result[i] = static_cast<char>(bits.to_ulong());
    }
    
    outfile << result;
    outfile.close();
}

vector<int> decode(string encodedData, Node* root) {
    // This function takes the encoded data and the root node of the Huffman tree as input
    vector<int> decodedData;
    Node* current = root;

    // Loop through the encoded data one character at a time
    for (char c : encodedData) {
        // If the character is '0', move to the left child of the current node
        if (c == '0') {
            current = current->left;
        } else { // Otherwise, move to the right child of the current node
            current = current->right;
        }

        // If the current node is a leaf node (i.e., has no children), then add its value to the decoded data
        // and move back to the root node to continue decoding
        if (current->left == nullptr && current->right == nullptr) {
            decodedData.push_back(current->value);
            current = root;
        }
    }

    // Return the decoded data
    return decodedData;
}

void huffman(string workload_path, string encoded_path){
    // Read the workload file 
    vector<int> workload = read_data(workload_path);

    // Encoding
    auto start_ = chrono::high_resolution_clock::now();
    map<int, double> frequency_map = get_frequency(workload);
    Node* root = buildHuffmanTree(frequency_map);
    map<int, string> codes = generateCodes(root);
    string encodedData = encode(workload, codes);
    auto stop_ = chrono::high_resolution_clock::now();
    
    // printing encoding time
    auto duration_ = std::chrono::duration_cast<std::chrono::nanoseconds>(stop_ - start_);
    unsigned long long time_taken = duration_.count();
    std::cout << "Time taken = " << time_taken << " nanoseconds" << endl;

    // Write encoded data and frequency map to a .txt file
    write_encoded_data(encodedData, encoded_path);

    // Decode the encoded data
    vector<int> decodedData = decode(encodedData, root);

    // accuracy
    calculateAccuracy(workload, decodedData);

    // compression ratio
    compression_ratio(workload_path, encoded_path);
}
