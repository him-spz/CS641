#include <iostream>
#include <fstream>

using namespace std;

int main(int argc, char* argv[]){
    ofstream out;
    ifstream in;
    in.open("./outputs/raw/rawoutputs" + string(argv[1]) + ".txt");
    out.open("./outputs/outputs" + string(argv[1]) + ".txt");

    string temp;
    while(getline(in, temp)){
        if(temp.length() == 17){
            out << temp << "\t";
        }
        else if(temp.length() == 19){
            out << temp.substr(2,19) << endl;
        }
    }
    in.close();
    out.close();
    return 0;
}