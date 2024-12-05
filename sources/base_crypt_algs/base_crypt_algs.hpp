#pragma once

#include <vector>
#include <string>


using namespace std;


string caesar_crypt(string line, int n);

string caesar_decrypt(string crypted_line, int n);

unsigned long long vigener_recovery_mod(long long a, long long b);

string vigener_crypt(string line, string password);

string vigener_decrypt(string crypted_line, string password);
