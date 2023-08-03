#include <iostream>
#include <fstream>

using namespace std;
using INT = unsigned int;

INT IP_[] = {
  58,50,42, 34,26,18,10,2,
  60,52,44,36,28,20,12,4,
  62,54, 46, 38, 30, 22, 14,6,
  64, 56, 48, 40,32,24, 16, 8,
  57, 49, 41, 33,25,17, 9,1,
  59, 51,43,35,27,19,11,3,
  61,53,45,37,29,21,13, 5,
  63,55, 47,39,31,23,15,7
};

/* REVERSE PERMUTATION (RFP) */

INT RFP_[] = {
  8,40,16,48,24,56,32,64,
  7, 39,15,47,23,55,31,63,
  6,38,14,46,22,54,30,62,
  5,37,13,45, 21,53,29,61,
  4,36,12,44,20,52,28,60,
  3, 35, 11,43,19,51,27,59,
  2, 34, 10, 42,18, 50,26,58,
  1,33,9,41, 17, 49, 25,57
};

void hex2bin(string hex, int bin[64]){
    int dig;
    for(int i = 0; i < hex.length(); i++){
        dig = 0;
        if(hex[i] <= '9' && hex[i] >= '0')
            dig = hex[i] - '0';
        else if(hex[i] <= 'F' && hex[i] >= 'A')
            dig = hex[i] - 'A' + 10;
        
        bin[4*i+3] = dig%2;
        bin[4*i+2] = (dig/2)%2;
        bin[4*i+1] = (dig/4)%2;
        bin[4*i+0] = (dig/8)%2;
    }
}

void bin2hex(int bin[64], string &hex){
    hex.resize(16);
    int dig = 0;
    for(int i = 0; i < 16; i++){
        dig = 8*bin[4*i] + 4*bin[4*i+1] + 2*bin[4*i+2] + 1*bin[4*i+3];
        if(dig <= 9 && dig >= 0)
            hex[i] = '0' + dig;
        else if(dig <= 15 && dig >= 10)
            hex[i] = 'A' + dig -10;
    }
}

string toSpHex(const string hex){
    string spHex(16, '-');
    for(int i = 0; i < hex.length(); i++){
        if(hex[i] <= '9' && hex[i] >= '0')
            spHex[i] = hex[i] - '0' + 'f';
        else if(hex[i] <= 'F' && hex[i] >= 'A')
            spHex[i] = hex[i] - 'A' + 'f' + 10;
    }
    return spHex;
}

void dec2bin(long long int x, int bin[64]){
    for(int i = 0; i < 64; i++){
        bin[i] = 0;
    }
    for(int i = 0; i < 64 && x >= 0; i++){
        bin[64 - i - 1] = x%2;
        x /= 2;
    }
}

void IP(int bin[64]){
    int temp[64];
    for(int i = 0; i < 64; i++){
        temp[i] = bin[i];
    }
    for(int i = 0; i < 64; i++){
        bin[i] = temp[IP_[i]-1];
    }
}

void invIP(int bin[64]){
    int temp[64];
    for(int i = 0; i < 64; i++){
        temp[i] = bin[i];
    }
    for(int i = 0; i < 64; i++){
        bin[IP_[i]-1] = temp[i];
    }
}

// Saves A xor B in result (all in binary)
void XOR(const int A[64], const int B[64], int result[64]){
    for(int i = 0; i < 64; i++){
        result[i] = (A[i]+B[i])%2;
    }
}

void print(const int bin[64]){
    for(int i = 0; i < 64; i++){
        cout << bin[i];
    }
    cout << endl;
}

int main(){

    ofstream fi1("inputs1.txt"), fi2("inputs2.txt");
    int char1[64], char2[64], inp[64], inp1[64], inp2[64];

    // Define characteristics and get reverse initial permutation of their values in binary
    string characteristic1 = "4008000004000000", characteristic2 = "0020000800000400", input, input1, input2;
    hex2bin(characteristic1, char1);//    invIP(char1);
    hex2bin(characteristic2, char2);//    invIP(char2);

    // Generate 512 random input string pairs for each characteristic
    for(int i = 0; i < 512; i++){
        // Generate any one input
        dec2bin(i*i*i, inp);

        // Find pair such that xor with above input is characteristic
        XOR(inp, char1, inp1);
        XOR(inp, char2, inp2);

        // apply inverse initial permutation
        invIP(inp); invIP(inp1); invIP(inp2);

        // convert from binary to hexadecimal
        bin2hex(inp, input);
        bin2hex(inp1, input1);
        bin2hex(inp2, input2);

        // int Xor[64];
        // string hexor;
        // IP(inp);    IP(inp1);   IP(inp2);
        // XOR(inp, inp1, Xor);
        // bin2hex(Xor, hexor);
        // cout << hexor << " ";
        // XOR(inp, inp2, Xor);
        // bin2hex(Xor, hexor);
        // cout << hexor << endl;

        // convert to special hexadecimal as used in assignment (from 'f' to 'u') and write pair to files
        fi1 << toSpHex(input) << endl;
        fi1 << toSpHex(input1) << endl;
        fi2 << toSpHex(input) << endl;
        fi2 << toSpHex(input2) << endl;
    }
    fi1.close();
    fi2.close();

    return 0;
}