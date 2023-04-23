#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <bitset>
#include <map>

using namespace std;

vector<int> read_data(string path){
    vector<int> data;
    ifstream inputFile(path);
    int num;
    while (inputFile >> num) {
        data.push_back(num);
    }

    inputFile.close();

    return data;
}

map<int, double> get_probabilities(vector<int> data){
    map<int, double> probability_map;
    int total_size = data.size();

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
    cout << "Working on " << node->value << endl;
    for (const auto& element : codes) {
        cout << element.first << " " << element.second << endl;
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

void write_encoded_data(string encodedData, map<int, double> probability_map, string path_file){
    ofstream outfile(path_file);
    
    // Check if the file was successfully opened
    if (!outfile) {
        cerr << "Error: could not open file" << endl;
    }

    outfile << "Frequency Distribution\n";

    // Iterate over the key-value pairs of the map and write them to the file
    for (const auto& pair : probability_map) {
        outfile << pair.first << " " << pair.second << endl;
    }
    
    outfile << "\nEnocoded Data\n";
    outfile << encodedData;
    outfile.close();
}

int main() {
    // Read the workload file 
    vector<int> data = read_data("./Workload/workload.txt");

    // Get the probabilities of each element
    map<int, double> probability_map = get_probabilities(data);

    // Build Huffman tree and generate prefix codes
    Node* root = buildHuffmanTree(probability_map);
    map<int, string> codes = generateCodes(root);

    // for (const auto& element : codes) {
    //     cout << element.first << " " << element.second << endl;
    // }

    // Encode the data using the prefix codes
    string encodedData = encode(data, codes);

    // Write encoded data and prob map to a .txt file
    write_encoded_data(encodedData, probability_map, "./HuffmanEncoding/encoded_data.txt");
    
    return 0; 
}