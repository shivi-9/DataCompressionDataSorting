# DataCompressionDataSorting
Exploring the Performance of Data Compression Algorithms with Varying Data Sortedness 

## Contributors:
1. Shivangi
2. Vani Singhal

## Problem Statement
Our aim for this project is to compare the performance of different Data Compression Algorithms with changing levels of Data Sortedness and understand the relationship between Data sortedness on the performance of Data Compression Algorithms. As we all know, Data is rarely sorted in real-world scenarios therefore, we also want to compare these Data Compression Algorithms and try to find the one that performs the best with partially sorted Data.

## Project Background
We know that the amount of data being generated every day is increasing exponentially and this poses the question of Data Storage. If we keep storing these quintillion bytes of Data without any kind of compression or encoding, we are going to run out of resources pretty soon. That is why Data Compression is very essential nowadays. These Data Compression Algorithms squeeze large amounts of data, using some kind of encoding, in a format that is compact and can be decompressed when needed. 

Data Compression Algorithms depend on many factors including the degree of sortedness of Data. Data Sortedness is the measure of how arranged the data is in a specific order. Let’s consider an example, say we have time series data, then the order of data could be chronological. 

In this project, we will just focus on Data Sortedness and will try to compare the performance with different degrees/levels of sortedness. If our data is sorted in some order, Data Compression Algorithms can exploit the repetitive patterns and the redundancy to efficiently compress the Data. This was the level of Data sortedness can have an impact on the performance of Data Compression Algorithms.   

However, most research studying sortedness on compression performance assumes that the data is either completely sorted or unsorted. Practically, this rarely happens, data is usually partially sorted, and the degree of sortedness depends on the application and the data source. Hence, we offer to explore the performance of some Data Compression Algorithms with varying degrees of sortedness in this project. Specifically, we aim to examine the following:
Effect of degree of sortedness on the compression ratio and compression/decompression speed for different compression algorithms
Try to find Compression algorithms that perform better than others for partially sorted data. 

## Project objectives
1. Evaluate the performance of data compression algorithms- The primary objective of the project is to evaluate the performance of data compression algorithms on data with varying degrees of sortedness. The project should explore how different algorithms, such as Huffman encoding, arithmetic encoding, run-length encoding, Lempel-Ziv, X-match, Frequent Value Compression, BDI compression and C-Pack, perform when dealing with sorted data.
2. Measure compression ratios :The project should measure the compression ratios achieved by the different algorithms on sorted and unsorted data. This will help in comparing the efficiency of the different algorithms in compressing the data.
3. Evaluate the impact of data type: The project should evaluate the impact of data type on compression ratios. Different data types, such as (numerical/strings/byte encoded), may require different compression techniques, and this should be considered in the project.
4. Assessing the computational efficiency of different algorithms: The project could aim to compare the computational efficiency of different algorithms on datasets with varying degrees of sortedness. This could involve measuring the time taken for each algorithm to compress and decompress the data and comparing these times across algorithms.
5. Compare the results with existing literature: The project should compare the results with existing literature on data compression algorithms. This will help in validating the results and identifying areas that require further research.
