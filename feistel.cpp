/****************************************************************************
Projet Nucleus                                                              *
Jean-Baptiste Laguitton ; Nicolas Taffoureau ; Brandon Guigo / 2018         *
                                                                            *
Programme de messagerie cryptée                                             *
                                                                            *
                                                                            *
feistel.cpp, fonctions implémentants un réseau de Feistel                   *
****************************************************************************/

#include <iostream>
#include <string>
#include <iomanip>
#include <vector>
#include <limits.h>

using namespace std;

signed int key = 62530;

//Fonction de rotation circulaire de la clef pour générer une sous clef
int rotr(int key)
{
    return (key>>16) | (key<<16);
}

int xorfeistel(int subblock, char key)
{
	return subblock^key;
}

//Fonction de decryptage
int* decrypt(int *left, int *right, int* p_key)
{
	int rounds = 16;
	for(int i = rounds - 1; i >= 0; i--)
	{

		int temp = *left ^ xorfeistel(*right, rotr(*(char*)p_key));
		if(i != 15)
		{
			*left = *right;
			*right = temp;

		}
		else *right = temp;
	}

	return left;
}

//Fonction de cryptage
int* encrypt(int *left, int *right, int* p_key)
{
	int rounds = 16;
	for(int i = 0; i < rounds; i++)
	{

		int temp = *right ^ xorfeistel(*left, rotr(*(char*)p_key));

		if(i != 15)
		{

			*right = *left;
			*left = temp;
		}
		else *right = temp;
	}

	return left;
}

string feistelencrypt(string data)
{
    //On défini un string message qui sera le message de l'utilisateur et un vector de string
	string message = data;
	vector<string> v_s;

	int length = message.length();
	int quotient = length/16;

	//On prévoit le cas où la longueur de la chaîne n'est pas un multiple de 16
	if(length%16 != 0) quotient++;

	for(int i = 0; i < quotient; i++)
	{
		string new_message = message.substr(0, 16);
		v_s.push_back(new_message);

		for(int i = 0; i < 16; i++)
		{
			message.erase(0, 1);
		}
	}

	//On rejoute un padding
	string last_string = v_s.at(v_s.size()-1);
	if(last_string.length() < 16) last_string.resize(16, '0');

	signed int* p_key = &key;

	//on crypte le message
	for(int i = 0; i < v_s.size(); i++)
	{
		const char* c = v_s.at(i).c_str();

		int* left = (int*)c;
		int* right = left+1;

		c = (char*)encrypt(left, right, p_key);

	}


    string temp = "";
    string chiffre = "";

	for(int i = 0; i < v_s.size(); i++)
	{
		const char* c = v_s.at(i).c_str();
		temp = c ;
		chiffre += temp;

	}
	return chiffre ;


}


 string feisteldecrypt(string data)
{
    //On défini un string message qui sera le message de l'utilisateur et un vector de string
	string message = data;
	vector<string> v_s;

	int length = message.length();
	int quotient = length/16;

	//On prévoit le cas où la longueur de la chaîne n'est pas un multiple de 16
	if(length%16 != 0) quotient++;

	for(int i = 0; i < quotient; i++)
	{
		string new_message = message.substr(0, 16);
		v_s.push_back(new_message);

		for(int i = 0; i < 16; i++)
		{
			message.erase(0, 1);
		}
	}



	signed int* p_key = &key;

	//on decrypte le message
	for(int i = 0; i < v_s.size(); i++)
	{
		const char* c = v_s.at(i).c_str();

		int* left = (int*)c;
		int* right = left+1;

		c = (char*)decrypt(left, right, p_key);
	}

//On affiche le message decrypté
    string temp = "";
    string dechiffre = "";

	for(int i = 0; i < v_s.size(); i++)
	{
		const char* c = v_s.at(i).c_str();
		temp = c ;
		dechiffre += temp;
	}
	return dechiffre ;
}
