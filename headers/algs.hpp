#pragma once

#include <vector>
#include <string>


using namespace std;



unsigned long long mod(long long a, long long b);

unsigned long long binpow(unsigned long long a, unsigned long long n);

unsigned long long binpow(unsigned long long a, unsigned long long n, unsigned long long module);

vector<unsigned long long> primes_gen(unsigned long long mini=1000, unsigned long long maxi=1000000);

string caesar_crypt(string line, int n);

string caesar_decrypt(string crypted_line, int n);

string vigener_crypt(string line, string password);

string vigener_decrypt(string crypted_line, string password);
