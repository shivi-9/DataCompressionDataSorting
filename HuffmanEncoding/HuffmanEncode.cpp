#include <iostream>
#include <fstream>
#include <chrono>
#include <queue>
#include <unordered_map>
#include <bitset>

using namespace std;

struct Node {
    char data;
    int freq;
    Node *left, *right;

    Node(char data, int freq) {
        this->data = data;
        this->freq = freq;
        left = right = nullptr;
    }

    ~Node() {
        delete left;
        delete right;
    }
};

struct Compare {
    bool operator()(Node* left, Node* right) {
        return left->freq > right->freq;
    }
};

unordered_map<char, int> getFrequencies(string filename) {
    unordered_map<char, int> freq;

    ifstream input(filename, ios::binary);
    char c;

    while (input.get(c)) {
        freq[c]++;
    }

    input.close();

    return freq;
}

Node* buildHuffmanTree(unordered_map<char, int> freq) {
    priority_queue<Node*, vector<Node*>, Compare> pq;

    for (auto it = freq.begin(); it != freq.end(); it++) {
        pq.push(new Node(it->first, it->second));
    }

    while (pq.size() != 1) {
        Node* left = pq.top();
        pq.pop();

        Node* right = pq.top();
        pq.pop();

        Node* node = new Node('$', left->freq + right->freq);
        node->left = left;
        node->right = right;

        pq.push(node);
    }

    return pq.top();
}

void getCodes(Node* root, string code, unordered_map<char, string>& codes) {
    if (root == nullptr) {
        return;
    }

    if (root->data != '$') {
        codes[root->data] = code;
    }

    getCodes(root->left, code + "0", codes);
    getCodes(root->right, code + "1", codes);
}

void compressFile(string inputFilename, string outputFilename) {
    auto start = chrono::high_resolution_clock::now();

    unordered_map<char, int> freq = getFrequencies(inputFilename);
    Node* root = buildHuffmanTree(freq);
    unordered_map<char, string> codes;
    getCodes(root, "", codes);

    ofstream output(outputFilename, ios::binary);

    // Write the Huffman tree to the compressed file
    output << codes.size() << "\n";
    for (auto it = codes.begin(); it != codes.end(); it++) {
        output << it->first << " " << it->second << "\n";
    }

    // Write the compressed data to the compressed file
    ifstream input(inputFilename, ios::binary);
    char c;
    string code;
    while (input.get(c)) {
        code += codes[c];
        while (code.length() >= 8) {
            bitset<8> b(code.substr(0, 8));
            output.put((char) b.to_ulong());
            code = code.substr(8);
        }
    }

    // Write the last byte to the compressed file
    if (code.length() > 0) {
        bitset<8> b(code);
        output.put((char) b.to_ulong());
    }

    input.close();
    output.close();

    auto end = chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
    cout << "Compression time: " << duration.count() << " nanoseconds." << endl;
}

int main() {
    compressFile("./Workload/workload100k.txt", "./HuffmanEncoding/encoded_data_huffman.txt");
    return 0;
}