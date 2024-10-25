#include "Declarations.h"

int main()
{
    int choix = 0;
    int nombreValide = 0;

    printf("\nBonjour et bienvenue sur le Mémorix en langage C développé par AIT BAHA Said, BARRE Dorian, et CHOLLET Thomas !");

    while (choix != 3)
    {
        if (choix == 2)
        {
            system("clear");
            afficheRegles();
        }
        if (choix == 1)
        {
            system("clear");
            debutPartie();
            printf("\nPartie terminée !\n\n");
        }

        afficheMenu();
        
        do                                                           //Tant qu'on entre une réponse invalide, on va afficher un message d'erreur et redemander une réponse
        {
            if (scanf("%i", &choix) == 1)  
            {
                nombreValide = 1;
            } 
            else
            {
                while (getchar() != '\n');
                system("clear");
                printf("ERREUR !\n");
                printf("Veuillez rentrer un des nombres proposé !\n");
                afficheMenu();
                nombreValide = 0;
            }
        } while(!nombreValide);

        if (choix != 1 && choix != 2 && choix != 3)
        {
            system("clear");
            printf("Veuillez rentrer un des nombres proposé !\n");
            if (choix == 2)
            {
                afficheRegles();
            }
        }
        
    }

    printf("\n");
    printf("Merci d'avoir joué !\n\n");

    return 0;
}