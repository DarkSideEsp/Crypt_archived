#include <iostream>
#include <vector>
#include <ctime>

#include "sources/base_crypt_algs/base_crypt_algs.hpp"
#include "sources/rsa/rsa.hpp"
#include "sources/math_algs/math_algs.hpp"


using namespace std;


int main(){
    string line, password;
    unsigned long long e, d, n, a, b;
    srand(time(NULL));
    cin >> line >> password;

    cout << "Caesar" << "\t" << line << "\t" << caesar_crypt(line, 2) << "\t" << caesar_decrypt(caesar_crypt(line, 2), 2) << "\n";
    cout << "Vigener" << "\t" << line << "\t" << vigener_crypt(line, password) << "\t" << vigener_decrypt(vigener_crypt(line, password), password) << "\n";


    vector<unsigned long long> primes = primes_gen(1000, 5000);
    a = rand() % primes.size();
    b = rand() % primes.size();
    while(a == b){
        a = rand() % primes.size();
        b = rand() % primes.size();
    }

    vector<unsigned long long> keys = gen_keys(primes[a], primes[b]);
    e = keys[0];
    d = keys[1];
    n = keys[2];
    vector<unsigned long long> crypted_line = rsa_crypt_string(line, e, n);

    cout << "Rsa" << "\t" << line << "\t";
    for(auto i : crypted_line) cout << i << " ";
    cout << "\t" << rsa_decrypt_line(crypted_line, d, n) << "\n";

    return 0;
}
