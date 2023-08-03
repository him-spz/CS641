#include<iostream>
#include<fstream>
#include<string>
#include<math.h>
#include<vector>
#include "funcs.cpp"

using namespace std;


  /* PERMUTED CHOICE  PC1 */
INT PC1[] = {
  57, 49, 41, 33, 25, 17, 9,
  1, 58, 50, 42, 34, 26, 18,
  10,  2, 59, 51, 43, 35, 27,
  19, 11,  3, 60, 52, 44, 36,
  63, 55, 47, 39, 31, 23, 15, 
  7, 62, 54, 46, 38, 30, 22, 
  14,  6, 61, 53, 45, 37, 29, 
  21, 13,  5, 28, 20, 12,  4
};

unsigned short shifts[] = {
1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1
};

/* PERMUTED CHOICE 2 (PC2) */
INT PC2[] = {
  14, 17, 11, 24,  1, 5, 
  3, 28 ,15,  6, 21, 10, 
  23, 19, 12,  4, 26, 8, 
  16,  7, 27, 20, 13, 2, 
  41, 52, 31, 37, 47, 55, 
  30, 40, 51, 45, 33, 48, 
  44, 49, 39, 56, 34, 53, 
  46, 42, 50, 36, 29, 32
};

/* Key Scedule of 16 48-bit subkey generated from 64-bit key */
BYTE KS[16][48];

void set_the_key(int sw1, BYTE *key, int r)
{
    register INT i, j, k, t1, t2;
    static BYTE CD[56];

    /* permute unpacked key with PC1 to generate C and D*/
    for (i=0; i<56; i++) {
    CD[i] = key[PC1[i] -1];
    }
    
    /* Rotate and permute C and D to generate 16 subkeys */
    for (i = 0; i < r; i++) {
        /* Rotate C and D */
        for (j = 0; j < shifts[i]; j++)
        {
            t1 = CD[0];
            t2 = CD[28];
            for (k = 0; k < 27; k++){
                CD[k] = CD[k+1];
                CD[k+28] = CD[k+29];
            }
            CD[27] = t1;
            CD[55] = t2;
        }
        /* Set the order of subkeys for type of encryption */
        j = sw1 ? r - 1 - i : i;

        /* Permute C and D with PC2 to generate KS[i] */
        for (k = 0; k < 48; k++)
            KS[j][k] = CD[PC2[k] - 1];
    }

    return;
}


/********************************************************************
 *UNPACK8()  Unpack 8 bytes at 8bits/byte into 64 bytes at 1 bit/byte
 ********************************************************************/

void unpack8(BYTE *packed, BYTE *binary)
    /* BYTE *packed;
     BYTE *binary;*/
{
  register INT i, j, k;

  for (i=0; i<8; i++) {
    k = *packed++;
    for (j=0; j<8;j++) *binary++ = (k>>(7-j)) &01 ;
  }
}

/********************************************************************
 *PACK8() Pack 64 bytes at 1 bits/byte into 8 bytes at 8 bit/byte
 ********************************************************************/

void pack8(BYTE *packed,BYTE *binary)
   /*  BYTE *packed;
     BYTE *binary;*/
{
  register INT i, j, k;

  for (i=0; i<8; i++) {
    k = 0;
    for (j=0; j<8;j++) k  = (k<<1)+ *binary++;
    *packed++ = k;
  }
}

/****************************************************************
		       DES
****************************************************************/


