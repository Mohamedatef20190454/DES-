#include<string>
#include <string>
#include <bitset>
#include <sstream>
#include <bits/stdc++.h>

using namespace std;

static string DecimalToBinary(int dec) {
    if (dec < 1) return "0";

    string binStr = "";

    while (dec > 0)
    {
        binStr = binStr.insert(0, string(1, (char)((dec % 2) + 48)));

        dec /= 2;
    }

    return binStr;
}
string BinaryToASCII(string binaryString) {
    string text = "";
    stringstream sstream(binaryString);
    while (sstream.good())
    {
        bitset<8> bits;
        sstream >> bits;
        text += char(bits.to_ulong());
    }
    return text;
}
int binary_to_decimal(string binaryString) {

    int value = 0;
    int indexCounter = 0;
    for (int i = binaryString.length() - 1; i >= 0; i--) {

        if (binaryString[i] == '1') {
            value += pow(2, indexCounter);
        }
        indexCounter++;
    }
    return value;
}
static string ASCIIToBinary(string str) {
    string bin = "";
    int strLength = str.length();

    for (int i = 0; i < strLength; ++i)
    {
        string cBin = DecimalToBinary(str[i]);
        int cBinLength = cBin.length();

        if (cBinLength < 8) {
            for (size_t i = 0; i < (8 - cBinLength); i++)
                cBin = cBin.insert(0, "0");
        }

        bin += cBin;
    }

    return bin;
}

string permute(string k, int* arr, int n)
{
    string per = "";
    for (int i = 0; i < n; i++)
    {
        per += k[arr[i] - 1];
    }
    return per;
}
string shift_left(string k, int shifts)
{
    string s = "";
    for (int i = 0; i < shifts; i++)
    {
        for (int j = 1; j < 28; j++)
        {
            s += k[j];
        }
        s += k[0];
        k = s;
        s = "";
    }
    return k;
}

string xor_(string a, string b)
{
    string ans = "";
    for (int i = 0; i < a.size(); i++)
    {
        if (a[i] == b[i])
        {
            ans += "0";
        }
        else
        {
            ans += "1";
        }
    }
    return ans;
}

