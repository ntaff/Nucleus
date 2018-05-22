/****************************************************************************
Projet Nucleus                                                              *
Jean-Baptiste Laguitton ; Nicolas Taffoureau ; Brandon Guigo / 2018         *
                                                                            *
Programme de messagerie cryptée                                             *
                                                                            *
                                                                            *
cryptobloc.cpp, fonctions implémentants SHA 512                             *
****************************************************************************/

#include <iostream>
#include <vector>
#include <bitset>
#include <stdio.h>
#include "cbc.h"
#include "feistel.h"
#include "pseudoaleatoire.h"
#include "cryptobloc.h"
#include "authmessage.h"


//Selon les specifications de SHA 512
#define ROTDROIT(mot,bit) (((mot) >> (bit)) | ((mot) << (32-(bit))))
#define SIG0(x) (ROTDROIT(x,1) ^ ROTDROIT(x,8) ^ ((x) >> 7))
#define SIG1(x) (ROTDROIT(x,19) ^ ROTDROIT(x,61) ^ ((x) >> 6))
#define CH(x,y,z) (((x) & (y)) ^ (~(x) & (z)))
#define MAJ(x,y,z) (((x) & (y)) ^ ((x) & (z)) ^ ((y) & (z)))
#define E0(x) (ROTDROIT(x,28) ^ ROTDROIT(x,34) ^ ROTDROIT(x,39))
#define E1(x) (ROTDROIT(x,14) ^ ROTDROIT(x,18) ^ ROTDROIT(x,41))

