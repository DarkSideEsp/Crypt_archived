#include <iostream>
#include <vector>
#include <ctime>

using namespace std;


unsigned long long mod(unsigned long long a, unsigned long long b);
unsigned long long binpow(unsigned long long a, unsigned long long n);
unsigned long long binpow(unsigned long long a, unsigned long long n, unsigned long long module);


string caesar_crypt(string line, int n);
string caesar_decrypt(string crypted_line, int n);


string vigener_crypt(string line, string password);
string vigener_decrypt(string crypted_line, string password);


vector<unsigned long long> gen_keys(unsigned long long p, unsigned long long q);
unsigned long long crypt(unsigned long long m, unsigned long long e, unsigned long long n);
unsigned long long decrypt(unsigned long long c, unsigned long long d, unsigned long long n);
vector<unsigned long long> rsa_crypt_string(string line, unsigned long long e, unsigned long long n);
string rsa_decrypt_line(vector<unsigned long long> crypted_line, unsigned long long d, unsigned long long n);


vector<unsigned long long> primes_gen(unsigned long long mini=1000, unsigned long long maxi=1000000);


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
