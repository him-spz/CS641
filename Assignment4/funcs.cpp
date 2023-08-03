#include <iostream>
#include <iomanip>
#include <fstream>

using namespace std;
using BYTE = unsigned char;
using INT = unsigned int;

INT S[8][64]=
{
  {14, 4, 13, 1, 2, 15, 11, 8, 3 , 10, 6, 12, 5, 9, 0, 7,
  0, 15, 7, 4, 14, 2, 13, 1, 10, 6, 12, 11, 9, 5, 3, 8,
  4, 1 , 14, 8, 13, 6, 2, 11, 15, 12, 9, 7,3, 10, 5, 0,
  15, 12, 8,2,4, 9, 1,7 , 5, 11, 3, 14, 10, 0, 6, 13},
  
  {15, 1, 8, 14, 6, 11, 3, 4, 9, 7, 2, 13, 12, 0,5, 10,
  3, 13, 4, 7, 15, 2, 8, 14, 12, 0, 1, 10, 6, 9, 11, 5,
  0, 14, 7, 11, 10, 4, 13, 1, 5, 8,12, 6, 9, 3, 2, 15,
  13, 8, 10, 1, 3, 15, 4, 2,11,6, 7, 12, 0,5, 14, 9},
  
  {10, 0, 9,14,6,3,15,5, 1, 13, 12, 7, 11, 4,2,8,
  13, 7, 0, 9, 3, 4, 6, 10, 2, 8, 5, 14, 12, 11, 15, 1,
  13, 6, 4, 9, 8, 15, 3, 0, 11, 1, 2, 12,5, 10, 14, 7,
  1, 10, 13, 0, 6, 9, 8, 7, 4, 15, 14, 3, 11, 5, 2, 12},
  
  {7, 13, 14, 3, 0, 6, 9, 10, 1, 2, 8, 5, 11, 12, 4, 15,
  13, 8, 11, 5, 6, 15, 0, 3, 4, 7, 2, 12, 1, 10, 14, 9,
  10, 6, 9, 0, 12, 11, 7, 13, 15, 1 , 3, 14, 5, 2, 8, 4, 
  3, 15, 0, 6, 10, 1, 13, 8, 9, 4, 5, 11, 12, 7, 2, 14},
  
  
  {2, 12, 4, 1, 7, 10, 11, 6, 8, 5, 3, 15, 13, 0, 14, 9, 
  14, 11,2, 12, 4, 7, 13, 1, 5, 0, 15, 10, 3, 9, 8, 6, 
  4, 2, 1, 11, 10, 13, 7, 8, 15, 9, 12, 5, 6, 3, 0, 14, 
  11, 8, 12, 7, 1, 14, 2, 13, 6, 15, 0, 9, 10, 4, 5, 3}, 
  
  
  
  {12, 1, 10, 15, 9, 2, 6,8, 0, 13, 3, 4, 14, 7, 5, 11, 
  10, 15, 4, 2, 7, 12, 9, 5, 6, 1, 13, 14, 0, 11, 3, 8, 
  9, 14, 15, 5, 2,8, 12, 3, 7, 0, 4, 10, 1, 13, 11, 6, 
  4, 3, 2, 12, 9, 5, 15, 10, 11, 14, 1, 7, 6, 0, 8, 13}, 
  
  {4, 11, 2, 14, 15, 0, 8, 13, 3, 12, 9, 7, 5, 10, 6, 1,
  13, 0, 11, 7, 4, 9, 1, 10, 14, 3, 5, 12, 2, 15, 8, 6,
  1, 4, 11, 13, 12, 3, 7, 14, 10, 15, 6, 8, 0, 5, 9, 2, 
  6, 11, 13, 8, 1, 4, 10, 7, 9, 5, 0, 15, 14, 2, 3, 12},
  
  {13, 2, 8, 4, 6, 15, 11, 1, 10, 9, 3, 14, 5, 0, 12,7, 
  1, 15, 13, 8, 10, 3, 7, 4, 12, 5, 6, 11, 0, 14, 9, 2, 
  7, 11, 4, 1, 9, 12, 14, 2, 0, 6, 10, 13, 15, 3, 5, 8, 
  2, 1, 14, 7, 4, 10, 8, 13, 15, 12, 9, 0, 3, 5, 6, 11}};

INT S_MAP[64] = {
    1, 17, 2, 18, 3, 19, 4, 20, 5, 21, 6, 22, 7, 23, 8, 24,
    9, 25, 10, 26, 11, 27, 12, 28, 13, 29, 14, 30, 15, 31, 16, 32,
    33, 49, 34, 50, 35, 51, 36, 52, 37, 53, 38, 54, 39, 55, 40, 56,
    41, 57, 42, 58, 43, 59, 44, 60, 45, 61, 46, 62, 47, 63, 48, 64
};


/* INITIAL PERMUTATION (IP) */

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

/* E BIT_SELECTION TABLE */

