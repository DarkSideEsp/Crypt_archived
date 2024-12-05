#pragma once

#include <vector>


using namespace std;


unsigned long long binpow(unsigned long long a, unsigned long long n);

unsigned long long binpow(unsigned long long a, unsigned long long n, unsigned long long module);

vector<unsigned long long> primes_gen(unsigned long long mini=1000, unsigned long long maxi=1000000);
