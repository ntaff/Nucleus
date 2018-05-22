#ifndef CRYPTOBLOC_H_INCLUDED
#define CRYPTOBLOC_H_INCLUDED

using namespace std;

int primtest(int prim);
void extd_pgcd(struct epgcd* s);
int pgcd(int a, int b);
unsigned long pow_mod_code(unsigned short b, unsigned long d, unsigned short n);
unsigned long pow_mod_decode(unsigned short b, unsigned long e, unsigned short n);
int rsa_keygen(struct RSA* rsa);
string code_rsa(string key);

#endif // CRYPTOBLOC_H_INCLUDED
