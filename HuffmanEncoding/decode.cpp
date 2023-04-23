#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <bitset>
#include <unordered_map>

using namespace std;

// Define a node structure for the Huffman tree
struct Node {
    int data;
    double prob;
    Node* left;
    Node* right;
    Node(int data, double prob) {
        this->data = data;
        this->prob = prob;
        left = right = nullptr;
    }
};

// Define a comparison function for the priority queue
struct Compare {
    bool operator()(Node* a, Node* b) {
        return a->prob > b->prob;
    }
};

// Build the Huffman tree
Node* buildTree(unordered_map<int, double>& prob) {
    priority_queue<Node*, vector<Node*>, Compare> pq;
    for (auto& it : prob) {
        pq.push(new Node(it.first, it.second));
    }
    while (pq.size() > 1) {
        Node* left = pq.top();
        pq.pop();
        Node* right = pq.top();
        pq.pop();
        Node* parent = new Node(-1, left->prob + right->prob);
        parent->left = left;
        parent->right = right;
        pq.push(parent);
    }
    return pq.top();
}

// Decode the Huffman encoded data
string decodeData(string encodedData, unordered_map<string, int>& codes) {
    string decodedData = "";
    string currCode = "";
    for (char c : encodedData) {
        currCode += c;
        if (codes.find(currCode) != codes.end()) {
            decodedData += to_string(codes[currCode]) + " ";
            currCode = "";
        }
    }
    return decodedData;
}

unordered_map<int, double> get_propbability(string path){
    unordered_map<int, double> probability_map;

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

unordered_map<int, int> convert_prob(unordered_map<int, double> probability_map){
    unordered_map<int, int> freq;
    int totalFreq = 0;
    for (auto& it : probability_map) {
        freq[it.first] = static_cast<int>(it.second * 1000);
        totalFreq += freq[it.first];
    }

    return freq;
}

int main() {
    // Read the frequency distribution from file
    unordered_map<int, double> probability_map = get_propbability("./HuffmanEncoding/encoded_data.txt");

    // Converting the prob into freq
    unordered_map<int, int> freq = convert_prob(probability_map);

    // Read the encoded data
    string encodeddata = get_data("./HuffmanEncoding/encoded_data.txt");

    // Build the Huffman tree
    Node* root = buildTree(probability_map);

    // Generate Huffman codes for each integer value
    unordered_map<string, int> codes;
    function<void(Node*, string)> traverse = [&](Node* node, string code) {
        if (node == nullptr) {
            return;
        }
        if (node->data != -1) {
            codes[code] = node->data;
        }
        traverse(node->left, code + "0");
        traverse(node->right, code + "1");
    };

    traverse(root, "");

    // Decode the Huffman encoded data
    string decodedData = decodeData(encodeddata, codes);
    
    // Output the decoded data
    cout << decodedData << endl;

    return 0;
}
