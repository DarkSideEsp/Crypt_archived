#include <vector>
#include <string>

#include "base_crypt_algs.hpp"


using namespace std;


const string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz 0123456789~!@#$%^&*()№;:?-_=+|<>АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯабвгдеёжзийклмнопрстуфхцчшщъыьэюя";

string caesar_encrypt(string line, int n){
    string crypted_line = "";

    for(auto i : line){
        crypted_line += char(int(i) + n);
    }

    return crypted_line;
}

string caesar_decrypt(string crypted_line, int n){
    string line = "";

    for(auto i : crypted_line){
        line += char(int(i) - n);
    }

    return line;
}


unsigned long long vigener_recovery_mod(long long a, long long b){
    return (b + (a % b)) % b;
}

string vigener_encrypt(string line, string password){
    string crypted_line = "";

    string full_password = "";
    for(unsigned int i = 0; i < line.size(); i++){
        full_password += password[i % password.size()];
    }

    for(unsigned int i = 0; i < line.size(); i++){
        crypted_line += char((int(line[i]) + int(full_password[i]) - (2 * int('a'))) % 26 + int('a')); 
    }

    return crypted_line;
}

string vigener_decrypt(string crypted_line, string password){
    string line = "";

    string full_password = "";
    for(unsigned int i = 0; i < crypted_line.size(); i++){
        full_password += password[i % password.size()];
    }

    for(unsigned int i = 0; i < crypted_line.size(); i++){
        line += char(vigener_recovery_mod((int(crypted_line[i]) - int(full_password[i])), 26) + int('a')); 
    }

    return line;
}

vector<unsigned int> string_to_nums(string line){
    vector<unsigned int> out_line;
    for(auto i : line){
        out_line.push_back(alphabet.find(i));
    }
    return out_line;
}

string nums_to_string(vector<unsigned int> line){
    string out_line = "";
    for(auto i : line){
        out_line += alphabet[i];
    }
    return out_line;
}
