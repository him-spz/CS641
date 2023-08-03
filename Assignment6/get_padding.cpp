#include<bits/stdc++.h>

using namespace std;

int hex2dec(string hex){
    int sum;
    for(int i = 0; i < hex.length(); i++){
        int dig = 0;
        if(hex[i] <= '9' && hex[i] >= '0')
            dig = hex[i] - '0';
        else if(hex[i] <= 'f' && hex[i] >= 'a')
            dig = hex[i] - 'a' + 10;
        sum += dig*pow(16, hex.length()-i-1);
    }
    return sum;
}

int main(){
    string padding = "59 6f 75 20 73 65 65 20 61 20 47 6f 6c 64 2d 42 75 67 20 69 6e 20 6f 6e 65 20 63 6f 72 6e 65 72 2e 20 49 74 20 69 73 20 74 68 65 20 6b 65 79 20 74 6f 20 61 20 74 72 65 61 73 75 72 65 20 66 6f 75 6e 64 20 62 79";

    stringstream buffer(padding);
    string number = "";
    while(getline(buffer, number, ' ')){
        char c = hex2dec(number);
        cout << c;
    }
    cout << endl;
}