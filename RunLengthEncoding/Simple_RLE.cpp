#include <iostream>
#include <string>

using namespace std;

string runLengthEncode(string input) {
    int count = 1;
    char currentChar = input[0];
    string output = "";

    for (int i = 1; i < input.length(); i++) {
        if (input[i] == currentChar) {
            count++;
        } else {
            output += to_string(count) + currentChar;
            count = 1;
            currentChar = input[i];
        }
    }

    // Add the last character sequence
    output += to_string(count) + currentChar;

    return output;
}

int main() {
    string input = "AAABBBCDDDDD";
    string output = runLengthEncode(input);
    cout << "Input: " << input << endl;
    cout << "Output: " << output << endl;
    return 0;
}
