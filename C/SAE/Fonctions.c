#include "Declarations.h"

void afficheMenu()
{
    printf("\n\nVeuillez entrer le chiffre correspondant à l'option que vous choisissez :\n");
    printf("1 - Lancer une partie\n");
    printf("2 - Afficher les règles du jeu\n");
    printf("3 - Quitter le jeu\n");
    printf("Votre choix : ");
}





























void afficheRegles()
{
    printf("\nRègles du Mémorix :\n\n");
    printf("On dispose d'un jeu de cartes contenant uniquement des paires de cartes et un unique Joker (ici 0).\n");
    printf("Chaque paire est constituée de 2 cartes portant le même nombre, et il n'y a pas deux paires portant le même nombre.\n");
    printf("On pose aléatoirement les cartes face cachées de sorte à ce qu'elles forment un rectangle, puis chaque joueur à son tour retourne deux cartes de son choix.\n");
    printf("Si les deux cartes sont identiques, il marque un point, rejoue, et son nombre d'erreurs est remis à 0. Les deux cartes sont également enlevées du jeu.\n");
    printf("Sinon, il repose les deux cartes faces cachées exactement au même endroit, on lui compte une erreur supplémentaire, et c'est au joueur suivant de tenter sa chance.\n");
    printf("Si l'une des deux cartes retournées par un joueur est le Joker, on compte une erreur supplémentaire à celui-ci.\n");
    printf("La carte Joker est également permutée avec une carte choisie aléatoirement sur le plateau parmis les paires encore non découvertes (carte Joker comprise).\n");
    printf("Si un joueur ne trouve aucune paire après un certain nombre de tentatives, choisi à l'avance, il perd un point.\n");
    printf("Il continuera à perdre un point à chaque fois qu'il échoue, et ce jusqu'à ce qu'il trouve enfin une paire.\n");
    printf("La partie s'arrête une fois que toutes les paires ont été trouvées. Le gagnant est celui qui a le plus de points.\n");
}




































void debutPartie()
{
    int L, C, nbJoueurs, E;
    S_Joueur *tabJoueurs;
    S_Coordonees *tabCo;
    S_Carte **Plateau;
    S_Carte **Memoire;

    system("clear");

    tabJoueurs = malloc(MaxJoueurs * sizeof(S_Joueur));
    saisieParam(&L, &C, &nbJoueurs, tabJoueurs, &E);
    sleep(5);

    tabCo = malloc((L*C) * sizeof(S_Coordonees));
    Plateau = (S_Carte **)malloc(L * sizeof(S_Carte *));
    for(int i = 0; i < L; i++) 
    {
        Plateau[i] = (S_Carte *)malloc(C * sizeof(S_Carte));
    }
    Memoire = (S_Carte **)malloc(L * sizeof(S_Carte *));
    for(int i = 0; i < L; i++) 
    {
        Memoire[i] = (S_Carte *)malloc(C * sizeof(S_Carte));
    }

    initPlateau(L, C, tabCo, Plateau);
    initMemoire(L, C, Memoire);

    partie(L, C, nbJoueurs, tabJoueurs, Plateau, Memoire, E);
    
    free(tabJoueurs);
    free(tabCo);
    for (int i = 0; i < L; i++)
    {
        free(Plateau[i]);
    }
    free(Plateau);
}




































