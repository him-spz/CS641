#include<iostream> 
using namespace std;

int* fromSpecial(string message){
    int n = message.length()/2;
    int *arr = new int[n];
    for(int i = 0; i < n; i++){
        int a = message[2*i]-'f';
        int b = message[2*i+1]-'f';
        arr[i] = (a<<4) + b;
    }
    return arr;
}

int main(int argc, char* argv[]){
    string input = string(argv[1]);
    int *block;
    block = fromSpecial(input);

    int n = input.length()/2;
    for(int i = 0; i < n; i++){
        cout << block[i] << " ";
    }
    cout << endl;
    
    return 0;
}
