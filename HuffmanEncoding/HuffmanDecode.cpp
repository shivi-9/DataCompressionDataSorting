#include <iostream>
#include <fstream>
#include <chrono>
#include <unordered_map>

using namespace std;

struct Node {
    char data;
    Node *left, *right;

    Node(char data) {
        this->data = data;
        left = right = nullptr;
    }

    ~Node() {
        delete left;
        delete right;
    }
};

Node* buildHuffmanTree(unordered_map<char, string> codes) {
    // cout << "Check4";
    Node* root = new Node('$');
    for (auto it = codes.begin(); it != codes.end(); it++) {
        // cout << "Check5";
        Node* current = root;
        string code = it->second;
        for (int i = 0; i < code.length(); i++) {
            // cout << "Check5";
            if (code[i] == '0') {
                if (current->left == nullptr) {
                    current->left = new Node('$');
                }
                current = current->left;
            } else {
                if (current->right == nullptr) {
                    current->right = new Node('$');
                }
                current = current->right;
            }
        }
        current->data = it->first;
    }
    cout << "Check6\n";
    return root;
}

void decodeFile(string inputFilename, string outputFilename, Node* root) {
    cout << "Check8";
    cout << "Check8";
    cout << "Check8";
    auto start = chrono::high_resolution_clock::now();

    ifstream input(inputFilename, ios::binary);
    ofstream output(outputFilename);

    // Read the number of codes from the input file
    int numCodes;
    input >> numCodes;

    // Read the Huffman codes from the input file
    unordered_map<string, char> codes;
    for (int i = 0; i < numCodes; i++) {
        cout << "Check9";
        char c;
        string code;
        input >> c >> code;
        codes[code] = c;
    }

    // Decode the data and write it to the output file
    Node* current = root;
    char c;
    while (input.get(c)) {
        cout << "Check10";
        for (int i = 7; i >= 0; i--) {
            cout << "Check11";
            if (c & (1 << i)) {
                current = current->right;
            } else {
                current = current->left;
            }
            if (current->data != '$') {
                output << current->data;
                current = root;
            }
        }
    }

    input.close();
    output.close();
    cout << "Check12";

    auto end = chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
    cout << "Decompression time: " << duration.count() << " nanoseconds." << endl;
}


int main() {
    //  cout << "Check1\n";
    // Read the Huffman codes from the encoded data file
   

    ifstream input("./HuffmanEncoding/encoded_data_huffman.txt", ios::binary);
    int numCodes;
    input >> numCodes;
    unordered_map<char, string> codes;

    // cout << "Check1\n";

    for (int i = 0; i < numCodes; i++) {
        // cout << "Check2\n";
        char c;
        string code;
        input >> c >> code;
        codes[c] = code;
    }
    input.close();

    // cout << "Check3\n";
    // Build the Huffman tree from the codes
    Node* root = buildHuffmanTree(codes);
    cout << "Check7\n";

    // Decode the encoded data and save it to a text file
    decodeFile("./HuffmanEncoding/encoded_data_huffman.txt", "./HuffmanEncoding/decoded_data_huffman.txt", root);

    return 0;
}
