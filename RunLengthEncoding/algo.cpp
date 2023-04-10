#include<iostream>
#include<vector>
using namespace std;
using namespace std::chrono;

// min-max way - every sorted run is replaced by min, max and number of elements in it. For counter= 1, 
//final array has element itself, for counter 2 final array has min and max, for counter >2 final array has min, max and counter
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
    //printing array
    for(int i=0;i<final_arr.size();i++){
       std::cout<<final_arr[i]<<" ";
    }
}

//frequency way - counting number of repeating characters. Final array has element and its frequency. 
//if counter =1 final array has only element.
void run_length_encoding_freq(std::vector<int> arr){
    int counter=1, temp = arr[0];
    std::vector<int> final_arr;
    for(int i=1;i<arr.size();i++){
       //If next element is same as previous 
       if(arr[i]==temp){
        counter++;
        //case when we reach last element of array
        if(i == arr.size()-1){
            final_arr.push_back(arr[i]);
            if(counter!=1)
                final_arr.push_back(counter);
        }
       }
       //If next element is not same as previous
       else{
        final_arr.push_back(arr[i-1]);
        if(counter!=1)
            final_arr.push_back(counter);
        counter=1;
        temp=arr[i];
       }
    }
    //printing array
    for(int i=0;i<final_arr.size();i++){
       std::cout<<final_arr[i]<<" ";
    }
}

int main(){
    std::vector<int> vect;
    vect.push_back(10);
    vect.push_back(10);
    vect.push_back(10);
    vect.push_back(1);
    vect.push_back(1);
    vect.push_back(1);
    std::cout<<" Min- Max way-"<<std::endl;
    run_length_encoding(vect);
    std::cout<<std::endl;
    std::cout<<" frequency way-"<<std::endl;
    run_length_encoding_freq(vect);
}