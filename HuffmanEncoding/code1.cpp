#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <bitset>
#include <map>
#include <chrono>

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

void generateCodesHelper(Node* node, string code, map<int, bitset<8>>& codes) {
    if (node == nullptr) return;
    if (node->value != -1) codes[node->value] = bitset<8>(code);
    generateCodesHelper(node->left, code + "0", codes);
    generateCodesHelper(node->right, code + "1", codes);
}

map<int, bitset<8>> generateCodes(Node* root) {
    map<int, bitset<8>> codes;
    string code = "";
    generateCodesHelper(root, code, codes);
    cout << "Code: " << code << "\n";
    return codes;
}

// vector<bool> encode(const vector<int>& data, const map<int, bitset<8>>& codes) {
//     vector<bool> encoded;
//     for (int i = 0; i < data.size(); i++) {
//         bool code = codes.at(data[i]);
//         encoded.push_back(code);
//     }
//     return encoded;
// }

void write_encoded_data(vector<bitset<8>> encodedData, string path_file){
    ofstream outfile(path_file);
    
    // Check if the file was successfully opened
    if (!outfile) {
        cerr << "Error: could not open file" << endl;
    }
    for (const auto& b : encodedData) {
        outfile << b.to_string();
    }
    outfile.close();
}

struct BitSetComparer {
    bool operator() (const bitset<8>& a, const bitset<8>& b) const {
        for (int i = 7; i >= 0; i--) {
            if (a[i] != b[i]) {
                return a[i] < b[i];
            }
        }
        return false;
    }
};

vector<int> decode(vector<bitset<8>> encodedData, map<int, bitset<8>> codes) {
    vector<int> decodedData;
    map< bitset<8>, int, BitSetComparer> reverseCodebook;

    // Build reverse codebook
    for (const auto& p : codes) {
        reverseCodebook[p.second] = p.first;
    }

    for (const auto& p : reverseCodebook) {
        cout << p.first << " : " << p.second<<endl;
    }

    // Traverse Huffman tree
    bitset<8> code;
    for (const auto& bits : encodedData) {
        code <<= 8;
        code |= bits;
        cout<< code<<endl;
        if (reverseCodebook.count(code) > 0) {
            decodedData.push_back(reverseCodebook[code]);
            code.reset();
        }
    }   
    return decodedData;
}

void write_decoded_data(vector<int> decodedData, string path_file){
    ofstream outfile(path_file);
    
    // Check if the file was successfully opened
    if (!outfile) {
        cerr << "Error: could not open file" << endl;
    }

    // Iterate over the key-value pairs of the map and write them to the file
    for (int pair : decodedData) {
        outfile << pair << endl;
    }
}

int main() {
    // Read the workload file 
    vector<int> data = read_data("../Workload/100_1.txt");

    auto start_ = std::chrono::high_resolution_clock::now();

    // Get the probabilities of each element
    map<int, double> probability_map = get_probabilities(data);

    // Build Huffman tree and generate prefix codes
    Node* root = buildHuffmanTree(probability_map);
    map<int, bitset<8>> codes = generateCodes(root);

    for (const auto& p : codes) {
        cout << p.first << " : " << p.second<<endl;
    }

    // for (int i = 0; i < data.size(); i++) {
    //     cout << data[i] << " ";
    // }

    // Encode the data using the prefix codes
    // vector<bool> encodedData = encode(data, codes);
    
    // auto stop_ = std::chrono::high_resolution_clock::now();
    // auto duration_ = std::chrono::duration_cast<std::chrono::nanoseconds>(stop_ - start_);
    // unsigned long long time_taken = duration_.count();
    // // std::cout << "Time taken = " << time_taken << " nanoseconds" << endl;

    // // Write encoded data and prob map to a .txt file
    // write_encoded_data(encodedData, "./HuffmanEncoding/EncodedData/100_1.txt");

    // // Decode the encoded data
    // vector<int> decodedData = decode(encodedData, codes);

    // write_decoded_data(decodedData, "./HuffmanEncoding/DecodedData/100_1.txt");
    
    return 0; 
}
