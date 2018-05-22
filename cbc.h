/****************************************************************************
Projet Nucleus                                                              *
Jean-Baptiste Laguitton ; Nicolas Taffoureau / 2018                         *
                                                                            *
Programme de messagerie cryptée                                             *
                                                                            *
****************************************************************************/


#ifndef CBC_H_INCLUDED
#define CBC_H_INCLUDED
#include <string.h>
#include <string>

using namespace std;
//Prototypes des fonctions principales

string strxor(const string & str1, const string & str2);
string cbcencrypt(string data);
string cbcdecrypt(string data);

#endif
