# DataCompressionDataSorting
Exploring the Performance of Data Compression Algorithms with Varying Data Sortedness 

## Contributors:
1. Shivangi
2. Vani Singhal

## Problem Statement
Our aim for this project is to compare the performance of different Data Compression Algorithms with changing levels of Data Sortedness and understand the relationship between Data sortedness on the performance of Data Compression Algorithms. As we all know, Data is rarely sorted in real-world scenarios therefore, we also want to compare these Data Compression Algorithms and try to find the one that performs the best with partially sorted Data.

## Dependencies
* Snappy
* C++ compiler

## Installation Instructions
To compile and run the make file for running the compression algorithms:
1. Ensure that g++ and snappy are installed on your system. If they are not installed, please install them before proceeding.
2. Download or clone the repository to your local machine.
3. Go to the make file, add the arguments. First argument is the path to the workload, second argument is the path where you want to save the encoded file, and for third argument:
    * Add 1 for Delta encoding
    * Add 2 for Huffman Encoding
    * Add 3 for LZ77 Encoding
    * Add 4 for Run Length Encoding
    * Add 5 for Snappy Algorithm
4. Open a terminal and navigate to the directory where you downloaded the repository.
5. Run the following command to compile the program:
```
make run
```

To generate workloads, follow the following steps:
1. Ensure that python interpreter is install on your system.
2. Download or clone the repository to your local machine.
3. Go to the WorkloadGenerator.py file and update the arguments. The first argument is the number of elements you want in your workload, second is the K value followed by L value and path where you want to save the workload.txt file
4. Open a terminal and navigate to the directory where you downloaded the repository.
5. Run the following commands:
```
python WorkloadGenerator.py
```