void saisieJoueurs(S_Joueur *joueur, int *i, int *nbOrdis)
{
    int ordi;
    char tempPseudo[255];
    int joueurValide = 0;
    int nombreValide = 0;



    while (joueurValide != 1)
    {
        printf("\nDéfinition du joueur %i\n", (*i)+1);
        printf("Ce joueur est-il un ordinateur (1 : oui, 0 : non) ? ");

        do                                                         
        {
            if (scanf("%i", &ordi) == 1)  
            {
                nombreValide = 1;
            } 
            else
            {
                while (getchar() != '\n');
                system("clear");
                printf("ERREUR !\n");
                printf("Rentres 0 ou 1 !\n");
                printf("Ce joueur est-il un ordinateur (1 : oui, 2 : non) ? ");
                nombreValide = 0;
            }
        } while(!nombreValide);

        if (ordi == 0 || ordi == 1)
        {
            (joueur->score) = 0;
            (joueur->nbErreur) = 0;

            if (ordi == 1)
            {
                *nbOrdis += 1;
                (joueur->noJoueur) = (*i)+1;
                sprintf((joueur->pseudo), "Ordinateur %i", (*nbOrdis));     //joueur->pseudo = (*joueur).pseudo = accéder à la valeur pseudo dans la structure joueur (désignée avec pointeur)
                (joueur->ordinateur) = 1;
            }
            else
            {
                (joueur->noJoueur) = (*i)+1;

                do          //Tant que le pseudo entré par le joueur comprends moins de 1 char ou plus de 30 char, on lui redemande d'entrer le pseudo
                {
                    printf("\nVeuillez rentrer le pseudo du joueur %i : ", (*i)+1);
                    scanf("%s", tempPseudo);
                    if(strlen(tempPseudo) > 30 || strlen(tempPseudo) < 1)
                    {
                        system("clear");
                        printf("\nVotre pseudo doit comporter au moins 1 caractère, et au plus 30 caractères !");
                    }
                } while(strlen(tempPseudo) > 30 || strlen(tempPseudo) < 1);

                sprintf((joueur->pseudo), "%s", tempPseudo);

                (joueur->ordinateur) = 0;
            }
            joueurValide = 1;
        }
        else
        {
            system("clear");
            printf("Rentres 0 ou 1 !\n");
            printf("Ce joueur est-il un ordinateur (1 : oui, 0 : non) ? ");
            joueurValide = 0;
        }
    }
}






































