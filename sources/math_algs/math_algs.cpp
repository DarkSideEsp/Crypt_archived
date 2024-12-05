#include <vector>


using namespace std;


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