void des(BYTE *in,BYTE *out,INT r,char flag)
    /* BYTE *in;              /* packed 64 bit Input block */
    // BYTE *out;             /* packed 64 bit output block */
    // INT r;                                  /* number of rounds */
	// char flag;
{
  	register INT i, j, k, t;
  	static BYTE block[64]; /* unpacked 64-bit input/output block */
  	static BYTE LR[64], f[32], preS[48];

  	/* Unpack the INPUT block */
   	unpack8(in, block);

  	/* Permute unpacked input block with IP to generate L and R */
  	/*
    	printf("\nThe block after the initial permutation IP \n");
  	*/
   	for (j =0; j<64 ; j++)
    {
        LR[j] = block[IP_[j] -1];
        /*printf("%d", LR[j]);*/
    }

    /* Perform r rounds */
    /*
    printf(" In des 3rd round expandes block is \n");
    */

    for (i=0; i<r; i++) {  /**--*/
      		/* expand R to 48 bits with E and XOR  with ith subkey */
	  	for( j=0; j<48; j++) {
	    	preS[j] = LR[E_[j]+31]^KS[i][j];
	    }


	  	/* Map 8 6-bit blocks into 8 4-bit bolcks using S-boxes */
	  	for (j=0; j<8; j++) {
	    	/* Compute index t into jth s box */

	    	k= 6*j;
	    	t= preS[k];
	    	t = (t<<1) | preS[k+5];
	    	t = (t<<1)| preS[k+1];
	    	t = (t<<1)| preS[k+2];
	    	t = (t<<1)| preS[k+3];
	    	t = (t<<1)| preS[k+4];
	    	/* fetch t th entry fron jth sbox */
	    		t = S[j][t];
	    	/* generate 4-bit block from s-box entry */
	    	k= 4*j;
	    	f[k] = (t>>3)&1;
	    	f[k+1] = (t >> 2) & 1;
	    	f[k+2] = (t >> 1) & 1;
	    	f[k+3] = t &1;

	  	}


	 	for (j=0; j <32; j++) {
	    	/* Copy R */
	    	t = LR[j+32];
	    	/* Permute Permute f w/ P and XOR w/ L to generate new R*/
			if (flag == 'N')
	    		LR[j+32] = LR[j]^f[P_[j] -1];
			else
	    		LR[j+32] = LR[j]^f[INV_P_[j] -1];
	    	/*LR[j+32] = LR[j]^f[j];*/
	    	/* copy original R to new L */
	    	LR[j] =t;
	  	}
	}


    /*
	printf( "\n\n I am in Des , block before final RFP permute\n");
	for(i=0; i<64; i++)
	printf( "%d", LR[i]);
    */
    /* Permute L and R with reverse IP-1 to generate output block*/
    for (j=0; j < 64; j++) block [j] = LR[RFP_[j]-1];
        /* Pack data into 8 bits per byte */


    pack8(out, block);

	  out[8] = '\0';

}
/******************************************************
                       DES ENDS
*******************************************************/



