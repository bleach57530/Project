#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h> // Inclure la bibliothèque pour sleep()
#define SUEURS "\U0001F613"

void Jeux1(int *score) {
  srand(time(NULL));
  int a = rand() % 10 + 1;
  int b = rand() % 10 + 1;
  int c = rand() % 10 + 1;
  int Bogoss;
  printf("---------------------------------------\n");
  printf("\e[1;34mJeu de la suite mystère\n\e[0m");
  printf("---------------------------------------\n");

  printf("\e[0;36ma = %d\nb = %d\nc = %d \n\e[0m", a, b, c);
  int res = c;
  printf("---------------------------------------\n");
  printf("\e[0;32mTerme 1 : %d\n\e[0m", c);
  for (int i = 0; i < 2; i++) {
    int Terme = a * res + b;
    res = Terme;
    printf("\e[0;32mTerme %d : %d \n\e[0m", i + 2, Terme);
  }
  printf("---------------------------------------\n");
  printf("Trouve le 4ème terme de la suite en moins de 30 secondes\n");
  printf("---------------------------------------\n");

  int Terme = a * res + b;
  Bogoss = Terme;

  time_t debut, fin;
  time(&debut);

  int resultat;
  scanf("%d", &resultat);

  time(&fin);

  double temps_ecoule =
      difftime(fin, debut); // Calcule le temps écoulé en secondes
  printf("---------------------------------------\n");
  printf("\e[0;35mTemps écoulé : %.2f secondes\n\e[0m", temps_ecoule);
  printf("---------------------------------------\n");

  if (resultat != Bogoss || temps_ecoule > 30) {
    printf(
        "\e[1;31mLe résultat n'est pas le bon ou le temps est écoulé.\n\e[0m");
    *score += 31;

  } else {
    printf("\e[1;32mT'as trouvé le résultat qui est %d en %.2f secondes\n\e[0m",
           Bogoss, temps_ecoule);
    *score += (int)temps_ecoule;
  }
}

void Jeux2(int *score) {
  srand(time(NULL));
  int resultat = rand() % 1000 + 1;
  int NbeEssais = 0;
  int MaxTent = 10;
  int tentative;
  printf("---------------------------------------\n");
  printf("Jeu de devinette\n");
  printf("Devine un nombre compris entre 1 et 1000\n");
  printf("---------------------------------------\n");

  while (NbeEssais < MaxTent) {
    printf("Nombre de tentatives  %d : \n", NbeEssais + 1);
    printf("La réponse est : %d\n", resultat);
    printf("Saisir le nombre : ");
    scanf("%d", &tentative);

    if (tentative > 1000) {
      printf("\e[0;31mLe nombre saisi a dépassé la limite !\n\e[0m");
      printf("---------------------------------------\n");
      printf("Saisir le nombre : ");
      scanf("%d", &tentative);
    }

    if (tentative < resultat) {
      printf("\e[0;35mC'est plus grand !\n\e[0m");
      printf("---------------------------------------\n");
    } else if (tentative > resultat) {
      printf("\e[0;34mC'est plus petit !\n\e[0m");
      printf("---------------------------------------\n");
    } else {
      printf("\e[1;32mBien joué t'es trop fooort, le nombre est %d \n\e[0m",
             resultat);
      *score += NbeEssais + 1;
      return; // Sort du jeu lorsque le nombre est deviné
    }
    NbeEssais++;
  }

  printf("\e[1;31mFrérot t'es nul ou quoi ?? Le nombre était %d.\n\e[0m",
         resultat);
  *score += 11;
}

void Jeux3(int *score) {
  printf("---------------------------------------\n");
  printf("\e[1;32mLe MasterMind\n\e[0m");
  printf("---------------------------------------\n");
  printf("\e[1;36mTu dois retrouver la combinaison de voyelles. Bonne chance !\n\e[0m");
  printf("---------------------------------------\n");

  int bp = 0;
  int mp = 0;
  int compeur = 0;
  char voyelles[] = {'A', 'E', 'I', 'O', 'U', 'Y'};
  srand(time(NULL));
  char suite[4];

  for (int i = 0; i < 4; i++) {
    char voyelle;

    do {
      voyelle = voyelles[rand() % 6];
    } while (strchr(suite, voyelle) != NULL);

    suite[i] = voyelle;
  }

  // Afficher la combinaison générée
  for (int i = 0; i < 4; i++) {
    printf("%c ", suite[i]);
  }
  printf("\n");



  time_t debut, fin;
  time(&debut);

  while (compeur < 10) {
    char resultat[5];
    printf("Saisir ta proposition : ");
    scanf("%s", resultat);

    bp = 0;
    mp = 0;

    for (int i = 0; i < 4; i++) {
      for (int j = 0; j < 4; j++) {
        if (suite[j] == resultat[i]) {
          if (j == i) {
            bp++;
          } else {
            mp++;
          }
          break;
        }
      }
    }

    printf("---------------------------------------\n");
    printf("\e[1;38;5;208m%d mal placée(s)\n\e[0m", mp);
    printf("\e[1;32m%d bien placée(s)\n\e[0m", bp);
    printf("---------------------------------------\n");

    if (bp == 4) {
      printf("Bien joué, t'as trouvé la combinaison !\n");

       time(&fin);
      double temps_ecoule =
      difftime(fin, debut); // Calcule le temps écoulé en secondes
      printf("---------------------------------------\n");
      printf("\e[0;35mTemps écoulé : %.2f secondes\n\e[0m", temps_ecoule);
      printf("---------------------------------------\n");
      *score += compeur + 1;
      return;
    }

    compeur++;
  }

  printf("Désolé, tu as atteint le maximum d'essais. La combinaison était : ");
  for (int i = 0; i < 4; i++) {
    printf("%c ", suite[i]);
  }
  printf("\n");

    time(&fin);
  double temps_ecoule =
      difftime(fin, debut); // Calcule le temps écoulé en secondes
      printf("---------------------------------------\n");
      printf("\e[0;35mTemps écoulé : %.2f secondes\n\e[0m", temps_ecoule);
      printf("---------------------------------------\n");
}

int main(void) {

  int scoreTotal = 0;

  int choix;
  printf("\e[1;30m---------------------------------------\n\e[0m");
  printf("\e[1;38;2;200mBienvenueeeee !!!!!!!!!!!!!!!!!!!!!!\e[0m ");
  printf("%s\n", SUEURS);
  printf("\e[1;30m---------------------------------------\n\e[0m");

  while (choix != 4) {
    printf("Choisis un jeu :\n");
    printf("\e[1;34m1/ Suite mystère\n\e[0m");
    printf("\e[1;35m2/ Le nombre caché\n\e[0m");
    printf("\e[1;32m3/ MasterMind\n\e[0m");
    printf("\e[1;31m4/ Quitter\n\e[0m");
    printf("\e[1;30m---------------------------------------\n\e[0m");
    printf("Votre choix :\n");

    scanf("%d", &choix);

    switch (choix) {
    case 1:
      Jeux1(&scoreTotal);
      break;
    case 2:
      Jeux2(&scoreTotal);
      break;
    case 3:
      Jeux3(&scoreTotal);
      break;
    case 4:
      printf("Merci d'avoir joué ! Ton score total est de %d\n", scoreTotal);
      break;
    default:
      printf("Choix invalide. Choisis un jeu valide.\n");
    }

    printf("---------------------------------------\n");
    printf("\e[0;30mVotre score total est de %d\n\e[0m", scoreTotal);
    printf("---------------------------------------\n");
  }

  return 0;
}
