#include <iostream>
#include <iomanip>
#include <fstream>
#include "funcs.cpp"

using namespace std;
using BYTE = unsigned char;
using INT = unsigned int;
int main(){
    string num ="\0";
    cout << "Enter ID of characteristic to be used (1/2): ";
    cin >> num;
    if((num.compare("1") != 0) && (num.compare("2") != 0)){
        cout << "Please enter valid ID from 1 and 2." << endl;
        return 0;
    }

    string outA, outB;
    ifstream out("outputs"+num+".txt");
    ofstream text_keys("keys_distribution_"+num+".txt"), key_6i("key_6i"+num+".txt");

    string characteristic;
    if(num.compare("1") == 0)
        characteristic = "4008000004000000";
    else
        characteristic = "0020000800000400";
    int chr[64], cl[32], cr[32];
    hex2bin(characteristic, chr);
    getLR(chr, cl, cr);

    // counter for each S box and each key
    long long int KEY_COUNT[8][64];
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 64; j++){
            KEY_COUNT[i][j] = 0;
        }
    }

    int count = 0;

    int iter = 0;
    while(getline(out, outA)){
        getline(out, outB);
        // get ciphertexts for both inputs
        
        int oA[64], oB[64], oXOR[64], lXOR[32], rXOR[32], lA[32], rA[32], lB[32], rB[32], eA[48], eB[48], eXOR[48];
        
        outA = fromSpHex(outA); outB = fromSpHex(outB);
        hex2bin(outA, oA);      hex2bin(outB, oB);
        
        // inverse final permutation
        invFP(oA);  invFP(oB);
        
        // get left and right halves of the ciphertexts
        getLR(oA, lA, rA);  getLR(oB, lB, rB);
        
        // get XOR value of cihpertexts, along with left and right halves
        XOR(oA, oB, oXOR, 64);
        getLR(oXOR, lXOR, rXOR);

        // print(oA, 64);
        // print(oB, 64);
        // print(oXOR, 64);
        // print(lXOR, 32);
        // print(rXOR, 32);

        // apply expansion to left half of output (right half of input to 5th round)
        E(lA, eA);  E(lB, eB);
        XOR(eA, eB, eXOR, 48);

        // print(lA, 32);
        // print(eA, 48);

        int alpha[8], betaXOR[8], gammaXOR[8];
        separate(eA, &alpha[0], 48, 8);
        // separate(eB, &alpha[1][0], 48, 8);
        separate(eXOR, betaXOR,    48, 8);

        int Sout[32];
        XOR(rXOR, cr, Sout, 32);
        invP(Sout);
        separate(Sout, gammaXOR,    32, 8);
        // for(int i = 0; i < 2; i++){
        //     for(int j = 0; j < 8; j++){
        //         cout << alpha[i][j] << " ";
        //     }
        //     cout << endl;
        // }
        // for(int j = 0; j < 8; j++){
        //     cout << betaXOR[j] << " ";
        // }
        // cout << endl;

        for(int i = 0; i < 8; i++){
            int beta[2], S_b1, S_b2, key;
            for(int b = 0; b < 64; b++){
                beta[0] = b;
                beta[1] = betaXOR[i]^beta[0];
                S_b1 = S[i][S_MAP[beta[0]] - 1];
                S_b2 = S[i][S_MAP[beta[1]] - 1];

                if((S_b1^S_b2) == gammaXOR[i]){
                    key = alpha[i]^beta[0];
                    KEY_COUNT[i][key]++;
                }
            }
        }
        // cout << endl;
        iter++;
        // cout << iter << endl;
    }

    // output distribution of keys for further processing
    for(int i = 0; i < 8; i++){
        text_keys << "S" << i+1 << "\t";
        for(int j = 0; j < 64; j++){
            text_keys << setw(3) << KEY_COUNT[i][j] << "  ";
        }
        text_keys << "\n";
    }

    // get max key
    for(int i = 0; i < 8; i++){
        int mx = INT32_MIN, ind = -1, key_i[6];
        double sum = 0;
        for(int j = 0; j < 64; j++){
            sum += KEY_COUNT[i][j];
            if(KEY_COUNT[i][j] > mx){
                mx = KEY_COUNT[i][j];
                ind = j;
            }
        }
        dec2bin(ind, key_i, 6);
        cout << "S" << i+1 << "\tkey_max = " << ind << " = ";
        print(key_i, 6);
        cout << "freq = " << mx << "\tavg = " << sum/64.0 << endl << endl;

        // key_6i << ind << "\t";
        for(int k = 0; k < 6; k++){
            key_6i << key_i[k];
        }
        key_6i << endl;
    }
    // cout << count;
}