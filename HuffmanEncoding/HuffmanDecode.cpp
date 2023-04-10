#include <iostream>
#include <fstream>
#include <queue>
#include <unordered_map>

using namespace std;

// Structure for nodes of Huffman tree
struct Node {
    char data;
    int freq;
    Node* left;
    Node* right;

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

// Comparator for priority queue
struct comp {
    bool operator()(Node* l, Node* r) {
        return l->freq > r->freq;
    }
};

// Build Huffman tree and return the root node
Node* buildHuffmanTree(const string& data) {
    unordered_map<char, int> freqMap;
    for (char c : data) {
        freqMap[c]++;
    }

    priority_queue<Node*, vector<Node*>, comp> pq;
    for (auto& p : freqMap) {
        pq.push(new Node(p.first, p.second));
    }

    while (pq.size() != 1) {
        Node* left = pq.top();
        pq.pop();

        Node* right = pq.top();
        pq.pop();

        Node* newNode = new Node('\0', left->freq + right->freq);
        newNode->left = left;
        newNode->right = right;

        pq.push(newNode);
    }

    return pq.top();
}

// Traverse Huffman tree to decode the encoded data
string decodeData(const string& encodedData, Node* root) {
    string decodedData = "";
    Node* curr = root;
    for (char c : encodedData) {
        if (c == '0') {
            curr = curr->left;
        }
        else {
            curr = curr->right;
        }

        if (curr->left == nullptr && curr->right == nullptr) {
            decodedData += curr->data;
            curr = root;
        }
    }

    return decodedData;
}

int main() {
    // Read encoded data from file
    ifstream encodedFile("./HuffmanEncoding/workload_encoded.dat", ios::binary);
    string encodedData((istreambuf_iterator<char>(encodedFile)), istreambuf_iterator<char>());
    encodedFile.close();

    // Build Huffman tree
    Node* root = buildHuffmanTree(encodedData);

    // Decode data
    string decodedData = decodeData(encodedData, root);

    // Write decoded data to file
    ofstream decodedFile("./HuffmanEncoding/workload_decoded.dat", ios::binary);
    decodedFile.write(decodedData.c_str(), decodedData.size());
    decodedFile.close();

    // Free memory
    delete root;

    return 0;
}