/****************************************************************************
Projet Nucleus                                                              *
Jean-Baptiste Laguitton ; Nicolas Taffoureau / 2018                         *
                                                                            *
Programme de messagerie cryptée                                             *
                                                                            *
****************************************************************************/


#ifndef FEISTEL_H_INCLUDED
#define FEISTEL_H_INCLUDED

int rotr(int v);
int xorfeistel(int subblock, char key);
int* decrypt(int *left, int *right, int* p_key);
int* encrypt(int *left, int *right, int* p_key);
//string feistelencrypt(string data);
//string feisteldecrypt(string data);

#endif // FEISTEL_H_INCLUDED