void saisieParam(int *L, int *C, int *nbJ, S_Joueur *param, int *Emax)
{
    int nbCartes;
    int nombreJoueurs;
    int nombreOrdis = 0;
    int nbEmax;
    int nombreValide = 0;
    int cartesValides = 0;
    int nbJoueursValides = 0;
    int erreurValide = 0;




    
    printf("\n");
    printf("Voulez-vous jouer avec 15, 21, 25, 27, 35, 45, 49, ou 63 cartes ? ");

    while (cartesValides != 1)
    {
        do                                                          
        {
            if (scanf("%i", &nbCartes) == 1)  
            {
                nombreValide = 1;
            } 
            else
            {
                while (getchar() != '\n');
                system("clear");
                printf("ERREUR !\n");
                printf("Rentres un nombre !\n");
                printf("Voulez-vous jouer avec 15, 21, 25, 27, 35, 45, 49, ou 63 cartes ? ");
                nombreValide = 0;
            }
        } while(!nombreValide);



        switch (nbCartes)
        {
        case 15:
            *L = 3;
            *C = 5;
            cartesValides = 1;
            break;

        case 21:
            *L = 3;
            *C = 7;
            cartesValides = 1;
            break;

        case 25:
            *L = 5;
            *C = 5;
            cartesValides = 1;
            break;

        case 27:
            *L = 3;
            *C = 9;
            cartesValides = 1;
            break;

        case 35:
            *L = 5;
            *C = 7;
            cartesValides = 1;
            break;

        case 45:
            *L = 5;
            *C = 9;
            cartesValides = 1;
            break;

        case 49:
            *L = 7;
            *C = 7;
            cartesValides = 1;
            break;

        case 63:
            *L = 7;
            *C = 9;
            cartesValides = 1;
            break;

        default:
            system("clear");
            printf("Rentres un des nombres proposés !\n");
            printf("Voulez-vous jouer avec 15, 21, 25, 27, 35, 45, 49, ou 63 cartes ? ");
            cartesValides = 0;
            break;
        }
    }

    printf("\n");
    printf("Le nombre maximum de joueurs possible est %i. Veuillez entrer le nombre de joueurs :  ", MaxJoueurs);

    while(nbJoueursValides != 1)
    {
        do                                                          
        {
            if (scanf("%i", &nombreJoueurs) == 1)  
            {
                nombreValide = 1;
            } 
            else
            {
                while (getchar() != '\n');
                system("clear");
                printf("ERREUR !\n");
                printf("Rentres un nombre compris entre 2 et %i (inclus) !\n", MaxJoueurs);
                printf("Le nombre maximum de joueurs possible est %i. Veuillez entrer le nombre de joueurs : ", MaxJoueurs);
                nombreValide = 0;
            }
        } while(!nombreValide);

        if (nombreJoueurs >= 2 && nombreJoueurs <= MaxJoueurs)
        {
            nbJoueursValides = 1;
            *nbJ = nombreJoueurs;
        }
        else
        {
            nbJoueursValides = 0;
            system("clear");
            printf("Rentres un nombre compris entre 2 et %i (inclus) !\n", MaxJoueurs);
            printf("Le nombre maximum de joueurs possible est %i. Veuillez entrer le nombre de joueurs : ", MaxJoueurs);
        }
    }


    printf("\n");
    printf("Veuillez entrer le nombre maximum d'erreurs possibles par un joueur avant qu'il ne commence à perdre des points : ");
        
    while(erreurValide != 1)
    {
        do                                                        
        {
            if (scanf("%i", &nbEmax) == 1)  
            {
                nombreValide = 1;
            } 
            else
            {
                while (getchar() != '\n');
                system("clear");
                printf("ERREUR !\n");
                printf("Rentres un nombre compris entre 1 et 99 (inclus) !\n");
                printf("Veuillez entrer le nombre maximum d'erreurs possibles par un joueur avant qu'il ne commence à perdre des points : ");
                nombreValide = 0;
            }
        } while(!nombreValide);

        if (nbEmax >= 1 && nbEmax <= 99)
        {
            erreurValide = 1;
            *Emax = nbEmax;
        }
        else
        {
            erreurValide = 0;
            system("clear");
            printf("Rentres un nombre compris entre 1 et 99 (inclus) !\n");
            printf("Veuillez entrer le nombre maximum d'erreurs possibles par un joueur avant qu'il ne commence à perdre des points : ");
        }
    }

    system("clear");
    for (int i = 0; i < *nbJ; i++)
    {
        saisieJoueurs(param+i, &i, &nombreOrdis);
        system("clear");
    }

    for(int i = 0; i < *nbJ; i++)
    {
        printf("Joueur n°%i :\n", (param+i)->noJoueur);
        printf("\tPseudo : %s\n", (param+i)->pseudo);
        if((param+i)->ordinateur == 1)
        {
            printf("\tOrdinateur : oui\n\n");
        }
        else
        {
            printf("\tOrdinateur : non\n\n");
        }
    }
}



































/*On mets dans la première case du tableau 00, ensuite 01, puis 02, etc jusqu'à atteindre la case égale au nombre de colonnes, où on remet le deuxième chiffre à 0
et on augmente le premier chiffre de 1. exemple pour L = 3 et C = 7 :
00, 01, 02, 03, 04, 05, 06, 10, 11, 12, 13, 14, 15, 16, 20, 21, 22, 23, 24, 25, 26
pour la case 20 par exemple je veux évidemment dire i = 2 et j = 0*/

void initEmplacements(int L, int C, S_Coordonees *Emplacements)
{
    int i = 0, j = 0;
    for (int k = 0; k < (L*C); k++)
    {
        Emplacements[k].valeurI = i;
        Emplacements[k].valeurJ = j;

        j += 1;
        if(j == C)
        {
            j = 0;
            i += 1;
        }
    }
}



































