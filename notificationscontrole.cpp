#include <windows.h> //Bibliothèque graphique de Windows
#include <stdio.h> //Librairie standard d'imput/output
#include <Commdlg.h> //Librairie additionnelle de Windows.h
#include "Crypto.h" //Header contenant les fonctions de cryptographies
#include "copy&past.h" //Gestion du copier coller
#include "notificationscontrole.h"

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


VOID NotificationControle(HWND fenetrePrincipale,UINT message,WPARAM wParam, LPARAM lParam)
{
    UINT iId=LOWORD(wParam);
    UINT iCode=HIWORD(wParam);
    HWND hCtl=(HWND)lParam;

     int choix;

     HWND hEdit1;
     HWND hEdit2;
     HWND hEdit3;
     HINSTANCE instance;


        if(iId==ID_BUTTON_6)
        {
        SendMessage( hEdit1, EM_SETPASSWORDCHAR,'*',0);

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
