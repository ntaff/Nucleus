/****************************************************************************
Projet Nucleus                                                              *
Jean-Baptiste Laguitton ; Nicolas Taffoureau ; Brandon Guigo / 2018         *
                                                                            *
Programme de messagerie cryptée                                             *
                                                                            *
****************************************************************************/

//Inclusions des bibliothèques utilisées

#include <windows.h> //Bibliothèque graphique de Windows
#include <stdio.h> //Librairie standard d'imput/output
#include <Commdlg.h> //Librairie additionnelle de Windows.h
#include "cbc.h"
#include "feistel.h"
#include "pseudoaleatoire.h" //Fonction générant des nombres pseudo aléatoires
#include "cryptobloc.h"
#include "authmessage.h"

HINSTANCE instance; //Création de l'instance principale

//Define des ID servant à la création des boutons et objets graphiques de la fenêtre

//Bouton permettant d'envoyer le message
#define ID_BUTTON_3         113

//EditBox où l'utilisateur peut rentrer le message
#define ID_EDIT_1           115
//EditBox affichant la conversation
#define ID_EDIT_2           116
//EditBox affichant diverses informations
#define ID_EDIT_3          118

//Bouton définissant le mode de cryptage comme étant par bloc
#define ID_RADIOBUTTON_11   117
//Bouton définissant le mode de cryptage comme étant par flux
#define ID_RADIOBUTTON_21   120

//Bouton permettant de rendre le message visible
#define ID_BUTTON_5   123
//Bouton permettant de rendre le message invisible
#define ID_BUTTON_6   124

//Définie les handle de la fenêtre
HWND hEdit1;
HWND hEdit2;
HWND hEdit3;
HWND hControle;


//Pour savoir les choix de l'utilisateur
int choix;



// Fonction composée des fonctions permettant la création de boutons
VOID RemplieFenetrePrincipale(HWND fenetrePrincipale)
{

    //Création de l'édit pour rentrer le message
     hEdit1=CreateWindow(
        "EDIT",
        "Bonjour, je suis un texte d'exemple.",
        WS_CHILD|WS_VISIBLE|ES_MULTILINE|ES_AUTOHSCROLL|WS_BORDER, //Attribut du control
        10,80,
        400,120, //Placement et dimension
        fenetrePrincipale,
        (HMENU)ID_EDIT_1,
        instance,
        NULL);

           CreateWindow(
        "BUTTON",
        "Conversation",
        WS_CHILD|WS_VISIBLE|BS_GROUPBOX,
        495, 10,
        411,225,
        fenetrePrincipale,
        NULL,
        instance,
        NULL);

        {

            //Création de l'édit affichant la conversation
           hEdit2=CreateWindow(
            "EDIT",
            "",
            WS_CHILD|WS_VISIBLE|ES_MULTILINE|ES_READONLY|WS_BORDER,
            500,30,
            400,200,
            fenetrePrincipale,
            (HMENU)ID_EDIT_2,
            instance,
            NULL);
        }


           CreateWindow(
        "BUTTON",
        "Logs",
        WS_CHILD|WS_VISIBLE|BS_GROUPBOX,
        495, 250,
        411,125,
        fenetrePrincipale,
        NULL,
        instance,
        NULL);

        {

            //Création de l'édit affichant la conversation
           hEdit3=CreateWindow(
            "EDIT",
            "",
            WS_CHILD|WS_VISIBLE|ES_MULTILINE|ES_READONLY|WS_BORDER,
            500,270,
            400,100,
            fenetrePrincipale,
            (HMENU)ID_EDIT_3,
            instance,
            NULL);
        }

    CreateWindow(
        "BUTTON",
        "Envoyer",
        WS_CHILD|WS_VISIBLE|BS_PUSHBUTTON,
        412,90,
        80,30,
        fenetrePrincipale,
        (HMENU)ID_BUTTON_3,
        instance,
        NULL);


        //Création d'un "group" contenant les différentes methode de cryptage
   CreateWindow(
        "BUTTON",
        "Méthodes de cryptage",
        WS_CHILD|WS_VISIBLE|BS_GROUPBOX,
        10, 205,
        400,55,
        fenetrePrincipale,
        NULL,
        instance,
        NULL);

        {

            // Deux radiobuttons
            hControle=CreateWindow(
                "BUTTON",
                "Bloc",
                WS_CHILD|WS_VISIBLE|BS_AUTORADIOBUTTON|WS_GROUP,
                10+10,205+20,
                100,20,
                fenetrePrincipale,
                (HMENU)ID_RADIOBUTTON_11,
                instance,
                NULL);

            hControle=CreateWindow(
                "BUTTON",
                "Flux",
                WS_CHILD|WS_VISIBLE|BS_AUTORADIOBUTTON,
                130+120,205+20,
                100,20,
                fenetrePrincipale,
                (HMENU)ID_RADIOBUTTON_21,
                instance,
                NULL);



         CreateWindow(
            "BUTTON",
            "Fenêtre de saisie du message",
            WS_CHILD|WS_VISIBLE|BS_GROUPBOX,
            10, 10,
            400,70,
            fenetrePrincipale,
            NULL,
            instance,
            NULL);

            {
                // Deux autres radiobuttons
                hControle=CreateWindow(
                    "BUTTON",
                    "Non sécurisé",
                    WS_CHILD|WS_VISIBLE|BS_AUTORADIOBUTTON|WS_GROUP,
                    20,35,
                    150,35,
                    fenetrePrincipale,
                    (HMENU)ID_BUTTON_5,
                    instance,
                    NULL);

                hControle=CreateWindow(
                    "BUTTON",
                    "Sécurisé",
                    WS_CHILD|WS_VISIBLE|BS_AUTORADIOBUTTON,
                    170,35,
                    150,35,
                    fenetrePrincipale,
                    (HMENU)ID_BUTTON_6,
                    instance,
                    NULL);

            }
        }
}

