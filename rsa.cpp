/****************************************************************************
Projet Nucleus                                                              *
Jean-Baptiste Laguitton ; Nicolas Taffoureau ; Brandon Guigo / 2018         *
                                                                            *
Programme de messagerie cryptée                                             *
                                                                            *
                                                                            *
rsa.cpp, fonctions implémentants RSA                                        *
****************************************************************************/

//Inclusion des bibliotheques utilisées
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <math.h>

using namespace std;

//Struct de stokage des clés RSA
struct RSAKEY
{
    long n;
    int k;
};

//Struct principale du RSA, avec les deux clés
struct RSA
{
    struct RSAKEY pubkey;
    struct RSAKEY prikey;

};

//Struct stockage des variables du PGCD étendu
struct epgcd
{
    long r,u,v,a,b;
};

//Génération de nombres pseudoaleatoires entiers entre min et max
int borned_rand(int min, int max)
{
    return (int)(((double)rand() * (double)(max - min) / (double)RAND_MAX)) + min ;
}

//Test de primalité. Retourne 1 si premier, 0 sinon (acc=100%)
int primtest(int prim)
{
    int i=3;
    if ((prim%2)==0) return 0;  //Si divisible par deux alors non premier
    for (i=3; i<((int)sqrt(prim)+1); i=i+2)
    {
        if ((prim%i)==0) return 0; //si divisible par au moins un i (avec i allant de 3 à sqrt(prim) avec un pas de 2) alors nom premier
    }
    return 1; //Sinon premier
}

//Implémentation du PGCD étendu (parametres : a et b (de la struct epgcd)
void extd_pgcd(struct epgcd* s)
{
    //Implémentation d'une résolution du thrm de bezout (forall (a,b) in N² & (u,v) in Z² ; (au+bv) >= pgcd(a,b))
    long q;
    s->r = s->a;
    long r2 = s->b;
    s->u = 1; s->v = 0;
    long u2 = 0; long v2 = 1;
    while (r2 != 0)
    {
     q = (long) s->r/r2;
     long rs = s->r;
     long us = s->u;
     long vs = s->v;
     s->r = r2; s->u = u2; s->v = v2;
     r2 = rs - q * r2;
     u2 = us - q*u2;
     v2 = vs - q*v2;
     }
};

//pgcd réccursif (ERREUR si pile dépassée)
int pgcd(int a, int b)
{
    int c,d;
    if (a>b) c=a; else c=b;
    if (a<b) d=b; else d=c;
    if(d==1) return 1;
    if (d==0) return c;
    else return pgcd(d, (c%d));
}

//pow_mod calcule x**y %z
unsigned long pow_mod(unsigned short x, unsigned long y, unsigned short z)
{
    unsigned long number = 1;
    //Tant que y vrai
    while (y)
    {
        if (y & 1)
        number = number * x % z;

        // Decalage des bits de y, la boucle a autant d'itération que y a de chiffre
        y >>= 1;
        x = (unsigned long)x * x % z;
    }
    return number;
}


//Génération des clés RSA, retoure 1 quand terminé
int rsa_keygen(struct RSA* rsa)
{
    //Variables locales
    struct epgcd rsa_d;
    struct epgcd ep;
    int p, q;
    long d,phi, e;
    do
    {
        p=borned_rand(50, 100);
    }while(primtest(p)!=1);
    //Génération du premier nombre aléatoire
    do
    {
        q=borned_rand(50, 100);
    }while(primtest(q)!=1&&p!=q);
    //Génération du 2eme nombre aléatoire
    phi=(q-1)*(p-1);
    do{
    e=borned_rand(0, phi);
    ep.a=e;
    ep.b=phi;
    extd_pgcd(&ep);
    }while(ep.r!=1);
    //Calcul de e tel que et e phi premier entre eux ET e<phi
    rsa_d.a=e; rsa_d.b=phi;
    extd_pgcd(&rsa_d);
    d=rsa_d.u;
    //Calcul de l'inverse modulaire de e, avec le thrm de Bezout
    rsa->prikey.n=p*q;
    rsa->pubkey.n=p*q;
    rsa->prikey.k=d;
    rsa->pubkey.k=e;
    //Remplissage des struct clés
    return 1;
}

//Codage RSA
string code_rsa(string symkey){


    struct RSA thisRSA;
    char cdc;
    string finalkey = "";
    //Variables déclarées

    rsa_keygen(&thisRSA); //Génération des clés RSA, peut être long !

    int pubkeyN = thisRSA.pubkey.n ; //On stock la clef publique
    int pubkeyK = thisRSA.pubkey.k ;


    for (int i = 0 ; i < symkey.size() ; i++) //On boucle sur la taille de la variable d'entrée
    {
        cdc= pow_mod((unsigned short)symkey[i], thisRSA.pubkey.k, thisRSA.pubkey.n);
        finalkey += cdc ;
    }


return finalkey;
}

