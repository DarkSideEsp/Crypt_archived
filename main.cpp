#include <iostream>
#include <vector>

#include "sources/base_crypt_algs/base_crypt_algs.hpp"
#include "sources/rsa/rsa.hpp"
#include "sources/math_algs/math_algs.hpp"


using namespace std;


int main(){
    string line, password;
    unsigned long long e, d, n, a, b;

    cout << "Write the line: ";
    cin >> line;
    

    vector<unsigned int> numbered_line = string_to_nums(line);

    vector<unsigned long long> keys = gen_keys();
    e = keys[0];
    d = keys[1];
    n = keys[2];
    vector<unsigned long long> crypted_line = rsa_encrypt(numbered_line, e, n);

    cout << "Rsa" << "\t" << line << "\t";
    for(auto i : crypted_line) cout << "..." << i % 10 << " ";
    cout << "\t" << nums_to_string(rsa_decrypt(crypted_line, d, n)) << "\n";

    return 0;
}