/*Permutation aléatoire : on créé une structure de type S_Coordonees nommée save, on choisit autant de fois qu'il y a des cartes 2 nombres aléatoires (rand1 et rand2), puis
on met dans save les valeurs de l'emplacement rand1, on met dans l'emplacement rand1 les valeurs de l'emplacement rand2, puis on met dans rand2 les valeurs de save
(qui étaient dans rand1)*/
void melangerEmplacements(int L, int C, S_Coordonees *Emplacements)
{
    srand(time(NULL));
    S_Coordonees save;
    for(int k = 0; k < (L*C); k++)
    {
        int rand1 = rand() % (L*C);
        int rand2 = rand() % (L*C);

        save.valeurI = Emplacements[rand1].valeurI;
        save.valeurJ = Emplacements[rand1].valeurJ;

        Emplacements[rand1].valeurI = Emplacements[rand2].valeurI;
        Emplacements[rand1].valeurJ = Emplacements[rand2].valeurJ;

        Emplacements[rand2].valeurI = save.valeurI;
        Emplacements[rand2].valeurJ = save.valeurJ;
    }
}



































/*On place les numéro de carte dans l'ordre dans lequel ils sont dans Emplacement (qui a donc été mélangé). Exemple :
Si emplacement commence par 20, 16, 04, 12, 14... alors on va mettre le 0 dans la case 20, le 1 dans les cases 16 et 04, le 2 dans les cases 12 et 14, etc...
On attribue également la place dans le tableau dans l'ordre (case 00 = place 0, case 01 = place 1, etc...), mais aussi on met retournee et associee à 0*/
void initPlateau(int L, int C, S_Coordonees *Emplacements, S_Carte **Plateau)
{
    initEmplacements(L, C, Emplacements);
    melangerEmplacements(L, C, Emplacements);

    Plateau[Emplacements[0].valeurI][Emplacements[0].valeurJ].numCarte = 0;
    int l = 1;

    for (int k = 1; k < (((L*C)+1)/2); k++)
    {
        Plateau[Emplacements[l].valeurI][Emplacements[l].valeurJ].numCarte = k;
        l++;
        Plateau[Emplacements[l].valeurI][Emplacements[l].valeurJ].numCarte = k;
        l++;
    }

    int i = 0, j = 0;
    for (int k = 0; k < (L*C); k++)
    {
        Plateau[i][j].placeTableau = k;
        Plateau[i][j].retournee = 0;
        Plateau[i][j].associee = 0;

        j += 1;
        if(j == C)
        {
            j = 0;
            i += 1;
        }
    }
}




































/*On fait pareil que dans le plateau mais sans placer les numéros de carte*/
void initMemoire(int L, int C, S_Carte **Memoire)
{
    int i = 0, j = 0;
    for (int k = 0; k < (L*C); k++)
    {
        Memoire[i][j].placeTableau = k;
        Memoire[i][j].retournee = 0;
        Memoire[i][j].associee = 0;

        j += 1;
        if(j == C)
        {
            j = 0;
            i += 1;
        }
    }
}





































void afficherPlateau(int L, int C, S_Carte **Plateau)
{
    system("clear");
    for (int i = 0; i < L; i++)
    {
        for (int j = 0; j < C; j++)
        {
            if (Plateau[i][j].associee == 0)
            {
                if (Plateau[i][j].retournee == 1)
                {
                    printf("\033[1;31m %2i \033[0m", Plateau[i][j].numCarte); //Ici \033[1;31m permet d'écrire en orange/rouge, et \033[0m permet de réécrire avec les valeurs par défaut (en blanc)
                }
                else
                {
                    printf(" %2i ", Plateau[i][j].placeTableau);
                }
            }
            else
            {
                printf("    ");
            }
    
            if (j < C - 1) 
            {
                printf("|");
            }
        }
        printf("\n");
        if (i < L - 1) 
        {
            for (int k = 0; k < C; k++)
            {
                printf("-----");
            }
        }
        printf("\n");
    }
}





































