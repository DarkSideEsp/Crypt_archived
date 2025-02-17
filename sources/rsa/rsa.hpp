#pragma once

#include <vector>
#include <string>
#include <algorithm>


using namespace std;


vector<unsigned long long> gen_keys(unsigned long long p, unsigned long long q);

unsigned long long encrypt(unsigned long long m, unsigned long long e, unsigned long long n);

unsigned long long decrypt(unsigned long long c, unsigned long long d, unsigned long long n);

vector<unsigned long long> rsa_encrypt(vector<unsigned int> line, unsigned long long e, unsigned long long n);

vector<unsigned int> rsa_decrypt(vector<unsigned long long> crypted_line, unsigned long long d, unsigned long long n);
