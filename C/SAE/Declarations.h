#include <stdio.h>          //Bibliothèque d'entrées/sorties
#include <stdlib.h>         //Bibliothèque standard (permet de faire pleins de trucs)
#include <string.h>         //Bibliothèque gestion des chaines de caractères
#include <time.h>           //Bibliothèque pour le temps
#include <unistd.h>         //Bibliothèque pour les sleep

#define MaxJoueurs 4

typedef struct              //Structures pour les coordonnées des cartes dans le tableau Emplacements
{
    int valeurI;
    int valeurJ;
} S_Coordonees;

typedef struct              //Structures pour enregistrer les différents joueurs
{
    int noJoueur;
    char pseudo[30];
    int score;
    int nbErreur;
    int ordinateur;
} S_Joueur;

typedef struct              //Structures pour enregistrer les différentes cartes
{
    int numCarte;
    int placeTableau;
    int retournee;
    int associee;
} S_Carte;

void afficheMenu();
void afficheRegles();
void debutPartie();
void saisieJoueurs(S_Joueur *joueur, int *i, int *nbOrdis);
void saisieParam(int *L, int *C, int *nbJ, S_Joueur *param, int *Emax);
void initEmplacements (int L, int C, S_Coordonees *Emplacements);
void melangerEmplacements(int L, int C, S_Coordonees *Emplacements);
void initPlateau(int L, int C, S_Coordonees *Emplacements, S_Carte **Plateau);
void initMemoire(int L, int C, S_Carte **Memoire);
void afficherPlateau(int L, int C, S_Carte **Plateau);
int partie(int L, int C, int nbJ, S_Joueur *joueur, S_Carte **Plateau, S_Carte **Memoire, int Emax);
void selectCarte(S_Carte **Plateau, S_Carte **Memoire, int *I, int *J, int L, int C, S_Joueur *joueur, int *numJoueur);
void selectCarteOrdi1(S_Carte **Plateau, S_Carte **Memoire, int L, int C, int *I, int *J);
void selectCarteOrdi2(S_Carte **Plateau, S_Carte **Memoire, int L, int C, int *I, int *J, int prevI, int prevJ);
void permutJoker(int L, int C, S_Carte **Plateau, int i, int j);
void afficheParam(S_Joueur *joueur, int nbJ, int Emax);
void afficheScores(S_Joueur *joueur, int nbJ);
void gagnant(S_Joueur *joueur, int nbJ);