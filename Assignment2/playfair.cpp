#include <iostream>
#include <fstream>
#include <unordered_set>
#include <unordered_map>
#include <vector>


using namespace std;

void show_table(vector<vector<char>> &table){
    cout << "Cipher table" << endl;
    for(int i = 0; i < 5; i++){
        for(int j = 0; j < 5; j++){
            cout << "\t" << table[i][j];
        }
        cout << endl;
    }
    return;
}

void genKeyTable(const string &key, vector<vector<char>> &table){
    unordered_set<char> reps;
    int i = 0, j = 0;
    for(int c = 0; c < key.size(); c++){
        // cout << key[c] << endl;
        if(reps.find(key[c]) == reps.end()){
            reps.insert(key[c]);
            table[i][j] = key[c];
            j++;
            j %= 5;
            i += !j;
        }
    }

    char c;
    for(int k = 0; k < 26 && i < 5; k++){
        c = 'A' + k;
        if(c == 'J')
            continue;
        if(reps.find(c) == reps.end()){
            reps.insert(c);
            table[i][j] = c;
            j++;
            j %= 5;
            i += !j;
        }
    }
    return;
}

vector<pair<int,int>> search(const vector<vector<char>> &table, char a, char b){ 
	vector<pair<int,int>> ind(2,pair<int,int>(-1,-1));

    if (a == 'J') 
		a = 'I'; 
	else if (b == 'J') 
		b = 'I'; 

	for (int i = 0; i < 5; i++) { 
		for (int j = 0; j < 5; j++) { 
			if (table[i][j] == a) { 
				ind[0] = make_pair(i,j); 
			} 
			else if (table[i][j] == b) { 
				ind[1] = make_pair(i,j); 
			} 
		} 
	}
    return ind;
}

void preprocess(string &txt){
    for(int i = 0; i < txt.size(); i++){
        if(!isalpha(txt[i])){
            txt.erase(i,1);
            i--;
        }
        txt[i] = toupper(txt[i]);
    }
}

string decrypt(string &txt, const vector<vector<char>> &table){
	vector<pair<int,int>> ind(2,pair<int,int>(-1,-1));
    string msg;
    char a, b;

    preprocess(txt);

    for(int i = 0; i < txt.size(); i += 2){
        a = txt[i];
        b = txt[i+1];
        if(a == b){
            b = txt[i+2];
            i++;
        }
        if(!isalpha(b)){
            continue;
        }
        ind = search(table, a, b);
        int i1 = ind[0].first, j1 = ind[0].second,
            i2 = ind[1].first, j2 = ind[1].second;

        // printf("%c%c\t(%d, %d)\t(%d, %d)", a, b, i1, j1, i2, j2);

        if(i1 == i2){
            // printf("\t\t(%d, %d)\t(%d, %d)", i1, (j1-1)%5 + (((j1-1)%5) < 0)*5, i2, (j2-1)%5 + (((j2-1)%5) < 0)*5);
            a = table[i1][(j1-1)%5 + (((j1-1)%5) < 0)*5];
            b = table[i2][(j2-1)%5 + (((j2-1)%5) < 0)*5];
        }
        else if(j1 == j2){
            // printf("\t\t(%d, %d)\t(%d, %d)", (i1-1)%5 + (((i1-1)%5) < 0)*5, j1, (i2-1)%5 + (((i2-1)%5) < 0)*5, j2);
            a = table[(i1-1)%5 + (((i1-1)%5) < 0)*5][j1];
            b = table[(i2-1)%5 + (((i2-1)%5) < 0)*5][j2];
        }
        else{
            // printf("\t\t(%d, %d)\t(%d, %d)", i1, j2, i2, j1);
            a = table[i1][j2];
            b = table[i2][j1];
        }
        // printf("\t\t%c%c\n", a, b);
        msg += a;
        msg += b;
    }
    return msg;
}

int main(){
    vector<vector<char>>  table(5, vector<char>(5, ' '));
    string msg, fin;
    unordered_map<int, char> sym;
    
    string key= "SECURITY";
    
    ifstream cipher("ciphertext.txt");
    char c;
    int i = 0;
    cipher >> noskipws;
    while(cipher){
        cipher >> c;
        if(isalpha(c)){
            msg += toupper(c);
        }
        else{
            sym[i] = c;
        }
        i++;
    }
    cipher.close();

    genKeyTable(key, table);
    // show_table(table);
    fin = decrypt(msg, table);

    ofstream fout("message.txt");

    i = 0;
    for(int j = 0; j < fin.size();){
        if(sym.find(i) != sym.end()){
            fout << sym[i];
            i++;
        }
        else{
            fout << fin[j];
            i++;
            j++;
        }
    }
    fout.close();

    return 0;
}