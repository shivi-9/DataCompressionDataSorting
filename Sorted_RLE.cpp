#include <iostream>
#include <vector>

std::vector<std::pair<int, int>> runLengthEncoding(std::vector<int>& data) {
    std::vector<std::pair<int, int>> encodedData;
    int count = 1;
    
    for (int i = 1; i < data.size(); i++) {
        if (data[i] == data[i-1]) {
            count++;
        } else {
            encodedData.push_back(std::make_pair(count, data[i-1]));
            count = 1;
        }
    }
    
    // Handle the last run of values
    encodedData.push_back(std::make_pair(count, data[data.size()-1]));
    
    return encodedData;
}

int main() {
    std::vector<int> sortedData = {2, 2, 2, 3, 3, 5, 5, 5, 5, 5};
    std::vector<std::pair<int, int>> encodedData = runLengthEncoding(sortedData);
    
    for (auto& p : encodedData) {
        std::cout << "(" << p.first << ", " << p.second
