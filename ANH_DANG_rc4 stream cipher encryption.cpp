//============================== Program for RC4 Stream Cipher Encryption ===========
#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>//colors
#include <iomanip>//hex
#include <math.h>

HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
using namespace std;

int bin_arr[10000][8];// array to store binary of input/random
int final_arr[10000][8];// array to store XOR'd binary
int file_size = 0;// file size in B
int input_file_size, random_file_size, n = 0;
int num_blocks = 13;//discarding first 12 blocks, starting at 13
int final_int[10000] = { 0 };
int binary_dec[8] = { 128,64,32,16,8,4,2,1 };

//=================== Geeksforgeeks.com ==============
//==================== String to Binary ===============
void strToBinary(string s)
{
	for (int i = 0; i <= s.length(); i++)
	{
		// convert each char to ASCII value 
		int val = int(s[i]);
		string bin = "";
		// Convert ASCII value to binary 
		while (val > 0)
		{
			(val % 2) ? bin.push_back('1'):
				bin.push_back('0');
			val /= 2;
		}
		reverse(bin.begin(), bin.end());
		
		cout << bin << " ";
		file_size++;
	}
}
void bin_output(string s)
{
	for (int i = 0; i <= s.length(); i++)
	{
		// convert each char to ASCII value 
		int val = int(s[i]);
		string bin = "";
		// Convert ASCII value to binary 
		while (val > 0)
		{
			(val % 2) ? bin.push_back('1') :
				bin.push_back('0');
			val /= 2;
		}
		reverse(bin.begin(), bin.end());
//============= Putting Original Text Binary into Array ==========
		if (n < input_file_size)
		{
			if (bin.length() == 6)
			{
				bin_arr[n][0] = 48;
				bin_arr[n][1] = 48;
				for (int x = 2; x < 8; x++)
				{
					bin_arr[n][x] = bin[x-2];
				}
				for (int x = 0; x < 8; x++)
				{
					cout << char(bin_arr[n][x]);
				}
			}
			if (bin.length() == 7)
			{
				bin_arr[n][0] = 48;
				for (int x = 1; x < 8; x++)
				{
					bin_arr[n][x] = bin[x-1];
				}
				for (int x = 0; x < 8; x++)
				{
					cout << char(bin_arr[n][x]);
				}
			}
			cout << " ";
			n++;
		}
		cout << endl;
//==================== Putting Random Text Binary into Array ===============	
		if (n >= input_file_size)
		{
			if (bin.length() == 6)
			{
				bin_arr[n][0] = 48;
				bin_arr[n][1] = 48;
				for (int x = 2; x < 8; x++)
				{
					bin_arr[n][x] = bin[x - 2];
				}
				for (int x = 0; x < 8; x++)
				{
					cout << char(bin_arr[n][x]);
				}
			}
			if (bin.length() == 7)
			{
				bin_arr[n][0] = 48;
				for (int x = 1; x < 8; x++)
				{
					bin_arr[n][x] = bin[x - 1];
				}
				for (int x = 0; x < 8; x++)
				{
					cout << char(bin_arr[n][x]);

				}
			}
			cout << " ";
			n++;
		}
	}
}
// ============= Key-Scheduling Algorithms & Pseudo-Random Generated Algorithms (Source: Wikipedia) =============
int KSA_PRGA(string key, int plaintext_l)
{
// Permutation of S[]
// ======================= KSA ==================
	int S[256];
	int temp = {};
	int j = 0;
// identity permutation
	for (int i = 0; i < 256; i++)
	{
		S[i] = i;
	}
// initializing permutation mixed with bytes of key
	for (int i = 0; i < 256; i++)
	{
		j = (j + S[i] + key[i % key.length()]) % 256;
		temp = S[i];// Swap S[i] & S[j]
		S[i] = S[j];
		S[j] = temp;
	}

// ========= PRGA =====================
// generate 32 B of Keystream based on permutation
	ofstream output_random;
	output_random.open("output_random.txt");
// discard first 3072 B of pseudo random numbers (12*256 B = 3072 B)
	for (int x = 0; x < num_blocks; x++)// num_blocks initialized to 13
	{
		int K, i = 0;
		while (i < 255)// 1 Block = 256 B
		{
			i = (i + 1) % 256;
			j = (j + S[i]) % 256;
			temp = S[i];//swap S[i] & S[j]
			S[i] = S[j];
			S[j] = temp;
			K = S[(S[i] + S[j])] % 256;// outputting K
			// generating useful random numbers over Blocks #13
			if (x >= 13)
			{
				cout << "(" << K << ")" << " ";
				if (K > 31 && K < 127)
				{
					output_random << char(K);// store in txt file
				}
			}
		}
	}
	return 0;
}
//================ Generate Output File of Random Char ==============
void random_generated()
{
	ifstream infile;
	infile.open("output_random.txt");
	//============= Store Text File in String Array ==========
	string plaintext[100];
	cout << "============== RANDOM INPUT TEXT ====================" << endl;
	int s_length = 0;
	for (int x = 0; x < 100; x++)
	{
		infile >> plaintext[x];
		if (plaintext[x] != "")
		{
			cout << plaintext[x] << " ";
			s_length++;
		}
	};
	cout << "Random Text in Binary" << endl;
	for (int x = 0; x < s_length; x++)
	{
		strToBinary(plaintext[x]);
		cout << "(SPACE) ";
	}
}
int main()
{
	ifstream infile;
	infile.open("rc4Input.txt");
	//============= Store Text File in String Array ==========
	string plaintext[100];
	cout << "============== RC4 INPUT TEXT ====================" << endl;
	int s_length = 0;
	for (int x = 0; x < 100; x++)
	{
		infile >> plaintext[x];
		if (plaintext[x] != "")
		{
			cout << plaintext[x] << " ";
			s_length++;
		}
	}
	cout << endl << "=============== ORIGINAL TEXT IN BINARY ================" << endl;
	for (int x = 0; x < s_length; x++)
	{
		strToBinary(plaintext[x]);
		cout << "(SPACE) ";
	}
	cout << "=================================" << endl;
	string key;
	cout << "Please input key for encryption (5-32 Char): " << endl;
	cin >> key;
	if (key.length() >= 5 && key.length() <= 32)
	{
		strToBinary(key);
		KSA_PRGA(key, s_length);
	}
	else (cout << "Key Length is Invalid.");
	input_file_size = file_size;
	cout << endl << "Input File Size: " << input_file_size << " B" << endl;
	file_size = 0;
	random_generated();
	random_file_size = file_size;
	cout << "Random Generated File Size: " << random_file_size << " B" << endl;
//==================== Increase Number of Blocks to Match Input Text File to Random Generated File =============
	while (random_file_size < input_file_size)
	{
		file_size = 0;
		num_blocks++;
		KSA_PRGA(key, s_length);
		random_generated();
		random_file_size = file_size;
		cout << "Random Generated File Size: " << random_file_size << " B" << endl;
	}

//================= RC4 Input Text -> Binary -> Int Array =======
	cout << "============== ORIGINAL TEXT IN BINARY 8-BITS (1 BLOCK = 1 WORD) ===========" << endl;
	for (int x = 0; x < s_length; x++)
	{
		bin_output(plaintext[x]);
	}
//================ Random Input Text -> Binary -> Int Array ==========
	ifstream random_infile;
	random_infile.open("output_random.txt");
	string random_text[100];

	int random_s_length = 0;
	for (int x = 0; x < 100; x++)
	{
		random_infile >> random_text[x];
		if (random_text[x] != "")
		{
			cout << random_text[x] << " ";
			random_s_length++;
		}
	}
	cout << endl << "=============== RANDOM TEXT IN BINARY ================" << endl;
	for (int x = 0; x < random_s_length; x++)
	{
		strToBinary(random_text[x]);
		cout << "(SPACE) ";
	}
	cout << "============== RANDOM TEXT IN BINARY 8-BITS (1 BLOCK = 1 WORD) ===========" << endl;
	while (n < input_file_size)
	{
		n++;
	}
	for (int x = 0; x < random_s_length; x++)
	{
		bin_output(random_text[x]);
	}

	cout << "=============" << endl;
	int total_size = input_file_size + random_file_size;
	for (int x = 0; x < total_size; x++)
	{
		for (int y = 0; y < 8; y++)
		{
			if (bin_arr[x][y] == 0)
			{
				cout << bin_arr[x][y];
			}
			if (bin_arr[x][y] != 0)
			{
				cout << char(bin_arr[x][y]);
			}
		}
		if (x < input_file_size)
		{
			cout << "(" << x << ")" << endl;
		}
		if (x >= input_file_size)
		{
			cout << "[" << (x - input_file_size) << "]" << endl;
		}
	}
// =================== XOR ON FINAL ARRAY =============
	for (int x = 0; x < total_size; x++)
	{
		for (int y = 0; y < 8; y++)
		{
			if (char(bin_arr[x][y]) == '0' && char(bin_arr[x + input_file_size][y]) == '0')
			{
				final_arr[x][y] = 0;
			}
			if (char(bin_arr[x][y]) == '1' && char(bin_arr[x + input_file_size][y]) == '0')
			{
				final_arr[x][y] = 0;
			}
			if (char(bin_arr[x][y]) == '0' && char(bin_arr[x + input_file_size][y]) == '1')
			{
				final_arr[x][y] = 1;
			}
			if (char(bin_arr[x][y]) == '1' && char(bin_arr[x + input_file_size][y]) == '0')
			{
				final_arr[x][y] = 1;
			}
			if (bin_arr[x][y] == 0 && bin_arr[x + input_file_size][y] == 0)// 2 SPACES XOR'D
			{
				final_arr[x][y] = 0;
			}
			if (bin_arr[x][y] == 0 && char(bin_arr[x + input_file_size][y]) == '1')// INPUT SPACE XOR 1
			{
				final_arr[x][y] = 1;
			}
			if (bin_arr[x][y] == 0 && char(bin_arr[x + input_file_size][y]) == '0')// INPUT SPACE XOR 0
			{
				final_arr[x][y] = 0;
			}
			if (char(bin_arr[x][y]) == '1' && bin_arr[x + input_file_size][y] == 0)// INPUT 1 XOR SPACE
			{
				final_arr[x][y] = 1;
			}
			if (char(bin_arr[x][y]) == '0' && bin_arr[x + input_file_size][y] == 0)// INPUT 0 XOR SPACE
			{
				final_arr[x][y] = 0;
			}

		}
	}
	cout << "============= FINAL XOR'D VALUES ===============" << endl;
	for (int x = 0; x < input_file_size; x++)
	{
		for (int y = 0; y < 8; y++)
		{
			cout << final_arr[x][y];
		}
		cout << "(" << x << ")" << endl;
	}
// ================= Converting Binary to Decimal =============	
	for (int x = 0; x < input_file_size; x++)
	{
		for (int y = 0; y < 8; y++)
		{
			if (final_arr[x][y] == 1)
			{
				final_int[x] += binary_dec[y];
			}
		}
		cout << final_int[x] << "(" << x << ")" << endl;
	}
//=============== Output Final Text File in Hex ==========
	ofstream output_final;
	output_final.open("output_final.txt");
	for (int x = 0; x < input_file_size; x++)
	{
		output_final << hex << final_int[x] << " ";
	}
	cout << "=======================================" << endl;
	cout << "THIS IS YOUR FINAL CIPHER TEXT IN HEX: " << endl;
	cout << "=======================================" << endl;
	for (int x = 0; x < input_file_size; x++)
	{
		cout << hex << final_int[x] << " ";
	}
	return 0;
	system("pause");
}
