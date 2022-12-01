#include<iostream>
#include<string>
#include<vector>
#include<unordered_map>
#include<cassert>
#include<fstream>
#include"tables.h"
using namespace std;

string hex2bin(const string& hex) {
	assert(hex.length() <= 16);
	string bin = "";
	unordered_map<char, string> mp;
	mp['0'] = "0000";
	mp['1'] = "0001";
	mp['2'] = "0010";
	mp['3'] = "0011";
	mp['4'] = "0100";
	mp['5'] = "0101";
	mp['6'] = "0110";
	mp['7'] = "0111";
	mp['8'] = "1000";
	mp['9'] = "1001";
	mp['A'] = "1010";
	mp['B'] = "1011";
	mp['C'] = "1100";
	mp['D'] = "1101";
	mp['E'] = "1110";
	mp['F'] = "1111";
	for (unsigned int i = 0; i < hex.size(); i++) {
		bin += mp[hex[i]];
	}
	int zeros_to_prepend = 64 - bin.length();
	for (int i = 0; i < zeros_to_prepend; i++) {
		bin.insert(0, "0");
	}
	return bin;
}

string bin2hex(const string& bin) {
	assert(bin.length() == 64);
	string hex = "";
	unordered_map<string, string> mp;
	mp["0000"] = "0";
	mp["0001"] = "1";
	mp["0010"] = "2";
	mp["0011"] = "3";
	mp["0100"] = "4";
	mp["0101"] = "5";
	mp["0110"] = "6";
	mp["0111"] = "7";
	mp["1000"] = "8";
	mp["1001"] = "9";
	mp["1010"] = "A";
	mp["1011"] = "B";
	mp["1100"] = "C";
	mp["1101"] = "D";
	mp["1110"] = "E";
	mp["1111"] = "F";
	for (unsigned int i = 0; i < bin.length(); i += 4) {
		string ch = "";
		ch += bin[i];
		ch += bin[i + 1];
		ch += bin[i + 2];
		ch += bin[i + 3];
		hex += mp[ch];
	}
	return hex;
}

string bin2dec(const string& bin) {
	string dec = "";
	unordered_map<string, string> mp;
	mp["00"] = "0";
	mp["01"] = "1";
	mp["10"] = "2";
	mp["11"] = "3";
	mp["0000"] = "0";
	mp["0001"] = "1";
	mp["0010"] = "2";
	mp["0011"] = "3";
	mp["0100"] = "4";
	mp["0101"] = "5";
	mp["0110"] = "6";
	mp["0111"] = "7";
	mp["1000"] = "8";
	mp["1001"] = "9";
	mp["1010"] = "10";
	mp["1011"] = "11";
	mp["1100"] = "12";
	mp["1101"] = "13";
	mp["1110"] = "14";
	mp["1111"] = "15";
	dec = mp[bin];
	return dec;
}

string dec2bin(const string& dec) {
	string bin = "";
	unordered_map<string, string> mp;
	mp["0"] = "0000";
	mp["1"] = "0001";
	mp["2"] = "0010";
	mp["3"] = "0011";
	mp["4"] = "0100";
	mp["5"] = "0101";
	mp["6"] = "0110";
	mp["7"] = "0111";
	mp["8"] = "1000";
	mp["9"] = "1001";
	mp["10"] = "1010";
	mp["11"] = "1011";
	mp["12"] = "1100";
	mp["13"] = "1101";
	mp["14"] = "1110";
	mp["15"] = "1111";
	bin = mp[dec];
	return bin;
}


string P_res(const string& bit_stream) {
	string new_text = "";
	for (unsigned int i = 0; i < 32; i++)
		new_text += bit_stream[P_box[i] - 1];
	return new_text;
}



string sbox_res(const string& bit_stream) {
	assert(bit_stream.length() == 48);
	string new_text, text_segment, row_val, left, right, col_val = "";
	int select_box, selected_val, row_val_dec, col_val_dec = 0;
	for (unsigned int i = 0; i < 48; i += 6) {
		left = bit_stream.substr(i, 1);
		right = bit_stream.substr(i + 5, 1);
		row_val = left + right;
		row_val_dec = stoi(bin2dec(row_val));
		col_val = bit_stream.substr(i + 1, 4);
		col_val_dec = stoi(bin2dec(col_val));
		select_box = i / 6;
		selected_val = sbox[select_box][row_val_dec][col_val_dec];
		text_segment = dec2bin(to_string(selected_val));
		new_text += text_segment;
	}
	return new_text;
}

string IP_res(const string& plaintext) {
	string new_text = "";
	for (unsigned int i = 0; i < 64; i++) {
		new_text += plaintext[IP[i] - 1];
	}
	return new_text;
}

string IPrev_res(const string& bit_stream) {
	string new_text = "";
	for (unsigned int i = 0; i < 64; i++)
		new_text += bit_stream[IP_rev[i] - 1];
	return new_text;
}

string E_res(const string& right) {
	string new_text = "";
	for (unsigned int i = 0; i < 48; i++) {
		new_text += right[E_[i] - 1];
	}
	return new_text;
}

