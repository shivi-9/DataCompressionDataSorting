#include <iostream>
#include <fstream>
#include <queue>
#include <vector>
#include <unordered_map>
using namespace std;

struct Node {
    int freq;
    int val;
    Node* left;
    Node* right;

    Node(int freq, int val) {
        this->freq = freq;
        this->val = val;
        left = right = nullptr;
    }

    Node(int freq, int val, Node* left, Node* right) {
        this->freq = freq;
        this->val = val;
        this->left = left;
        this->right = right;
    }

    bool isLeaf() const {
        return (left == nullptr && right == nullptr);
    }
};

struct CompareNodes {
    bool operator()(const Node* lhs, const Node* rhs) const {
        return lhs->freq > rhs->freq;
    }
};

void generateCodes(Node* root, string code, unordered_map<int, string>& codes) {
    if (root == nullptr) return;

    if (root->isLeaf()) {
        codes[root->val] = code;
    } else {
        generateCodes(root->left, code + "0", codes);
        generateCodes(root->right, code + "1", codes);
    }
}

void huffmanEncode(int* data, int size) {
    unordered_map<int, int> freqMap;
    for (int i = 0; i < size; i++) {
        freqMap[data[i]]++;
    }

    priority_queue<Node*, vector<Node*>, CompareNodes> pq;
    for (auto& p : freqMap) {
        pq.push(new Node(p.second, p.first));
    }

    while (pq.size() > 1) {
        Node* left = pq.top();
        pq.pop();
        Node* right = pq.top();
        pq.pop();
        pq.push(new Node(left->freq + right->freq, -1, left, right));
    }

    unordered_map<int, string> codes;
    generateCodes(pq.top(), "", codes);

    ofstream outfile("./HuffmanEncoding/workload_encoded.dat", ios::binary);
    for (int i = 0; i < size; i++) {
        string code = codes[data[i]];
        for (char c : code) {
            outfile.write(&c, sizeof(char));
        }
    }
    outfile.close();
}

int main() {
    ifstream infile("./Workload/workload.dat", ios::binary);
    infile.seekg(0, ios::end);
    int size = infile.tellg() / sizeof(int);
    infile.seekg(0, ios::beg);

    int* data = new int[size];
    infile.read((char*)data, size * sizeof(int));
    infile.close();

    huffmanEncode(data, size);

    delete[] data;
    return 0;
}