string encryption(string plaintext, string keys[],int h ) {

    int s[8][4][16] = {
{ 14, 4,  13, 1, 2,  15, 11, 8,  3,  10, 6,  12, 5,
  9,  0,  7,  0, 15, 7,  4,  14, 2,  13, 1,  10, 6,
  12, 11, 9,  5, 3,  8,  4,  1,  14, 8,  13, 6,  2,
  11, 15, 12, 9, 7,  3,  10, 5,  0,  15, 12, 8,  2,
  4,  9,  1,  7, 5,  11, 3,  14, 10, 0,  6,  13 },
{ 15, 1,  8,  14, 6,  11, 3, 4,  9,  7,  2,  13, 12,
  0,  5,  10, 3,  13, 4,  7, 15, 2,  8,  14, 12, 0,
  1,  10, 6,  9,  11, 5,  0, 14, 7,  11, 10, 4,  13,
  1,  5,  8,  12, 6,  9,  3, 2,  15, 13, 8,  10, 1,
  3,  15, 4,  2,  11, 6,  7, 12, 0,  5,  14, 9 },

{ 10, 0,  9,  14, 6,  3,  15, 5,  1,  13, 12,
  7,  11, 4,  2,  8,  13, 7,  0,  9,  3,  4,
  6,  10, 2,  8,  5,  14, 12, 11, 15, 1,  13,
  6,  4,  9,  8,  15, 3,  0,  11, 1,  2,  12,
  5,  10, 14, 7,  1,  10, 13, 0,  6,  9,  8,
  7,  4,  15, 14, 3,  11, 5,  2,  12 },
{ 7,  13, 14, 3,  0,  6,  9,  10, 1,  2, 8,  5,  11,
  12, 4,  15, 13, 8,  11, 5,  6,  15, 0, 3,  4,  7,
  2,  12, 1,  10, 14, 9,  10, 6,  9,  0, 12, 11, 7,
  13, 15, 1,  3,  14, 5,  2,  8,  4,  3, 15, 0,  6,
  10, 1,  13, 8,  9,  4,  5,  11, 12, 7, 2,  14 },
{ 2,  12, 4, 1,  7,  10, 11, 6, 8,  5,  3,  15, 13,
  0,  14, 9, 14, 11, 2,  12, 4, 7,  13, 1,  5,  0,
  15, 10, 3, 9,  8,  6,  4,  2, 1,  11, 10, 13, 7,
  8,  15, 9, 12, 5,  6,  3,  0, 14, 11, 8,  12, 7,
  1,  14, 2, 13, 6,  15, 0,  9, 10, 4,  5,  3 },
{ 12, 1,  10, 15, 9,  2,  6,  8,  0,  13, 3, 4, 14,
  7,  5,  11, 10, 15, 4,  2,  7,  12, 9,  5, 6, 1,
  13, 14, 0,  11, 3,  8,  9,  14, 15, 5,  2, 8, 12,
  3,  7,  0,  4,  10, 1,  13, 11, 6,  4,  3, 2, 12,
  9,  5,  15, 10, 11, 14, 1,  7,  6,  0,  8, 13 },
{ 4,  11, 2,  14, 15, 0,  8, 13, 3,  12, 9,  7,  5,
  10, 6,  1,  13, 0,  11, 7, 4,  9,  1,  10, 14, 3,
  5,  12, 2,  15, 8,  6,  1, 4,  11, 13, 12, 3,  7,
  14, 10, 15, 6,  8,  0,  5, 9,  2,  6,  11, 13, 8,
  1,  4,  10, 7,  9,  5,  0, 15, 14, 2,  3,  12 },
{ 13, 2,  8, 4,  6,  15, 11, 1,  10, 9, 3, 14, 5,
  0,  12, 7, 1,  15, 13, 8,  10, 3,  7, 4, 12, 5,
  6,  11, 0, 14, 9,  2,  7,  11, 4,  1, 9, 12, 14,
  2,  0,  6, 10, 13, 15, 3,  5,  8,  2, 1, 14, 7,
  4,  10, 8, 13, 15, 12, 9,  0,  3,  5, 6, 11 }
    };
    if(h==0)
    plaintext = ASCIIToBinary(plaintext);
    //cout << plaintext << endl;
    int IP[64]
        = { 58, 50, 42, 34, 26, 18, 10, 2,  60, 52, 44,
            36, 28, 20, 12, 4,  62, 54, 46, 38, 30, 22,
            14, 6,  64, 56, 48, 40, 32, 24, 16, 8,  57,
            49, 41, 33, 25, 17, 9,  1,  59, 51, 43, 35,
            27, 19, 11, 3,  61, 53, 45, 37, 29, 21, 13,
            5,  63, 55, 47, 39, 31, 23, 15, 7 };

    plaintext = permute(plaintext, IP, 64);

    string tump; "";
    string L0 = plaintext.substr(0, 32);
    string R0 = plaintext.substr(32, 32);
    int exp_per[48]
        = { 32, 1,  2,  3,  4,  5,  4,  5,  6,  7,  8,  9,
            8,  9,  10, 11, 12, 13, 12, 13, 14, 15, 16, 17,
            16, 17, 18, 19, 20, 21, 20, 21, 22, 23, 24, 25,
            24, 25, 26, 27, 28, 29, 28, 29, 30, 31, 32, 1 };
    string tumpL;
    string tumpR;
    string result[8];
    int  col[8];
    int  row[8];
    for (int i = 0; i < 16; i++)
    {
        string expaned_right =xor_( permute(R0, exp_per , 48), keys[i] ) ;

        result[0]= expaned_right.substr(0, 6);
        result[1]= expaned_right.substr(6, 6);
        result[2]= expaned_right.substr(12, 6);
        result[3]= expaned_right.substr(18, 6);
        result[4]= expaned_right.substr(24, 6);
        result[5]= expaned_right.substr(30, 6);
        result[6]= expaned_right.substr(36, 6);
        result[7]= expaned_right.substr(42, 6);

        for (int j = 0; j < 8; j++)
        {
            col[j] = binary_to_decimal(result[j].substr(1, 4));
            row[j] = binary_to_decimal(result[j].substr(0,1) + result[j][5]);

        }
        string tump;
        string fout = "";
        for (int j = 0; j < 8; j++)
        {
            tump = DecimalToBinary( s[j][row[j]][col[j]]);

            while (tump.length() < 4 )
            {
                tump =  "0" + tump ;
            }
            fout    += tump;

        }
        int per[]
            = { 16, 7, 20, 21, 29, 12, 28, 17, 1,  15, 23,
                26, 5, 18, 31, 10, 2,  8,  24, 14, 32, 27,
                3,  9, 19, 13, 30, 6,  22, 11, 4,  25 };

       // cout << R0 << endl << L0 << endl;

        fout =  permute(fout, per, 32);
        tumpR = R0;
        tumpL = L0;
      //  if (h == 1 && i == 16)
       //     break;
        L0 = tumpR;
        R0 = xor_( tumpL , fout ) ;
     //   cout << R0 << endl << L0 << endl ;

    }
    int FP[]
        = { 40, 8,  48, 16, 56, 24, 64, 32, 39, 7,  47,
            15, 55, 23, 63, 31, 38, 6,  46, 14, 54, 22,
            62, 30, 37, 5,  45, 13, 53, 21, 61, 29, 36,
            4,  44, 12, 52, 20, 60, 28, 35, 3,  43, 11,
            51, 19, 59, 27, 34, 2,  42, 10, 50, 18, 58,
            26, 33, 1,  41, 9,  49, 17, 57, 25 };

    return permute(R0 + L0, FP , 64);


}
int main()
{
    int choice, shiftvalue;
    string key, plaintext, ciphertext;
    string keys[17];


        cout << "Enter the Plain text:" << endl;
        cin >> plaintext;

        cout << "Enter the key:" << endl;
        cin >> key;
        while (true)
        {
             string new_p = "";
        int sub=0 ;//number of padding
        if(plaintext.size() %8 == 0 )
        {
            new_p = plaintext;
            //cout<<new_p<<endl;
        }
        else if(plaintext.size() < 8 )
        {
            sub = 8 - plaintext.size();
            for(int j = 0 ; j<sub ; j++)
            {
                new_p += "#";
            }
            new_p = new_p + plaintext;
            //cout<new_p<<endl;
        }
        else if(plaintext.size() > 8)

        {


            if (plaintext.size() % 8 != 0)
            {
                for (int i = 0; i < (8 - plaintext.size() % 8); i++)
                {
                    new_p += "";
                }

                new_p = new_p + plaintext ;


            }


        }
                        //cout<<new_p<<endl;




            if (key.size() == 8)
            {
                key = ASCIIToBinary(key);


                int pc1[56]
                    = { 57, 49, 41, 33, 25, 17, 9,  1,  58, 50, 42, 34,
                        26, 18, 10, 2,  59, 51, 43, 35, 27, 19, 11, 3,
                        60, 52, 44, 36, 63, 55, 47, 39, 31, 23, 15, 7,
                        62, 54, 46, 38, 30, 22, 14, 6,  61, 53, 45, 37,
                        29, 21, 13, 5,  28, 20, 12, 4
                };

                key = permute(key, pc1, 56);
                string c0 = key.substr(0, 28);
                string d0 = key.substr(28, 28);

                int pc2[48] = { 14, 17, 11, 24, 1,  5,  3,  28,
                                15, 6,  21, 10, 23, 19, 12, 4,
                                26, 8,  16, 7,  27, 20, 13, 2,
                                41, 52, 31, 37, 47, 55, 30, 40,
                                51, 45, 33, 48, 44, 49, 39, 56,
                                34, 53, 46, 42, 50, 36, 29, 32
                };

                for (int i = 0; i <= 16; i++)
                {

                    if (i == 0 || i == 1 || i == 8 || i == 15)
                    {
                        shiftvalue = 1;
                    }
                    else
                    {
                        shiftvalue = 2;
                    }
                    c0 = shift_left(c0, shiftvalue);
                    d0 = shift_left(d0, shiftvalue);
                    string modulkey = c0 + d0;
                    string finalkey = permute(modulkey, pc2, 48);
                    keys[i] = finalkey;


                }




                string  cy = encryption(new_p, keys ,0);
                cout<<"the cipher text is:"<<endl;
                cout<<ASCIIToBinary(cy)<<endl;

               // cout << cy << endl;

                string new2[17];
                int num = 16;
                for (int i = 0; i < 17; i++)
                {
                    new2[i] = keys[num];
                    num--;

                }
                string keys2[16] ;
                for (int i = 0; i < 16; i++)
                {
                    keys2[i] = new2[i + 1];
                }
                cout<<"after decryption:"<<endl;



                cout << BinaryToASCII(encryption(cy, keys2, 1)).substr(sub,plaintext.size());


                break ;
            }
            else
            {
                cout << "The key size must be 8 char please Enter another key " << endl;
                cin >> key;
            }
        }







return 0;
}