VOID NotificationControle(HWND fenetrePrincipale,UINT message,WPARAM wParam, LPARAM lParam)
{
    UINT iId=LOWORD(wParam);
    UINT iCode=HIWORD(wParam);
    HWND hCtl=(HWND)lParam;

     int choix;
     HINSTANCE instance;


        if(iId==ID_BUTTON_6)
        {
            SendMessage(hEdit1, EM_SETPASSWORDCHAR,'*',0);
        }
        else if(iId==ID_BUTTON_5)
        {
            SendMessage( hEdit1, EM_SETPASSWORDCHAR,0,0);
        }

        else if(iId==ID_RADIOBUTTON_11)
        {
            choix +=10;
        }

}

        LRESULT CALLBACK procedureFenetrePrincipale(HWND fenetrePrincipale, UINT message, WPARAM wParam, LPARAM lParam)
        {

            switch (message)
            {
                case WM_CREATE: //Fonction a executer à la création de la fenêtre
                    RemplieFenetrePrincipale(fenetrePrincipale);

                    return 0;
                case WM_COMMAND:
                    NotificationControle(fenetrePrincipale,message,wParam,lParam);
                    return 0;
                case WM_DESTROY: //Fonction a executer à la destruction de la fenêtre
                    PostQuitMessage(0);
                    return 0;
                default:
                    return DefWindowProc(fenetrePrincipale,message,wParam,lParam);
            }
        }

 // Fonction équivalent au Main
// Le type LPSTR est l'équivalent du type Char*
int WINAPI WinMain (HINSTANCE cetteInstance, HINSTANCE precedenteInstance,
             LPSTR lignesDeCommande, int modeDAffichage)
{
    HWND fenetrePrincipale;
    MSG message;
    WNDCLASS classeFenetre;

    instance = cetteInstance;

    classeFenetre.style = CS_DBLCLKS; // Pour attraper les double-clics
    classeFenetre.lpfnWndProc = procedureFenetrePrincipale; // Définit la fonction callback à utiliser pour cette fenêtre
    classeFenetre.cbClsExtra = 0;
    classeFenetre.cbWndExtra = 0;
    classeFenetre.hInstance = NULL;
    classeFenetre.hIcon = LoadIcon(NULL, IDI_WINLOGO);
    classeFenetre.hCursor = LoadCursor(NULL, IDC_ARROW);
    classeFenetre.hbrBackground = (HBRUSH)(1 + COLOR_BTNFACE); //Permet de définir une nuance de gris sur la fenêtre
    classeFenetre.lpszMenuName =
    classeFenetre.lpszClassName = "classeF";

// On prévoit quand même le cas où ça échoue
    if(!RegisterClass(&classeFenetre))
        return FALSE;


        // Création de la fenêtre principale, sans l'afficher
    fenetrePrincipale=CreateWindow(
        "classeF",
        "Nucleus", //Nom de la fenêtre
        WS_OVERLAPPEDWINDOW, //Type de fenêtre
        CW_USEDEFAULT,CW_USEDEFAULT,
        925,460, //On indique ici ses dimensions en pixels
        NULL,
        NULL,
        cetteInstance,
        NULL);

        //On Prévoit encore le cas où ça échoue
    if (!fenetrePrincipale)
        return FALSE;

    ShowWindow(fenetrePrincipale,modeDAffichage); // Fonction permettant d'afficher la fenêtre
    UpdateWindow(fenetrePrincipale); //Rafraichit la fenêtre


    while(GetMessage(&message,NULL,0,0)) //Récupère les messages de l'utilisateur
    {
        TranslateMessage(&message);
        DispatchMessage(&message);
    }

    return message.wParam;
}
