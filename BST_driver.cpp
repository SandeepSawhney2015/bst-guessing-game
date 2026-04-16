#include "BST.hpp"
#include <iostream>
#include <fstream>
#include <map>

using namespace std;

pair<map<int, double>, int> gather_data(){
    map<int, double> freq;
    ifstream file("data.txt");
    int number, count;
    double total = 0;
    while(file >> number >> count){
        freq[number] = count;
        total += count;
    }
    return {freq, total};
}

int create_root(const map<int, double>& freq, const double& total){
    int number;
    int where_we_at = 0;
    int boundary = total/2;
    for(auto i : freq){
        where_we_at = i.second + where_we_at;
        if(where_we_at >= boundary){
            number = i.first;
            break;
        }
    }
    return number;
}



int main(){
    auto read = gather_data();
    BST<int> tree(create_root(read.first, read.second));
}