INT E_[] = {
  32, 1, 2, 3, 4, 5,
  4, 5,6, 7, 8, 9,
  8, 9, 10, 11, 12, 13,
  12, 13, 14, 15, 16, 17, 
  16, 17, 18, 19, 20, 21, 
  20, 21, 22, 23, 24, 25, 
  24, 25, 26, 27, 28, 29,
  28, 29, 30, 31, 32, 1
};


/* PERMUTATION FUNCTION P */
INT P_[] = {
  16, 7, 20, 21, 
  29, 12, 28, 17,
  1, 15, 23, 26,
  5, 18, 31,10,
  2, 8, 24, 14,
  32, 27, 3, 9,
  19, 13, 30, 6,
  22, 11, 4, 25
};


/* Inverse of P */
INT INV_P_[] = {
	9, 17, 23, 31,
	13, 28, 2, 18,
	24, 16, 30, 6,
	26, 20, 10, 1,
	8, 14, 25, 3,
	4, 29, 11, 19,
	32, 12, 22, 7,
	5, 27, 15, 21
};

/*TYPE CONVERSIONS*/

// converts hexadecimal to binary
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

// converts binary to hexadecimal
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

// converts standard hexadecimal to the one used in assignment
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

// converts assingment hexadecimal to standard hexadecimal
string fromSpHex(const string SpHex){
    string hex(16, '-');
    char temp;
    for(int i = 0; i < SpHex.length(); i++){
        temp = SpHex[i] - 'f';
        if(temp <= 9 && temp >= 0)
            hex[i] = temp + '0';
        else if(temp <= 15 && temp >= 10)
            hex[i] = temp + 'A' - 10;
    }
    return hex;
}

// converts decimal to binary
void dec2bin(long long int x, int bin[], int size){
    for(int i = 0; i < size; i++){
        bin[i] = 0;
    }
    for(int i = 0; i < size && x >= 0; i++){
        bin[size - i - 1] = x%2;
        x /= 2;
    }
}

// converts binary to decimal
long long int bin2dec(int bin[], int size){
    long long int x = 0, pow2 = 1;
    for(int i = 0; i < size; i++){
        x += bin[size - i - 1] * pow2;
        pow2 *= 2;
    }
    return x;
}

/*PERMUTATION OPERATIONS*/

// initial permutation
void IP(int bin[64]){
    int temp[64];
    for(int i = 0; i < 64; i++){
        temp[i] = bin[i];
    }
    for(int i = 0; i < 64; i++){
        bin[i] = temp[IP_[i]-1];
    }
}

// inverse of initial permutation
void invIP(int bin[64]){
    int temp[64];
    for(int i = 0; i < 64; i++){
        temp[i] = bin[i];
    }
    for(int i = 0; i < 64; i++){
        bin[IP_[i]-1] = temp[i];
    }
}

// final permutation
void FP(int bin[64]){
    int temp[64];
    for(int i = 0; i < 64; i++){
        temp[i] = bin[i];
    }
    for(int i = 0; i < 64; i++){
        bin[i] = temp[RFP_[i]-1];
    }
}

// inverse of final permutation
void invFP(int bin[64]){
    int temp[64];
    for(int i = 0; i < 64; i++){
        temp[i] = bin[i];
    }
    for(int i = 0; i < 64; i++){
        bin[RFP_[i]-1] = temp[i];
    }
}

// gets left and right half of text
void getLR(int bin[64], int L[32], int R[32]){
    for(int i = 0; i < 64; i++){
        if(i >= 32)
            R[i-32] = bin[i];
        else
            L[i] = bin[i];
    }
}

// expansion
void E(int inp[32], int inpE[48]){
    for(int i = 0; i < 48; i ++){
        inpE[i] = inp[E_[i] - 1];
    }
}

// permutation
void P(int bin[32]){
    int temp[64];
    for(int i = 0; i < 32; i++){
        temp[i] = bin[i];
    }
    for(int i = 0; i < 32; i++){
        bin[i] = temp[P_[i]-1];
    }
}

// inverse of permutation
void invP(int bin[32]){
    int temp[64];
    for(int i = 0; i < 32; i++){
        temp[i] = bin[i];
    }
    for(int i = 0; i < 32; i++){
        bin[i] = temp[INV_P_[i]-1];
    }
}

/*UTILITY OPERATIONS*/

// Saves A xor B in result (all in binary)
void XOR(const int A[], const int B[], int result[], int size){
    for(int i = 0; i < size; i++){
        result[i] = (A[i]^B[i]);
    }
}

// prints binary form
void print(const int bin[], int size){
    for(int i = 0; i < size; i++){
        cout << bin[i];
    }
    cout << endl;
}

// separate parts of input based on which S-box they go to
void separate(int inp[], int sep[], int size_i, int size_s){
    int size = size_i/size_s, sum = 0, pow2 = 1;
    for(int i = 0; i < size_s; i++){
        sum = 0;    pow2 = 1;
        for(int j = 0; j < size; j++){
            sum += inp[size*(i+1) - j - 1]*pow2;
            pow2 *= 2;
        }
        sep[i] = sum;
    }
} 