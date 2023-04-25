#include <iostream>
#include <fstream>
using namespace std;

double calculateAccuracy(const string& originalFile, const string& decodedFile) {
    ifstream infile1(originalFile, ios::binary);
    ifstream infile2(decodedFile, ios::binary);

    int numBytesMatched = 0;
    int numBytesTotal = 0;
    char c1, c2;
    while (infile1.read(&c1, sizeof(char)) && infile2.read(&c2, sizeof(char))) {
        if (c1 == c2) {
            numBytesMatched++;
        }
        numBytesTotal++;
    }

    infile1.close();
    infile2.close();

    return (double)numBytesMatched / numBytesTotal * 100;
}

int main() {
    double accuracy = calculateAccuracy("./Workload/Workload40KB/100_100.txt", "./HuffmanEncoding/decoded_data.txt");
    cout << "Accuracy: " << accuracy << "%" << endl;
    return 0;
}