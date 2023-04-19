#include<iostream>
#include<vector>
using namespace std;
using namespace std::chrono;


std::vector<int> delta_decoding(std::vector<int> arr){
    
    int temp1 = arr[0];
    int n = arr.size();
    for(int i=1;i<n;i++){ 
       arr[i] += temp1;
       temp1 = arr[i];
    }
   return arr;
}


std::vector<int> delta_encoding(std::vector<int> arr){
    int temp1 = arr[0];
    int n = arr.size();
    for(int i=1;i<n;i++){
       int temp2 = arr[i]; 
       arr[i] -= temp1;
       temp1 = temp2;
    }
    return arr;
}

int main(){
    std::vector<int> vect;
    vect.push_back(4);
    vect.push_back(20);
    vect.push_back(23);
    vect.push_back(40);
    vect.push_back(66);
    vect.push_back(65);

    std::cout<<" delta encoding way-"<<std::endl;
    delta_encoding(vect);

    std::vector<int> vect1;
    vect1.push_back(4);
    vect1.push_back(16);
    vect1.push_back(3);
    vect1.push_back(17);
    vect1.push_back(16);
    vect1.push_back(-1);


    std::cout<<" delta decoding way-"<<std::endl;
    delta_decoding(vect1);
}