int main()
{
	// This is how indices of Key appear in K6
	int k6[] = {3,44,27,17,42,10,26,50,60,2,41,35,25,57,19,18,1,51,52,59,58,49,11,34,13,23,30,45,63,62,38,21,31,12,14,55,20,47,29,54,6,15,4,5,39,53,46,22};


	// Characteristic 1 gives 2,5,6,7,8 parts of K6
	// Charactersitic 2 gives 1,2,4,5,6 parts of K6, only 3 is unknown
	string key6 = "";
	ifstream key6_1("key_6i1.txt"), key6_2("key_6i2.txt");
	vector<string> key6_i1(8,""), key6_i2(8,"");
	for(int i = 0; i < 8; i++){
		getline(key6_1, key6_i1[i]);
		getline(key6_2, key6_i2[i]);
	}
	for(int i = 1; i <= 8; i++){
		if((i == 7) || (i == 8))
			key6 += key6_i1[i-1];
		else if(i == 3)
			key6 += "xxxxxx";
		else
			key6 += key6_i2[i-1];
	}

	char key[65];
	for(int i=0 ; i<64 ; i++)
		key[i] = 'x';
	for(int i=0 ; i<48 ; i++) 
		key[k6[i]-1] = key6[i];
	for(int i=0; i<8; i++)
		key[8*i+7] = '0';
	key[64] = '\0';
	
	// key[64] has currently 14 x's (unknown bits), EmptyBits[] stores those 14 indices
	int EmptyBits[14];
	int count = 0;
	for(int i=0; i<64; i++)
	{
		if(key[i]=='x')
		{
			EmptyBits[count]=i;
			count++;
		}
	}
	

	//****************** STUFF NEEDED FOR BRUTE FORCE ********************//
	BYTE key_i[64];

	// Setting the plaintext and ciphertext pair
	string input = "ffffffffffffffff",	output = "hiunujmihmsmknlh";
	input = fromSpHex(input);		 	output = fromSpHex(output);
	int in_b[64], out_b[64], pow2, in_d, out_d;
	BYTE plaintext[9], ciphertext[9], cipherout[9];
	hex2bin(input, in_b);				hex2bin(output, out_b);
	for(int i=0; i<8; i++)
	{	
		pow2=1;
		in_d=0;		out_d=0;
		for(int j=0; j<8; j++)
		{
			in_d += in_b[8*(i+1)-j-1]*pow2;
			out_d += out_b[8*(i+1)-j-1]*pow2;
			pow2 *= 2;
		}
		plaintext[i] = in_d;
		ciphertext[i] = out_d;
		// cout << in_d << "   " << out_d << endl;
	}
	plaintext[8]='\0';
	ciphertext[8]='\0';

	BYTE DES_KEY[64];


	//*********************** KEY BRUTE FORCE LOOP **********************//
	for(int k=0; k<powf(2,14); k++)
	{
		pow2 = 1;
		for( count=13; count>=0; count--)
		{
			key[EmptyBits[count]] = (k/pow2)%2 + 48 ;
			pow2 *= 2;
		}
		// key_out << key << endl;

		// convert from char to int
		for(int i=0; i<64; i++)
		{	
			key_i[i] = key[i] - 48;
			// key_out << key_i[i];
		}
		// key_out << endl;

		set_the_key(0, key_i, 6);
		des(plaintext, cipherout, 6, 'N');

		int yes = 1;
		for(int i=0; i<8; i++)
		{
			if(int(cipherout[i]) != int(ciphertext[i]))
				yes = 0;
		}

		if(yes)
		{
			cout << "DES KEY IS: ";
			for(int i=0; i<64; i++)
			{
				DES_KEY[i] = key_i[i];
				cout << int(DES_KEY[i]);
			}
			cout << endl;
		}
	}


	//**************** DECRYPTING PASSWORD USING DES KEY ****************//


	// Setting the plaintext (encrypted Password)
	string input1 = "kqguqgjlsfifrfto",	input2 = "igtpghpqoflokkph";
	input1 = fromSpHex(input1);		 	input2 = fromSpHex(input2);
	int in1_b[64], in2_b[64], in1_d, in2_d;
	BYTE plaintext1[9], plaintext2[9], cipherout1[9], cipherout2[9];
	hex2bin(input1, in1_b);				hex2bin(input2, in2_b);
	for(int i=0; i<8; i++)
	{	
		pow2=1;
		in1_d=0;		in2_d=0;
		for(int j=0; j<8; j++)
		{
			in1_d += in1_b[8*(i+1)-j-1]*pow2;
			in2_d += in2_b[8*(i+1)-j-1]*pow2;
			pow2 *= 2;
		}
		plaintext1[i] = in1_d;
		plaintext2[i] = in2_d;
		// cout << in_d << "   " << out_d << endl;
	}
	plaintext1[8]='\0';
	plaintext1[8]='\0';

	set_the_key(1, DES_KEY, 6);

	cout << "The Decrypted Password is: ";
	des(plaintext1, cipherout1, 6, 'N');
	for(int i=0; i<8; i++)
		cout << (cipherout1[i]);

	des(plaintext2, cipherout2, 6, 'N');
	for(int i=0; i<8; i++)
		cout << (cipherout2[i]);

	cout << endl;
}