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

map<int, double> get_probabilities(vector<int> data){
    map<int, double> probability_map;
    int total_size = data.size(); 

    // sort the data
    sort(data.begin(), data.end());

    for (int i = 0; i < total_size; i++) {
        int current_int = data[i];

        if (probability_map.find(current_int) == probability_map.end()) {
            probability_map[current_int] = 1.0 / total_size;
        } 
        else {
            probability_map[current_int] += 1.0 / total_size;
        }
    }

    return probability_map;
}

Node* buildHuffmanTree(const map<int, double>& freqMap) {
    priority_queue<Node*, vector<Node*>, Compare> pq;
    for (auto& p : freqMap) {
        Node* node = new Node(p.first, p.second);
        pq.push(node);
    }
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

void generateCodesHelper(Node* node, string code, map<int, string>& codes) {
    if (node == nullptr) return;
    if (node->value != -1) codes[node->value] = code;
    // cout << "Working on " << node->value << endl;
    for (const auto& element : codes) {
        // cout << element.first << " " << element.second << endl;
    }
    generateCodesHelper(node->left, code + "0", codes);
    generateCodesHelper(node->right, code + "1", codes);
}

map<int, string> generateCodes(Node* root) {
    map<int, string> codes;
    generateCodesHelper(root, "", codes);
    return codes;
}

string encode(const vector<int>& data, const map<int, string>& codes) {
    string encoded = "";
    for (int i = 0; i < data.size(); i++) {
        encoded += codes.at(data[i]);
    }
    return encoded;
}

void write_encoded_data(string encodedData, string path_file){
    ofstream outfile(path_file);
    
    // Check if the file was successfully opened
    if (!outfile) {
        cerr << "Error: could not open file" << endl;
    }

    int numBytes = encodedData.size() / 8;
    string result(numBytes, '\0');
    for (int i = 0; i < numBytes; i++) {
        std::bitset<8> bits(encodedData.substr(i * 8, 8));
        result[i] = static_cast<char>(bits.to_ulong());
    }
    
    outfile << result;
    outfile.close();
}

vector<int> decode(string encodedData, Node* root) {
    vector<int> decodedData;
    Node* current = root;
    for (char c : encodedData) {
        if (c == '0') {
            current = current->left;
        } else {
            current = current->right;
        }
        if (current->left == nullptr && current->right == nullptr) {
            decodedData.push_back(current->value);
            current = root;
        }
    }
    return decodedData;
}

void huffman(string workload_path, string encoded_path){
    // Read the workload file 
    vector<int> workload = read_data(workload_path);

    // Encoding
    auto start_ = std::chrono::high_resolution_clock::now();
    map<int, double> probability_map = get_probabilities(workload);
    Node* root = buildHuffmanTree(probability_map);
    map<int, string> codes = generateCodes(root);
    string encodedData = encode(workload, codes);
    auto stop_ = std::chrono::high_resolution_clock::now();
    
    // printing encoding time
    auto duration_ = std::chrono::duration_cast<std::chrono::nanoseconds>(stop_ - start_);
    unsigned long long time_taken = duration_.count();
    std::cout << "Time taken = " << time_taken << " nanoseconds" << endl;

    // Write encoded data and prob map to a .txt file
    write_encoded_data(encodedData, encoded_path);

    // Decode the encoded data
    vector<int> decodedData = decode(encodedData, root);

    // accuracy
    calculateAccuracy(workload, decodedData);

    // compression ratio
    compression_ratio(workload_path, encoded_path);
}
