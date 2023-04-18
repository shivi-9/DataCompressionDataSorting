#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <chrono>

// Compress the data using Snappy
void compressData(const std::string& input, std::string& compressed) {
    // Divide the data into small blocks
    const int block_size = 32768;
    const int num_blocks = (input.length() + block_size - 1) / block_size;
    const int last_block_size = input.length() - (num_blocks - 1) * block_size;

    // Create a buffer for each block
    std::vector<char> compressed_data(num_blocks * block_size);
    std::vector<int32_t> uncompressed_sizes(num_blocks);

    // Compress each block separately
    for (int i = 0; i < num_blocks; ++i) {
        const int32_t block_start = i * block_size;
        const int32_t block_size = (i == num_blocks - 1) ? last_block_size : block_size;
        const char* block_data = input.c_str() + block_start;

        // Identify repeated patterns and create a dictionary of those patterns
        std::vector<int32_t> offsets;
        std::vector<int32_t> sizes;
        std::vector<char> dictionary;
        dictionary.reserve(block_size);

        for (int j = 0; j < block_size; ) {
            const int32_t max_size = std::min(block_size - j, block_size / 6 + 1);
            const int32_t offset_limit = std::max(1, j - 4096);
            int32_t best_size = 0;
            int32_t best_offset = 0;

            // Find the best match in the dictionary
            for (int32_t offset = j - 1; offset >= offset_limit; --offset) {
                int32_t size = 0;
                while (size < max_size && block_data[j + size] == block_data[offset + size]) {
                    ++size;
                }
                if (size > best_size || (size == best_size && offset < best_offset)) {
                    best_size = size;
                    best_offset = offset;
                }
            }

            // Add the best match to the dictionary
            if (best_size > 2 || (best_size == 2 && j - best_offset == 1)) {
                offsets.push_back(best_offset);
                sizes.push_back(best_size);
                j += best_size;
            } else {
                dictionary.push_back(block_data[j++]);
            }
        }

        // Encode the data using the dictionary
        std::vector<char> encoded_data;
        encoded_data.reserve(block_size);

        for (int j = 0; j < block_size; ) {
            bool is_literal = true;
            for (int k = 0; k < offsets.size(); ++k) {
                if (offsets[k] == j) {
                    encoded_data.push_back(0x80 | (sizes[k] - 1) << 2);
                    encoded_data.push_back((j - offsets[k] - 1) & 0xFF);
                    encoded_data.push_back((j - offsets[k] - 1) >> 8);
                    is_literal = false;
                    j += sizes[k];
                    break;
                }
            }
            if (is_literal) {
                encoded_data.push_back(block_data[j++]);
            }
        }

        // Store the compressed block in the output buffer
        const int32_t compressed_size = encoded_data.size() + dictionary.size() + 4;
        char* compressed_block = &compressed_data[i * block_size];
        *(int32_t*)compressed_block = compressed_size;
        compressed_block += 4;
        *(int32_t*)compressed_block = dictionary.size();
        compressed_block += 4;
        std::copy(dictionary.begin(), dictionary.end(), compressed_block);
        std::copy(encoded_data.begin(), encoded_data.end(), compressed_block + dictionary.size());

        // Store the uncompressed size of the block
        uncompressed_sizes[i] = block_size;
    }

    // Combine the compressed blocks into a single output buffer
    const int32_t total_compressed_size = compressed_data.size();
    compressed.resize(total_compressed_size);
    char* output = &compressed[0];
    int32_t offset = 0;

    for (int i = 0; i < num_blocks; ++i) {
        *(int32_t*)output = uncompressed_sizes[i];
        output += 4;
        const char* compressed_block = &compressed_data[i * block_size];
        const int32_t compressed_size = *(int32_t*)compressed_block;
        std::copy(compressed_block, compressed_block + compressed_size, output);
        output += compressed_size;
        offset += compressed_size;
    }
}

// Decompress the data using Snappy
void decompressData(const std::string& compressed, std::string& output) {
    const char* input = compressed.c_str();
    const int32_t input_size = compressed.size();
    int32_t offset = 0;

    while (offset < input_size) {
        // Read the uncompressed size of the block
        const int32_t uncompressed_size = *(int32_t*)(input + offset);
        offset += 4;

        // Read the compressed block
        const int32_t compressed_size = *(int32_t*)(input + offset);
        const char* compressed_block = input + offset + 4;

        // Decompress the block
        const char* compressed_end = compressed_block + compressed_size;
        std::vector<char> dictionary;
        dictionary.reserve(4096);

        while (compressed_block < compressed_end) {
            const char tag = *compressed_block++;
            if ((tag & 0x80) == 0) {
                const int32_t literal_size = tag + 1;
                std::copy(compressed_block, compressed_block + literal_size, std::back_inserter(output));
                compressed_block += literal_size;
            } else {
                const int32_t size = ((tag >> 2) & 0x3F) + 2;
                const int32_t offset = ((tag & 0x3) << 8) | *compressed_block++;
                const char* dictionary_end = dictionary.data() + dictionary.size();

                for (int i = 0; i < size; ++i) {
                    output.push_back(*(dictionary_end - offset + i));
                }
            }

            // Update the dictionary
            dictionary.insert(dictionary.end(), compressed_block, compressed_end);
            compressed_block = compressed_end;
        }

        // Check that the uncompressed size matches the expected size
        if (output.size() != uncompressed_size) {
            std::cerr << "Error: expected uncompressed size of " << uncompressed_size
                      << ", but got " << output.size() << std::endl;
        }

        // Move to the next block
        offset += compressed_size;
    }
}

int main() {
    // Read the input data from file
    std::ifstream infile("data.txt");
   
    if (!infile.is_open()) {
        std::cerr << "Error: failed to open input file" << std::endl;
        return 1;
    }

    std::stringstream buffer;
    buffer << infile.rdbuf();
    std::string input_data = buffer.str();

    // Compress the input data
    std::string compressed_data;
    auto start_compress = std::chrono::high_resolution_clock::now();
    compressData(input_data, compressed_data);
    auto end_compress = std::chrono::high_resolution_clock::now();

    // Decompress the compressed data
    std::string output_data;
    auto start_decompress = std::chrono::high_resolution_clock::now();
    decompressData(compressed_data, output_data);
    auto end_decompress = std::chrono::high_resolution_clock::now();

    // Compute the compression accuracy
    const double accuracy = (double)compressed_data.size() / input_data.size();

    // Print the results
    std::cout << "Compression time: "
              << std::chrono::duration_cast<std::chrono::microseconds>(end_compress - start_compress).count()
              << " microseconds" << std::endl;
    std::cout << "Decompression time: "
              << std::chrono::duration_cast<std::chrono::microseconds>(end_decompress - start_decompress).count()
              << " microseconds" << std::endl;
    std::cout << "Compression accuracy: " << accuracy << std::endl;

    // Check that the decompressed data matches the original input
    if (output_data != input_data) {
        std::cerr << "Error: decompressed data does not match input data" << std::endl;
        return 1;
    }

    return 0;
}
