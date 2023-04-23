#include <iostream>
#include <fstream>
#include <queue>
#include <unordered_map>
#include <vector>

using namespace std;

// A Huffman tree node
struct Node {
    int data;
    unsigned freq;
    Node* left;
    Node* right;
    Node(int data, unsigned freq) {
        left = right = nullptr;
        this->data = data;
        this->freq = freq;
    }
};

// Function to compare two nodes based on their frequency
struct compare {
    bool operator()(Node* l, Node* r) {
        return l->freq > r->freq;
    }
};

// Traverse the Huffman tree and store codes in a map
void encode(Node* root, string str, unordered_map<int, string>& huffmanCode) {
    if (root == nullptr) {
        return;
    }
    if (!root->left && !root->right) {
        huffmanCode[root->data] = str;
    }
    encode(root->left, str + "0", huffmanCode);
    encode(root->right, str + "1", huffmanCode);
}

// Build Huffman tree and encode the data
void buildHuffmanTree(int data[], int size, unordered_map<int, string>& huffmanCode) {
    unordered_map<int, unsigned> freq;
    for (int i = 0; i < size; i++) {
        freq[data[i]]++;
    }
    priority_queue<Node*, vector<Node*>, compare> pq;
    for (auto& p : freq) {
        pq.push(new Node(p.first, p.second));
    }
    while (pq.size() != 1) {
        Node* left = pq.top(); pq.pop();
        Node* right = pq.top(); pq.pop();
        Node* node = new Node(-1, left->freq + right->freq);
        node->left = left;
        node->right = right;
        pq.push(node);
    }
    encode(pq.top(), "", huffmanCode);
}

// Print the encoded data and write to a file
void printAndWriteEncodedData(int data[], int size, unordered_map<int, string> huffmanCode) {
    // cout << "Encoded data:" << endl;
    string encodedData = "";
    for (int i = 0; i < size; i++) {
        encodedData += huffmanCode[data[i]];
        // encodedData += '\n';
    }
    // cout << encodedData << endl;

    ofstream outfile("./HuffmanEncoding/encoded_data.txt");
    if (outfile.is_open()) {
        outfile << "Huffman code map:" << endl;
        for (auto& p : huffmanCode) {
            outfile << p.first << " " << p.second << endl;
        }
        outfile << "\n";
        outfile << "Encoded data:" << endl;
        outfile << encodedData;
        outfile.close();
        cout << "Encoded data written to encoded_data.txt" << endl;
    }
    else {
        cerr << "Unable to open file" << endl;
    }
}

int main() {
    ifstream infile("./Workload/workload.txt");
    vector<int> data;
    int num;
    while (infile >> num) {
        data.push_back(num);
    }
    int size = data.size();
    int* dataArray = &data[0];
    unordered_map<int, string> huffmanCode;
    buildHuffmanTree(dataArray, size, huffmanCode);
    printAndWriteEncodedData(dataArray, size, huffmanCode);
    return 0;
}