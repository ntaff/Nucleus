/****************************************************************************
Projet Nucleus                                                              *
Jean-Baptiste Laguitton ; Nicolas Taffoureau ; Brandon Guigo / 2018         *
                                                                            *
Programme de messagerie cryptée                                             *
                                                                            *
                                                                            *
pseudoaleatoire.cpp, fonction implémentant un algorithme de génération     *
d'un nombre pseudo aléatoire, on utilise ici un Mersenne Twister            *
****************************************************************************/


#include <iostream>
#include <random>
#include <ctime>
#include "pseudoaleatoire.h"

//Utilisation de l'algorithme Mersenne Twister pour générer des nombres pseudos-aléatoires

int nombrepseudoaleatoire(int min, int max)

{

    static std::mt19937 mersenne(static_cast<int>(time(0))); // Initialisation du Mersenne Twister avec une seed "aleatoire"
	static const long double fraction = 1.0 / (static_cast<double>(mersenne.max()) + 1.0);
return min + static_cast<int>((max - min + 1) * (mersenne() * fraction));
}
