#ifndef HUFFMAN_H
#define HUFFMAN_H
#include "Huffman.h"
#include <vector>
#include <string>
#include <map>
 
using namespace std;

map<int, double> get_probabilities(vector<int> data); // Returns a map of the probability of each data value in the given vector

// Node struct for building the Huffman tree
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

// Comparison function for priority queue used in building the Huffman tree
struct Compare {
    bool operator()(Node* a, Node* b) {
        return a->frequency > b->frequency;
    }
};

Node* buildHuffmanTree(const map<int, double>& freqMap); // Builds the Huffman tree and returns the root node
void generateCodesHelper(Node* node, string code, map<int, string>& codes); // Helper function for generateCodes that recursively generates Huffman codes for each node
map<int, string> generateCodes(Node* root); // Returns a map of Huffman codes for each data value given the root node of the Huffman tree
string encode(const vector<int>& data, const map<int, string>& codes); // Encodes the given data using the given Huffman codes and returns the encoded string
void write_encoded_data(string encodedData, string path_file); // Writes the encoded data to a file
vector<int> decode(string encodedData, Node* root); // Decodes the given encoded string using the given Huffman tree and returns the decoded data
void huffman(string workload_path, string encoded_path); // Encapsulates the Huffman coding process

#endif