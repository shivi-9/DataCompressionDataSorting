#include <iostream>
#include <vector>

using namespace std;

vector<int> runLengthEncode(vector<int> input) {
    int count = 1;
    int currentValue = input[0];
    vector<int> output;

    for (int i = 1; i < input.size(); i++) {
        if (input[i] == currentValue) {
            count++;
        } else {
            output.push_back(count);
            output.push_back(currentValue);
            count = 1;
            currentValue = input[i];
        }
    }

    // Add the last integer sequence
    output.push_back(count);
    output.push_back(currentValue);

    return output;
}

int main() {
    vector<int> input = {1, 1, 1, 2, 2, 2, 2, 3, 3, 4, 4, 4};
    vector<int> output = runLengthEncode(input);
    
    // Print the input and encoded output arrays
    cout << "Input: ";
    for (int i = 0; i < input.size(); i++) {
        cout << input[i] << " ";
    }
    cout << endl;

    cout << "Output: ";
    for (int i = 0; i < output.size(); i++) {
        cout << output[i] << " ";
    }
    cout << endl;

    return 0;
}
