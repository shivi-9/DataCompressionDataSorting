#ifndef HUFFMAN_H
#define HUFFMAN_H
#include "Huffman.h"
#include <vector>
#include <string>
#include <map>

using namespace std;

map<int, double> get_probabilities(vector<int> data);

struct Node {
    int value;
    double frequency;
    Node* left;
    Node* right;
    Node(int value, double frequency) {
        this->value = value;
        this->frequency = frequency;
        left = right = nullptr;
    }
};

struct Compare {
    bool operator()(Node* a, Node* b) {
        return a->frequency > b->frequency;
    }
};

Node* buildHuffmanTree(const map<int, double>& freqMap);
void generateCodesHelper(Node* node, string code, map<int, string>& codes);
map<int, string> generateCodes(Node* root);
string encode(const vector<int>& data, const map<int, string>& codes);
void write_encoded_data(string encodedData, string path_file);
vector<int> decode(string encodedData, Node* root);
void huffman(string workload_path, string encoded_path);

#endif
