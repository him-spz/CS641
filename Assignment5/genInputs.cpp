#include<iostream>
#include<fstream>

using namespace std;

string toSpecial(int vector[8]){
    string fin(16,'f'), temp;
    for(int i = 0; i < 8; i++){
        char a, b;
        a = 'f' + (vector[i]>>4);
        b = 'f' + (vector[i]&15);
        fin[2*i] = a;
        fin[2*i+1] = b;
    }
    return fin;
}

int* fromSpecial(string message){
    int *arr = new int[8];
    for(int i = 0; i < 8; i++){
        int a = message[2*i]-'f';
        int b = message[2*i+1]-'f';
        arr[i] = (a<<4) + b;
    }
    return arr;
}

void inputs(int argc, char* argv[]){
    int  *block1, it;// *block2;
    if(argc >= 3){
        it = stoi(string(argv[1]))-1;
        string zeros(16-2*(it),'f');
        block1 = fromSpecial(string(argv[2])+zeros);
        // block2 = fromSpecial(string(argv[3])+zeros);
    }
    else{
        it = 0;
        block1 = new int[8];
        // block2 = new int[8];
        for(int i =0; i < 8; i++){
            block1[i] = 0;
            // block2[i] = 0;
        }
    }

    
    string outname = "./inputs/inputs"+to_string(it+1)+".txt";
    ofstream out(outname);
    for(int i = 0; i < 128; i++){
        string iBlock1;//, iBlock2;
        block1[it] = i;
        // block2[it] = i;
        iBlock1 = toSpecial(block1);
        // iBlock2 = toSpecial(block2);
        // cout << iBlock1 << "\t" << iBlock2 << endl;
        out << iBlock1 << endl; // << iBlock2 << endl;
    }
}

int main(int argc, char* argv[]){
    inputs(argc, argv);

    return 0;
}