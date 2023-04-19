#include <iostream>
#include <fstream>
#include <queue>
#include <unordered_map>
#include <chrono>
#include <functional>

using namespace std;
using namespace std::chrono;

struct HuffmanNode {
    char data;
    int freq;
    HuffmanNode *left, *right;

    HuffmanNode(char data, int freq) {
        this->data = data;
        this->freq = freq;
        left = right = nullptr;
    }
};

struct CompareNodes {
    bool operator()(HuffmanNode* a, HuffmanNode* b) {
        return a->freq > b->freq;
    }
};

void encodeFile(string inputFile, string outputFile) {
    // Step 1: read input file and count frequencies of characters
    unordered_map<char, int> freqMap;
    ifstream input(inputFile);
    char ch;
    while (input.get(ch)) {
        freqMap[ch]++;
    }
    input.close();

    // Step 2: build Huffman tree from frequency map using Vitter's algorithm
    priority_queue<HuffmanNode*, vector<HuffmanNode*>, CompareNodes> minHeap;
    for (auto& p : freqMap) {
        minHeap.push(new HuffmanNode(p.first, p.second));
    }

    while (minHeap.size() > 1) {
        // take two smallest nodes
        HuffmanNode* left = minHeap.top(); minHeap.pop();
        HuffmanNode* right = minHeap.top(); minHeap.pop();

        // create a new node as a parent of the two smallest nodes
        HuffmanNode* parent = new HuffmanNode('$', left->freq + right->freq);
        parent->left = left;
        parent->right = right;

        // determine the optimal rank of the parent node
        int rank = 0;
        if (left->freq < right->freq) {
            swap(left, right);
        }
        while ((1 << rank) <= minHeap.size()) {
            HuffmanNode* node = minHeap.top();
            if (node->freq < parent->freq) {
                break;
            }
            minHeap.pop();
            if (left == node) {
                swap(left, right);
            }
            HuffmanNode* grandparent = new HuffmanNode('$', parent->freq + node->freq);
            grandparent->left = parent;
            grandparent->right = node;
            parent = grandparent;
            rank++;
        }

        // insert the parent node at the optimal rank
        minHeap.push(parent);
    }

    // Step 3: build codebook from Huffman tree
    unordered_map<char, string> codebook;
    function<void(HuffmanNode*, string)> buildCodebook = [&](HuffmanNode* node, string code) {
        if (!node) return;
        if (node->data != '$') codebook[node->data] = code;
        buildCodebook(node->left, code + "0");
        buildCodebook(node->right, code + "1");
    };
    buildCodebook(minHeap.top(), "");

    // Step 4: encode input file using codebook
    ofstream output(outputFile);
    input.open(inputFile);
    while (input.get(ch)) {
        output << codebook[ch];
    }
    input.close();
    output.close();
}

int main() {
    auto start = high_resolution_clock::now();
    encodeFile("./Workload/workload100k.txt", "./HuffmanEncoding/encoded_data.huffman_100k.txt");
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout << "Encoding took " << duration.count() << " microseconds.\n";
    return 0;
}