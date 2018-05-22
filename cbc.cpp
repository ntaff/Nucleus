/****************************************************************************
Projet Nucleus                                                              *
Jean-Baptiste Laguitton ; Nicolas Taffoureau ; Brandon Guigo / 2018         *
                                                                            *
Programme de messagerie cryptée                                             *
                                                                            *
                                                                            *
cbc.cpp, fonctions implémentants le mode cipher bloc chaining               *
****************************************************************************/

#include <iostream>
#include <string.h>
#include <iomanip>
#include <vector>
#include <limits.h>
#include <cstdlib>
#include <cstdio>
#include <stdlib.h>
#include <stdio.h>
#include <sstream>

using namespace std;

string IV = "1234567890123456";
int blocksize = 16;

//Fonction permettant d'effectuer un OU exclusif (XOR) entre deux string
string strxor(const string & str1, const string & str2)
{
    string::size_type strmini = min(str1.size(), str2.size()); //Retourne la taille de la plus petite chaine entre str1 et str2
    string out = str1.substr(0, strmini); //On crée une chaine de la taille de strmini
   for(string::size_type i = 0; i < strmini;i++) //Size_type represente la taille de la chaine, peut importe sa longueur, pour prevoir les conflits entre les architectures 32 et 64bits
    {
        out[i] ^= str2[i]; //On xor entre out et str2
    }
return out; //On retourne la chaine xorée
}

string cbcencrypt(string data)
{
    //On défini un string message qui sera le message chiffré précedemment par le réseau de feistel et un vector de string
	string message = data;
	vector<string> v_s;

	// On calcule grâce à la longueur du message le nombre de blocs
	int length = message.length();
	int quotient = length/16;

	//On prévoit le cas où la longueur de la chaîne n'est pas un multiple de 16
	if(length%16 != 0) quotient++;

	//Chaque block sera un une instance de vector, on efface ensuite le message initial
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

	//on crypte le message

	string chiffre = "";

	for(int i = 0; i < v_s.size(); i++)
	{
	    //Le block actuel
		string actual = v_s.at(i).c_str();
		// Le block initialisé au vecteur d'initialisation
        string previous = IV;

		previous = strxor(previous, actual);
		chiffre += previous ;


	}

	return chiffre ;


}

string cbcdecrypt(string data)
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


	//on decrypte le message

	string dechiffre = "";
	for(int i = 0; i < v_s.size(); i++)
	{
		string actual = v_s.at(i).c_str();
		string previous = IV;
		previous = strxor(previous, actual);
		dechiffre += previous ;


	}

	return dechiffre ;


}
