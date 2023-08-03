#include <fstream>
#include <iostream>
#include <algorithm>
#include <map>
#include <vector>

using namespace std;

bool cmp(pair<char, int>& a, pair<char, int>& b){ 
    return a.second > b.second; 
} 

vector<pair<char, int>> sort(map<char,int>& M){
    vector<pair<char, int> > A; 
  
    // Copy key-value pair from Map 
    // to vector of pairs 
    for (auto& it : M) { 
        A.push_back(it); 
    } 
  
    // Sort using comparator function 
    sort(A.begin(), A.end(), cmp); 
    return A;
}

int main(){
    map<char, int> freq;
    double num = 0.;
    ifstream fin;
    fin.open("cipher.txt");

    char c;
    while(fin){
        fin >> c;
        c = tolower(c);
        if(!isalpha(c))
            continue;
        if(freq.find(c) == freq.end()){
            freq[c] = 1;
        }
        else{
            freq[c]++;
        }
        // cout << c;
        num++;
    }
    fin.close();

    vector<pair<char, int>> Freq = sort(freq);
    
    ofstream out;
    out.open("freq.txt");
    out << "Total Characters = " << num << endl;
    for(auto item : Freq){
        out << endl << item.first << " " << static_cast<double>(item.second)/num*100.;
    }
    out.close();
    return 0;
}