std:: string SHA512(std::string message)
{
    //convert le string en 8 bits par ascii
    std::vector<unsigned long> v ;
    for (int i = 0; i< message.size(); i++){
        std::bitset<8> tmp(message.c_str()[i]);

        v.push_back(tmp.to_ulong());
    }

    //calcule la taille de k pour le bourrage
    int tailleMessage = (int) v.size() *8;
    int k = 895 - tailleMessage;

    //ajout de 1 et de 7 0
    v.push_back(0x80);
    k -= 7;

    //ajout des 0 jusqu'a 1024 - 128
    for(int i = 0; i < k / 4; i++)
        v.push_back(0x00000000);

    //ajout de l en binaire pour faire 1024
    std::bitset<128> lBin(tailleMessage);

    //coupe le bloc de 128 en bloc de 8 bits
    std::string tmp =lBin.to_string();

    //met le 1e bloc dans le message
    std::bitset<8> temp(tmp.substr(0,8));
    v.push_back(temp.to_ulong());

    //ajoute le reste
    for(int i = 8; i < 123; i=i+8)
    {
        std::bitset<8> temp(tmp.substr(i,8));
        v.push_back(temp.to_ulong());
    }

    //MESSAGE AVEC PADDING OK DANS V

    std::vector<unsigned long> blocRetaille(16);

    for(int i = 0; i < 128; i = i + 8)
    {
        std::bitset<64> temp(0);

        temp = (unsigned long) v[i] << 48;
        temp |= (unsigned long) v[i + 1] << 40;
        temp |= (unsigned long) v[i + 2] << 32;
        temp |= (unsigned long) v[i + 3] << 24;
        temp |= (unsigned long) v[i + 4] << 16;
        temp |= (unsigned long) v[i + 5] << 8;
        temp |= (unsigned long) v[i + 6];

        blocRetaille[i/8] = temp.to_ulong();
    }

    //DEFINITION DES CONSTANTES POUR SHA 512
    unsigned long K[80] = {0x428a2f98d728ae22, 0x7137449123ef65cd, 0xb5c0fbcfec4d3b2f, 0xe9b5dba58189dbbc,
        0x3956c25bf348b538, 0x59f111f1b605d019, 0x923f82a4af194f9b, 0xab1c5ed5da6d8118,
        0xd807aa98a3030242, 0x12835b0145706fbe, 0x243185be4ee4b28c, 0x550c7dc3d5ffb4e2,
        0x72be5d74f27b896f, 0x80deb1fe3b1696b1, 0x9bdc06a725c71235, 0xc19bf174cf692694,
        0xe49b69c19ef14ad2, 0xefbe4786384f25e3, 0x0fc19dc68b8cd5b5, 0x240ca1cc77ac9c65,
        0x2de92c6f592b0275, 0x4a7484aa6ea6e483, 0x5cb0a9dcbd41fbd4, 0x76f988da831153b5,
        0x983e5152ee66dfab, 0xa831c66d2db43210, 0xb00327c898fb213f, 0xbf597fc7beef0ee4,
        0xc6e00bf33da88fc2, 0xd5a79147930aa725, 0x06ca6351e003826f, 0x142929670a0e6e70,
        0x27b70a8546d22ffc, 0x2e1b21385c26c926, 0x4d2c6dfc5ac42aed, 0x53380d139d95b3df,
        0x650a73548baf63de, 0x766a0abb3c77b2a8, 0x81c2c92e47edaee6, 0x92722c851482353b,
        0xa2bfe8a14cf10364, 0xa81a664bbc423001, 0xc24b8b70d0f89791, 0xc76c51a30654be30,
        0xd192e819d6ef5218, 0xd69906245565a910, 0xf40e35855771202a, 0x106aa07032bbd1b8,
        0x19a4c116b8d2d0c8, 0x1e376c085141ab53, 0x2748774cdf8eeb99, 0x34b0bcb5e19b48a8,
        0x391c0cb3c5c95a63, 0x4ed8aa4ae3418acb, 0x5b9cca4f7763e373, 0x682e6ff3d6b2b8a3,
        0x748f82ee5defb2fc, 0x78a5636f43172f60, 0x84c87814a1f0ab72, 0x8cc702081a6439ec,
        0x90befffa23631e28, 0xa4506cebde82bde9, 0xbef9a3f7b2c67915, 0xc67178f2e372532b,
        0xca273eceea26619c, 0xd186b8c721c0c207, 0xeada7dd6cde0eb1e, 0xeada7dd6cde0eb1e,
        0x06f067aa72176fba, 0x0a637dc5a2c898a6, 0x113f9804bef90dae, 0x1b710b35131c471b,
        0x28db77f523047d84, 0x32caab7b40c72493, 0x3c9ebe0a15c9bebc, 0x431d67c49c100d4c,
        0x4cc5d4becb3e42b6, 0x597f299cfc657e2a, 0x5fcb6fab3ad6faec, 0x6c44198c4a475817};

    unsigned long static H1 = 0x6a09e667f3bcc908;
    unsigned long static H2 = 0xbb67ae8584caa73b;
    unsigned long static H3 = 0x3c6ef372fe94f82b;
    unsigned long static H4 = 0xa54ff53a5f1d36f1;
    unsigned long static H5 = 0x510e527fade682d1;
    unsigned long static H6 = 0x9b05688c2b3e6c1f;
    unsigned long static H7 = 0x1f83d9abfb41bd6b;
    unsigned long static H8 = 0x5be0cd19137e2179;

    unsigned long a;
    unsigned long b;
    unsigned long c;
    unsigned long d;
    unsigned long e;
    unsigned long f;
    unsigned long g;
    unsigned long h;
    unsigned long t1;
    unsigned long t2;

    unsigned long W[80];
    //INIT W
    for(int t = 0; t <= 15; t++)
    {
        W[t] = blocRetaille[t] & 0xFFFFFFFF;

    }

    for(int t = 16; t <= 79; t++)
    {
        W[t] = SIG1(W[t-2]) + W[t-7] + SIG0(W[t-15]) + W[t-16];
        W[t] = W[t] & 0xFFFFFFFF;
    }
    a = H1;
    b = H2;
    c = H3;
    d = H4;
    e = H5;
    f = H6;
    g = H7;
    h = H8;

    for (int i = 0; i<15; i++){
        //initialise les registre


        for (int j = 0; j<79; j++){
            t1 = h + E1(e) + CH(e, f, g) + K[j] + W[j];
            t2 = E0(a) + MAJ(a, b, c);
            h = g;
            g = f;
            f = e;
            e = d + t1;
            d = c;
            c = b;
            b = a;
            a = t1 + t2;
        }

        H1 = a + H1;
        H2 = b + H2;
        H3 = c + H3;
        H4 = d + H4;
        H5 = e + H5;
        H6 = f + H6;
        H7 = g + H7;
        H8 = h + H8;
    }

    //return std::to_string(H1) + std::to_string(H2) + std::to_string(H3) + std::to_string(H4) + std::to_string(H5) + std::to_string(H6) + std::to_string(H7) + std::to_string(H8);
    //return H1+H2+H3+H4+H5+H6+H7+H8;

    char str[500];
    memset(str, 0, sizeof(str));

    sprintf(str, "%lx", H1);
    sprintf(str + strlen(str), "%lx", H2);
    sprintf(str + strlen(str), "%lx", H3);
    sprintf(str + strlen(str), "%lx", H4);
    sprintf(str + strlen(str), "%lx", H5);
    sprintf(str + strlen(str), "%lx", H6);
    sprintf(str + strlen(str), "%lx", H7);
    sprintf(str + strlen(str), "%lx", H8);
    return str;
}

std::string MAC(std::string message)
{
    std::string aChiffrer = SHA512(message);

    //A PASSER DANS UN ALGO DE CHIFFREMENT AVANT L'ENVOI ET REPASSER DANS ALGO DE DECRIFFREMENT A LA RECEPTION PUIS COMPARER AVEC CELUI CALCULER A L'AIDE DU MESSAGE RECU SANS LE HMAC
    string res = cbcencrypt(aChiffrer);
    return message+res;
}
