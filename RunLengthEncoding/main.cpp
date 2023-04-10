#include <fstream>
#include <vector>
#include <iostream>
#include <random>
#include <set>
#include <algorithm>
#include <functional>
#include <chrono>
#include <utility>

// Specify your path of workload file here
std::string kPointQueriesPath = "./point_queries.txt";
using namespace std;

void run_length_encoding(std::vector<int> arr){
    int min=arr[0],max,counter=1;
    std::vector<int> final_arr;
    for(int i=1;i<arr.size();i++){
        // not an increasing subsequence 
        if(arr[i]<min ){
            if(counter == 1){
                final_arr.push_back(min);
            }
            else if(counter==2){
                max = arr[i-1];
                final_arr.push_back(min);
                final_arr.push_back(max);
                min = arr[i];
                counter = 1;
            }
            else{
                max = arr[i-1];
                final_arr.push_back(min);
                final_arr.push_back(max);
                final_arr.push_back(counter);
                min = arr[i];
                counter = 1;
            }
        }
        //increasing subsequence
        else if(arr[i]>=min){
            counter++;
            //case when we reach last element of array
            if(i==arr.size()-1){
                if(counter == 1){
                    final_arr.push_back(min);
                }
                else if(counter==2){
                    max = arr[i];
                    final_arr.push_back(min);
                    final_arr.push_back(max);
                    min = arr[i];
                    counter = 1;
                }
                else{
                    max = arr[i];
                    final_arr.push_back(min);
                    final_arr.push_back(max);
                    final_arr.push_back(counter);
                    min = arr[i];
                    counter = 1;
                }
            }
        }
    }
    
}

vector<int> runLengthEncode_freq(vector<int> input) {
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

string runLengthEncode_string(string input) {
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


std::vector<int> generatePointQueries(std::vector<int> data, int n)
{
  std::vector<int> queries(data.begin(), data.end());

  // add a few elements out of range
  int non_existing_counter = (data.size() * 0.1);
  std::uniform_int_distribution<int> dist(n, (int)(1.8 * n));
  // Initialize the random_device
  std::random_device rd;
  // Seed the engine
  std::mt19937_64 generator(rd());
  std::set<int> non_existing;
  while (non_existing.size() != non_existing_counter)
  {
    non_existing.insert(dist(generator));
  }

  queries.insert(queries.end(), non_existing.begin(), non_existing.end());

  // shuffle indexes
  std::random_shuffle(queries.begin(), queries.end());

  return queries;
}



int main(int argc, char **argv)
{ 
    std::string input_file = argv[1];
    std::ifstream ifs;
    std::vector<int> data;

    ifs.open(input_file, std::ios::binary);
    ifs.seekg(0, std::ios::end);
    size_t filesize = ifs.tellg();
    ifs.seekg(0, std::ios::beg);

    data.resize(filesize / sizeof(int));
    ifs.read((char *)data.data(), filesize);
    std::vector<int> queries = generatePointQueries(data, data.size());


  //2. ----------------------------- int queries -----------------------------
    //std::vector<int> queries;
    //loadPointQueries(kPointQueriesPath, queries); 

    /*auto start_pq_f = std::chrono::high_resolution_clock::now();
    runLengthEncode_freq(queries);
    auto stop_pq_f = std::chrono::high_resolution_clock::now();
    auto duration_pq_f = std::chrono::duration_cast<std::chrono::microseconds>(stop_pq_f - start_pq_f);
    unsigned long long point_query_time_f = duration_pq_f.count();
    std::cout << "Time taken to perform runLengthEncode = " << point_query_time_f << " microseconds" << endl;


    auto start_pq = std::chrono::high_resolution_clock::now();
    run_length_encoding(queries);
    auto stop_pq = std::chrono::high_resolution_clock::now();
    auto duration_pq = std::chrono::duration_cast<std::chrono::microseconds>(stop_pq - start_pq);
    unsigned long long point_query_time = duration_pq.count();
    std::cout << "Time taken to perform runLengthEncode -min max = " << point_query_time << " microseconds" << endl;


    //2. ----------------------------- string queries -----------------------------
    char c;
    int r;
    string queries_string;
    srand (time(NULL));    // initialize the random number generator
    for (int i=0; i<1000000; i++)
    {    r = rand() % 26;   // generate a random number
          c = 'a' + r;            // Convert to a character from a-z
          queries_string+=c;
    }
    auto start_pq_s = std::chrono::high_resolution_clock::now();
    runLengthEncode_string(queries_string);
    auto stop_pq_s = std::chrono::high_resolution_clock::now();
    auto duration_pq_s = std::chrono::duration_cast<std::chrono::microseconds>(stop_pq_s - start_pq_s);
    unsigned long long point_query_time_s = duration_pq_s.count();
    std::cout << "Time taken to perform runLengthEncode_string = " << point_query_time_s << " microseconds" << endl;*/

    // ----------------------------- sorted string queries -----------------------------

    char c;
    int r;
    string queries_string;
    srand (time(NULL));    // initialize the random number generator
    for (int i=0; i<1000000; i++)
    {    r = rand() % 26;   // generate a random number
          c = 'a' + r;            // Convert to a character from a-z
          queries_string+=c;
    }
    std::sort(queries_string.begin(), queries_string.end());
    auto start_pq_s = std::chrono::high_resolution_clock::now();
    runLengthEncode_string(queries_string);
    auto stop_pq_s = std::chrono::high_resolution_clock::now();
    auto duration_pq_s = std::chrono::duration_cast<std::chrono::microseconds>(stop_pq_s - start_pq_s);
    unsigned long long point_query_time_s = duration_pq_s.count();
    std::cout << "Time taken to perform runLengthEncode_string_sorted = " << point_query_time_s << " microseconds" << endl;
    return 0;
}