void selectCarte(S_Carte **Plateau, S_Carte **Memoire, int *I, int *J, int L, int C, S_Joueur *joueur, int *numJoueur)
{
    int reponse;
    int nombreValide = 0;

    do                                                           
    {
        if (scanf("%i", &reponse) == 1)  
        {
            if(reponse > ((L*C)-1) || reponse < 0)
            {
                system("clear");
                afficherPlateau(L, C, Plateau);
                printf("Rentres un numéro de carte qui n'est pas encore retournée, et qui est affiché sur le plateau !\n");
                printf("C'est à %s de jouer !\n", joueur[*numJoueur].pseudo);
                printf("Choisis un numéro de carte à retourner : ");
                nombreValide = 0;
            }
            else
            {
                for(int i = 0; i < L; i++)
                {
                    for(int j = 0; j < C; j++)
                    {
                        if(Plateau[i][j].placeTableau == reponse)
                        {
                            if(Plateau[i][j].associee == 1)
                            {
                                system("clear");
                                afficherPlateau(L, C, Plateau);
                                printf("Tu ne peux pas choisir cette carte car sa paire a déjà été trouvée !\n");
                                printf("C'est à %s de jouer !\n", joueur[*numJoueur].pseudo);
                                printf("Choisis un numéro de carte à retourner : ");
                            }
                            else
                            {
                                if(Plateau[i][j].retournee == 1)
                                {
                                    system("clear");
                                    afficherPlateau(L, C, Plateau);
                                    printf("Tu ne peux pas choisir cette car elle est déjà retournée !\n");
                                    printf("C'est à %s de jouer !\n", joueur[*numJoueur].pseudo);
                                    printf("Choisis un numéro de carte à retourner : ");
                                }
                                else
                                {
                                    nombreValide = 1;
                                    Plateau[i][j].retournee = 1;
                                    Memoire[i][j].retournee = 1;
                                    Memoire[i][j].numCarte = Plateau[i][j].numCarte;
                                    *I = i;
                                    *J = j;
                                }
                            }
                        }
                    }
                }
            }
        } 
        else
        {
            while (getchar() != '\n');
            system("clear");
            afficherPlateau(L, C, Plateau);
            printf("ERREUR !\n");
            printf("Rentres un numéro de carte qui n'est pas encore retournée !\n");
            printf("C'est à %s de jouer !\n", joueur[*numJoueur].pseudo);
            printf("Choisis un numéro de carte à retourner : ");
            nombreValide = 0;
        }
    } while(!nombreValide);
}

































/*On vérifie d'abord pour chaque carte si jamais on connait l'emplacement d'une carte portant le même numéro à un autre endroit si celles-ci ne sont ni associées ni retournées
Si jamais on ne connait aucune carte dont on connait l'emplacement de sa paire, alors on choisit une carte au hasard, qui n'est ni associee ni retournee*/