string PC1_res(const string& key) {
	string new_key = "";
	for (unsigned int i = 0; i < 56; i++) {
		new_key += key[PC1[i] - 1];
	}
	return new_key;
}


//string permute(string s,int *arr, int n) {
//    int i;
//    string per = " ";
//    for (i = 0; i < n; i++) {
//        per += s[arr[i] - 1];
//    }
//    return per;
//}

//string shift_once(string key_chunk) {
//	string shifted = "";
//	for (int i = 1; i < 28; i++) {
//		shifted += key_chunk[i];
//	}
//	shifted += key_chunk[0];
//	return shifted;
//}
//
//
//string shift_twice(string key_chunk) {
//	string shifted = "";
//	for (int i = 0; i < 2; i++) {
//		for (int j = 1; j < 28; j++) {
//			shifted += key_chunk[j];
//		}
//		shifted += key_chunk[0];
//		key_chunk = shifted;
//		shifted = "";
//	}
//	return key_chunk;
//}

vector<string> generate_subkeys(const string& key) {
	vector<string> subkeys;
	string left, right, newLeft, newRight, temp_key, new_key = "";
	for (unsigned int i = 0; i < 16; i++) {
		left = key.substr(0, 28);
		right = key.substr(28, 28);
		if (shift[i] == 1|| shift[i] == 8 || shift[i] == 15 ) {
			newLeft = left.substr(1, 27) + left.substr(0, 1);
			newRight = right.substr(1, 27) + right.substr(0, 1);
		}
		else {
			newLeft = left.substr(2, 26) + left.substr(0, 2);
			newRight = right.substr(2, 26) + right.substr(0, 2);
		}
		temp_key = newLeft + newRight;
		new_key = ""; 
		for (int j = 0; j < 48; j++) {
			new_key += temp_key[PC2[j] - 1]; 
		}
		subkeys.push_back(new_key);
	}
	return subkeys;
}


string readtext(const string& fileName) {
	ifstream fileIn;
	string text = "";
	fileIn.open(fileName);
	if (!fileIn.is_open()) {
		cerr << "invalid file name" << endl;
		exit(0);
	}
	getline(fileIn, text);
	return text;
}

void writetext(const string& fileName, const string& data) {
	ofstream fileOut;
	string text = data;
	fileOut.open(fileName);
	if (!fileOut.is_open()) {
		cerr << "invalid file name" << endl;
		exit(0);
	}
	fileOut << data;
}

string XOR(const string& a, const string& b) {
	assert(a.length() == b.length());
	string res = "";
	for (unsigned int i = 0; i < a.length(); i++) {
		if (a[i] != b[i])
			res += "1";
		else
			res += "0";
	}
	return res;
}

string round_function(const string& left32, const string& right32, const vector<string>& subkeys) {
	string E_, E_XOR, sbox, permute, left, previousLeft, right, encrypted = "";
	for (unsigned int i = 0; i < subkeys.size(); i++) {
		if (i == 0) {
			left = left32;
			right = right32;
		}
		E_ = E_res(right);
		E_XOR = XOR(E_, subkeys[i]);
		sbox = sbox_res(E_XOR);
		permute = P_res(sbox);
		previousLeft = left;
		left = right;
		right = XOR(previousLeft, permute);
	}
	encrypted = left + right;
	return encrypted;
}


void DES_encrypt() {
	string round_result, encrypt, left, right, plaintext_hex, plaintext_bin, key_hex, key_bin, fileName = "";
	vector<string> subkeys;
	cout << "Encryption: " << endl;
	cout << "Input the key in hex form: ";
	getline(cin, key_hex);
	cout << "Input the file name .txt to encrypt: ";
	getline(cin, fileName);
	plaintext_hex = readtext(fileName);
	plaintext_bin = hex2bin(plaintext_hex);
	plaintext_bin = IP_res(plaintext_bin);
	//разбиваем на две части
	left = plaintext_bin.substr(0, 32);
	right = plaintext_bin.substr(32, 32);
	key_bin = hex2bin(key_hex);
	subkeys = generate_subkeys(key_bin);
	key_bin = PC1_res(key_bin);
	round_result = round_function(left, right, subkeys);
	// swap?
	left = round_result.substr(32, 32);
	right = round_result.substr(0, 32);
	encrypt = left + right;
	encrypt = IPrev_res(encrypt);
	encrypt = bin2hex(encrypt);
	writetext(fileName, encrypt);
	}
	
// Не получилось.....
//void DES_decrypt(){
//	cout << "Decryption: ";
//	string round_result, decrypt, left, right, plaintext_hex, plaintext_bin, key_hex, key_bin, fileName = "";
//	vector<string> subkeys;
//	cout << "Input the key in hex form: ";
//	getline(cin, key_hex);
//	cout << "Input the file name .txt to decrypt: ";
//	getline(cin, fileName);
//	plaintext_hex = readtext(fileName);
//	plaintext_bin = hex2bin(plaintext_hex);
//	reverse(subkeys.begin(), subkeys.end());
//	decrypt = IPrev_res(decrypt);
//	decrypt = bin2hex(decrypt);
//	writetext(fileName, decrypt);
//
//	}
//	


int main() {
	DES_encrypt();
	return 0;
}





