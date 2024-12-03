#include <vector>
#include <string>
#include <numeric>

#include "../headers/algs.hpp"

using namespace std;


vector<unsigned long long> gen_keys(unsigned long long p, unsigned long long q){
    unsigned long long n, fi, d, k, e;
    e = 1;
    vector<unsigned long long> keys(3, 0);

    n = p * q;

    fi = (p - 1) * (q - 1);

    for(unsigned long long i = 2; i < fi; i++){
        if(gcd(i, fi) == 1){
            e = i;
            break;
        }
    }

    k = 1;
    while((k * fi + 1) % e != 0) k++;
    d = (k * fi + 1) / e;

    keys[0] = e;
    keys[1] = d;
    keys[2] = n;

    return keys;
}


unsigned long long crypt(unsigned long long m, unsigned long long e, unsigned long long n){
    unsigned long long c = binpow(m, e, n) % n;
    return c;
}


unsigned long long decrypt(unsigned long long c, unsigned long long d, unsigned long long n){
    unsigned long long m = binpow(c, d, n) % n;
    return m;
}


vector<unsigned long long> rsa_crypt_string(string line, unsigned long long e, unsigned long long n){
    vector<unsigned long long> crypted_line;

    for(unsigned int i = 0; i < line.size(); i++){
        crypted_line.push_back(crypt(int(line[i]), e, n));
    }

    return crypted_line;
}


string rsa_decrypt_line(vector<unsigned long long> crypted_line, unsigned long long d, unsigned long long n){
    string line = "";

    for(unsigned int i = 0; i < crypted_line.size(); i++){
        line += char(decrypt(crypted_line[i], d, n));
    }

    return line;
}