void selectCarteOrdi1(S_Carte **Plateau, S_Carte **Memoire, int L, int C, int *I, int *J)
{
    int nbSelection = 0;
    int rand1, rand2;
    int randValide = 0;

    for(int i = 0; i < L; i++)
    {
        for(int j = 0; j < C; j++)
        {
            for(int k = 0; k < L; k++)
            {
                for(int l = 0; l < C; l++)
                {
                    if(Memoire[i][j].associee == 0)
                    {
                        if(Memoire[i][j].numCarte == Memoire[k][l].numCarte)
                        {
                            if(Memoire[i][j].placeTableau != Memoire[k][l].placeTableau)
                            {
                                if(Memoire[i][j].retournee == 0)
                                {
                                    if(nbSelection == 0)
                                    {
                                        Plateau[i][j].retournee = 1;
                                        Memoire[i][j].retournee = 1;
                                        Memoire[i][j].numCarte = Plateau[i][j].numCarte;
                                        *I = i;
                                        *J = j;
                                        nbSelection = 1;
                                    }
                                }
                                else if(Memoire[k][l].retournee == 0)
                                {
                                    if(nbSelection == 0)
                                    {
                                        Plateau[k][l].retournee = 1;
                                        Memoire[k][l].retournee = 1;
                                        Memoire[k][l].numCarte = Plateau[k][l].numCarte;
                                        *I = k;
                                        *J = l;
                                        nbSelection = 1;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    if(nbSelection == 0)
    {
        srand(time(NULL));

        do
        {
            rand1 = rand() % L;
            rand2 = rand() % C;

            if(Memoire[rand1][rand2].associee == 0)
            {
                if(Memoire[rand1][rand2].retournee == 0)
                {
                    if(nbSelection == 0)
                    {
                        Plateau[rand1][rand2].retournee = 1;
                        Memoire[rand1][rand2].retournee = 1;
                        Memoire[rand1][rand2].numCarte = Plateau[rand1][rand2].numCarte;
                        *I = rand1;
                        *J = rand2;
                        nbSelection = 1;
                        randValide = 1;
                    }
                }
            }
        } while(randValide != 1);
    }
}


































/*On vérifie d'abord pour la carte précédemment retournée si jamais on connait l'emplacement d'une carte portant le même numéro à un autre endroit
Si jamais on ne connait aucune carte qui est la paire de la carte précédemment retournée, alors on choisit une carte au hasard, qui n'est ni associee ni retournee*/

void selectCarteOrdi2(S_Carte **Plateau, S_Carte **Memoire, int L, int C, int *I, int *J, int prevI, int prevJ)
{
    int nbSelection = 0;
    int rand1, rand2;
    int randValide = 0;

    for(int i = 0; i < L; i++)
    {
        for(int j = 0; j < C; j++)
        {
            if(Memoire[i][j].numCarte == Memoire[prevI][prevJ].numCarte)
            {
                if(Memoire[i][j].placeTableau != Memoire[prevI][prevJ].placeTableau)
                {
                    if(Memoire[i][j].associee == 0)
                    {
                        if(Memoire[i][j].retournee == 0)
                        {
                            if(nbSelection == 0)
                            {
                                Plateau[i][j].retournee = 1;
                                Memoire[i][j].retournee = 1;
                                Memoire[i][j].numCarte = Plateau[i][j].numCarte;
                                *I = i;
                                *J = j;
                                nbSelection = 1;
                            }
                        }
                    }
                }
            }
        }
    }

    if(nbSelection == 0)
    {
        srand(time(NULL));

        do
        {
            rand1 = rand() % L;
            rand2 = rand() % C;

            if(Memoire[rand1][rand2].associee == 0)
            {
                if(Memoire[rand1][rand2].retournee == 0)
                {
                    if(nbSelection == 0)
                    {
                        Plateau[rand1][rand2].retournee = 1;
                        Memoire[rand1][rand2].retournee = 1;
                        Memoire[rand1][rand2].numCarte = Plateau[rand1][rand2].numCarte;
                        *I = rand1;
                        *J = rand2;
                        nbSelection = 1;
                        randValide = 1;
                    }
                }
            }
        } while(randValide != 1);
    }
}


































/*On recherche un emplacement de carte qui n'est pas associee jusqu'à ce qu'on en trouve un, puis on permute le numéro de cette carte avec le numéro du Joker*/

void permutJoker(int L, int C, S_Carte **Plateau, int i, int j)
{
    int carteValide = 0;
    int random;
    S_Carte save;

    srand(time(NULL));

    do
    {
        random = rand() % (L*C);

        for(int y = 0; y < L; y++)
        {
            for(int z = 0; z < C; z++)
            {
                if(Plateau[y][z].placeTableau == random)
                {
                    if(Plateau[y][z].associee == 1)
                    {
                        carteValide = 0;
                    }
                    else
                    {
                        save.numCarte = Plateau[i][j].numCarte;
                        Plateau[i][j].numCarte = Plateau[y][z].numCarte;
                        Plateau[y][z].numCarte = save.numCarte;
                        
                        carteValide = 1;
                    }
                }
            }
        }
    } while (carteValide != 1);
}




































void afficheScores(S_Joueur *joueur, int nbJ)
{
    for (int i = 0; i < nbJ; i++)
    {
        printf("Joueur n°%i :\n", joueur[i].noJoueur);
        printf("\tPseudo : %s\n", joueur[i].pseudo);
        printf("\tScore : %i\n", joueur[i].score);
        if(joueur[i].ordinateur == 1)
        {
            printf("\tOrdinateur : oui\n\n");
        }
        else
        {
            printf("\tOrdinateur : non\n\n");
        }
    }
}





































void afficheParam(S_Joueur *joueur, int nbJ, int Emax)
{
    for (int i = 0; i < nbJ; i++)
    {
        printf("Joueur n°%i :\n", joueur[i].noJoueur);
        printf("\tPseudo : %s\n", joueur[i].pseudo);
        printf("\tScore : %i\n", joueur[i].score);
        printf("\tNombre d'erreurs : %i\n", joueur[i].nbErreur);
        if((Emax - joueur[i].nbErreur) < 0)
        {
            printf("\tNombre d'erreurs restantes avant pénalité : 0\n");
        }
        else
        {
            printf("\tNombre d'erreurs restantes avant pénalité : %i\n", Emax - joueur[i].nbErreur);
        }
        if(joueur[i].ordinateur == 1)
        {
            printf("\tOrdinateur : oui\n\n");
        }
        else
        {
            printf("\tOrdinateur : non\n\n");
        }
    }
}




































void gagnant(S_Joueur *joueur, int nbJ)
{
    int position = 1;

    //On trie le tableau des joueurs dans l'ordre décroissant de leur score
    for (int i = 0; i < nbJ - 1; i++) 
    {
        for (int j = i + 1; j < nbJ; j++) 
        {
            if (joueur[j].score > joueur[i].score) 
            {
                S_Joueur temp = joueur[i];
                joueur[i] = joueur[j];
                joueur[j] = temp;
            }
        }
    }

    //On écrie le classement des joueurs
    printf("Classement des joueurs :\n");
    printf("\t1er.  ");
    for (int i = 0; i < nbJ; i++) 
    {
        if (i != 0 && joueur[i].score != joueur[i - 1].score) 
        {
            printf("\t%ième. ", position);
        }
        else if(i != 0)
        {
            position = position - 1;
            printf("\t      ");
        }
        printf("Joueur n°%i - Pseudo : %s - Score : %i\n", joueur[i].noJoueur, joueur[i].pseudo, joueur[i].score);
        position++;
    }
    printf("\n");


    //On vérifie quel est le score maximum parmi le score de chaque joueur
    int maxScore = joueur[0].score;

    for (int i = 1; i < nbJ; i++) 
    {
        if (joueur[i].score > maxScore) 
        {
            maxScore = joueur[i].score;
        }
    }

    //On ecrit les joueurs ayant le score maximum
    printf("Le ou les vainqueurs sont :\n");
    for (int i = 0; i < nbJ; i++) 
    {
        if (joueur[i].score == maxScore) 
        {
            printf("\tJoueur %i : %s avec un score de %i\n", joueur[i].noJoueur, joueur[i].pseudo, joueur[i].score);
        }
    }
    printf("\tFélicitations à vous !\n");
}



































int partie(int L, int C, int nbJ, S_Joueur *joueur, S_Carte **Plateau, S_Carte **Memoire, int Emax)
{
    int nbCartesAssociées = 0;
    int exit = 0;
    int carteChoisieI, carteChoisieJ;
    int i, j;
    int i2, j2;

    do          //Tant que toutes les cartes ne sont pas associées
    {
        for (int numJoueur = 0; numJoueur < nbJ ; numJoueur++)  //On parcours tout les joueurs
        {
            afficherPlateau(L, C, Plateau);
            afficheParam(joueur, nbJ, Emax);

            if(joueur[numJoueur].ordinateur == 1)
            {
                selectCarteOrdi1(Plateau, Memoire, L, C, &i, &j);
            }
            else
            {
                printf("C'est à %s de jouer !\n", joueur[numJoueur].pseudo);
                printf("Choisis un numéro de carte à retourner : ");

                selectCarte(Plateau, Memoire, &i, &j, L, C, joueur, &numJoueur);
            }

            afficherPlateau(L, C, Plateau);

            //Si la carte retournée est un 0, on augmente le nombre d'erreur du joueur, il passe son tour, on retourne la carte et on permute le Joker
            if(Plateau[i][j].numCarte == 0)
            {
                printf("\n%s as retourné le Joker !\n", joueur[numJoueur].pseudo);
                sleep(2);
                joueur[numJoueur].nbErreur = joueur[numJoueur].nbErreur + 1;
                Plateau[i][j].retournee = 0;
                Memoire[i][j].retournee = 0;
                permutJoker(L, C, Plateau, i, j);
            }
            else
            {
                if(joueur[numJoueur].ordinateur == 1)
                {
                    selectCarteOrdi2(Plateau, Memoire, L, C, &i2, &j2, i, j);
                }
                else
                {
                    printf("C'est toujours à %s de jouer !\n", joueur[numJoueur].pseudo);
                    printf("Choisis un autre numéro de carte à retourner : ");

                    selectCarte(Plateau, Memoire, &i2, &j2, L, C, joueur, &numJoueur);
                }

                afficherPlateau(L, C, Plateau);

                //Si la carte retournée est un 0, on augmente le nombre d'erreur du joueur, il passe son tour, on retourne la carte et on permute le Joker
                if(Plateau[i2][j2].numCarte == 0)
                {
                    printf("\n%s as retourné le Joker !\n", joueur[numJoueur].pseudo);
                    sleep(2);
                    joueur[numJoueur].nbErreur = joueur[numJoueur].nbErreur + 1;
                    Plateau[i][j].retournee = 0;
                    Plateau[i2][j2].retournee = 0;
                    Memoire[i][j].retournee = 0;
                    Memoire[i2][j2].retournee = 0;
                    permutJoker(L, C, Plateau, i2, j2);
                }
                else
                {
                    /*Si les deux cartes retournées portent le même numéro on augmente le score du joueur de 1, on reset son nombre d'erreurs, il rejoue et on associe les cartes*/
                    if(Plateau[i][j].numCarte == Plateau[i2][j2].numCarte)
                    {
                        printf("\nBravo %s, tu as trouvé une paire !\n", joueur[numJoueur].pseudo);
                        sleep(2);
                        joueur[numJoueur].score = joueur[numJoueur].score + 1;
                        joueur[numJoueur].nbErreur = 0;
                        numJoueur = numJoueur - 1;
                        Plateau[i][j].associee = 1;
                        Plateau[i2][j2].associee = 1;
                        Memoire[i][j].associee = 1;
                        Memoire[i2][j2].associee = 1;
                        nbCartesAssociées += 2;

                        if(nbCartesAssociées == ((L*C)-1))  //Si toutes les cartes ont été associées on affiche les scores, le classement, et le ou les gagnants et on quitte la partie
                        {
                            system("clear");
                            afficheScores(joueur, nbJ);
                            gagnant(joueur, nbJ);

                            return 0;
                        }
                    }
                    else                                    //Sinon on retourne les cartes et on augmente le nombre d'erreurs du joueur
                    {
                        printf("\nHélas %s, ces deux cartes ne forment pas une paire.\n", joueur[numJoueur].pseudo);
                        sleep(3);
                        Plateau[i][j].retournee = 0;
                        Plateau[i2][j2].retournee = 0;
                        Memoire[i][j].retournee = 0;
                        Memoire[i2][j2].retournee = 0;
                        joueur[numJoueur].nbErreur = joueur[numJoueur].nbErreur + 1;
                    }
                }
            }

            if (joueur[numJoueur].nbErreur >= Emax)         //Si le nombre d'erreurs du joueur est égal au nombre d'erreurs maximum, on diminue son score de 1
            {
                joueur[numJoueur].score = joueur[numJoueur].score - 1;
            }
            
        }
    } while (nbCartesAssociées != ((L*C)-1));

    return 0;
}