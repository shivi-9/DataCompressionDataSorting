#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <bitset>
#include <map>

using namespace std;

map<int, double> get_propbability(string path){
    map<int, double> probability_map;

    ifstream file(path);

    if(file.is_open()){
        string line;
        getline(file, line);

        while(getline(file, line)) {
            if(line.empty()){
                break;
            }

            int key = stoi(line.substr(0, line.find(" ")));
            double value = stod(line.substr(line.find(" ")+1));
            
            probability_map[key] = value;
        }

        // Close the file
        file.close();
    }
    else{
        cerr << "Failed to open file" << endl;
    }

    return probability_map;
}

string get_data(string path){
    string data;
    ifstream file(path);

    if(file.is_open()){
        string line;
        getline(file, line);

        while(getline(file, line)) {
            if(line.empty()){
                break;
            }
        }
        getline(file, line);
        getline(file, line);
        data = line;

        file.close();
    }
    else{
        cerr << "Failed to open file" << endl;
    }

    return data;
}

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

Node* buildHuffmanTree(const map<int, double>& freqMap) {
    priority_queue<Node*, vector<Node*>, Compare> pq;
    for (auto& p : freqMap) {
        Node* node = new Node(p.first, p.second);
        pq.push(node);
    }

    while (pq.size() > 1) {
        Node* left = pq.top(); pq.pop(); 
        cout << "Tree" << endl;
        cout << left->value << endl;
        Node* right = pq.top(); pq.pop();
        cout << right->value << endl;
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
    // for (const auto& element : codes) {
    //     cout << element.first << " " << element.second << endl;
    // }
    generateCodesHelper(node->left, code + "0", codes);
    generateCodesHelper(node->right, code + "1", codes);
}

map<int, string> generateCodes(Node* root) {
    map<int, string> codes;
    generateCodesHelper(root, "", codes);
    return codes;
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

int main() {
    // Read the frequency distribution from file
    map<int, double> probability_map = get_propbability("./HuffmanEncoding/encoded_data.txt");

    // Read the encoded data
    string encodedData = get_data("./HuffmanEncoding/encoded_data.txt");

    // Build Huffman tree and generate prefix codes
    Node* root = buildHuffmanTree(probability_map);
    map<int, string> codes = generateCodes(root);

    // for (const auto& element : codes) {
    //     cout << element.first << " " << element.second << endl;
    // }

    // Decode the encoded data
    vector<int> decodedData = decode(encodedData, root);

    // for (int element : decodedData) {
    //     cout << element << " ";
    // }
    // cout << endl;
    
    return 0;
}
