#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>

using namespace std;


unsigned long long mod(long long a, long long b){
    return (b + (a % b)) % b;
}

unsigned long long binpow(unsigned long long a, unsigned long long n){
    if(n == 0) return 1;
    else if(n % 2 == 0){
        unsigned long long bpa = binpow(a, n / 2);
        return bpa * bpa;
    }else{
        return binpow(a, n - 1) * a;
    }
}

unsigned long long binpow(unsigned long long a, unsigned long long n, unsigned long long module){
    if(n == 0) return 1;
    else if(n % 2 == 0){
        unsigned long long bpa = binpow(a, n / 2, module) % module;
        return (bpa * bpa) % module;
    }else{
        return ((binpow(a, n - 1, module) % module) * a) % module;
    }
}

vector<unsigned long long> primes_gen(unsigned long long mini=1000, unsigned long long maxi=1000000){
    vector<unsigned long long> primes;

    bool flag = true;
    for(unsigned long long i = mini; i <= maxi; i++){
        flag = true;
        for(unsigned long long j = 2; j * j <= i; j++){
            if(i % j == 0){
                flag = false;
                break;
            }
        }
        if(flag)primes.push_back(i);
    }

    return primes;
}


string caesar_crypt(string line, int n){
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



string vigener_crypt(string line, string password){
    string crypted_line = "";

    string full_password = "";
    for(int i = 0; i < line.size(); i++){
        full_password += password[i % password.size()];
    }

    for(int i = 0; i < line.size(); i++){
        crypted_line += char((int(line[i]) + int(full_password[i]) - (2 * int('a'))) % 26 + int('a')); // 26 - кол-во букв в английском алфавите
    }

    return crypted_line;
}

string vigener_decrypt(string crypted_line, string password){
    string line = "";

    string full_password = "";
    for(int i = 0; i < crypted_line.size(); i++){
        full_password += password[i % password.size()];
    }

    for(int i = 0; i < crypted_line.size(); i++){
        line += char(mod((int(crypted_line[i]) - int(full_password[i])), 26) + int('a')); // 26 - кол-во букв в английском алфавите
    }

    return line;
}
