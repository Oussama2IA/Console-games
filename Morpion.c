#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

// structure qui stocke le nom et le score du joueur
typedef struct Joueur
{
    char nom[20];
    int score;
} Joueur;

// La fonction qui va démarer le jeu
int playjeu(char mode)
{
    if (mode != '1' && mode != '2')
        return 0;

    // Les informations du premier joueur
    Joueur P1;
    P1.score = 0;
    printf(" Joueur 1: saisie ton nom: ");
    scanf("%s", P1.nom);

    // les informations du deuxième joueur (qui est l'ordinateur pour le mode 1)
    Joueur P2;
    P2.score = 0;
    if (mode == '1')
        strcpy(P2.nom, "Ordinateur");
    else if (mode == '2')
    {
        printf(" Joueur 2: saisie ton nom: ");
        scanf("%s", P2.nom);
    }

    // Pour rejouer si le jeu est terminé
    char rejouer = '1';

    do
    {
        char jeu[3][3] = {{' ', ' ', ' '}, {' ', ' ', ' '}, {' ', ' ', ' '}}; // La form du jeu (initialement vide)
        int choix;                                                            // La case que le joueur va choisir pour la remplir par 'X' ou par 'O'
        int disponible[3][3] = {{1, 1, 1}, {1, 1, 1}, {1, 1, 1}};             // Pour savoir si la case choisie est disponible ou non
        int c = 1;                                                            // Un nombre pour savoir le tour de quel joueur
        int k = 0;
        int i, j;

        do
        {
            system("cls"); // Pour effacer l'écran chaque fois et le remplir à nouveau
            printf("--------------------------------JEU DE MORPION---------------------------------\n\n");
            printf(" -%s: X \t-%s: O\n", P1.nom, P2.nom);
            printf(" -score: %d \t-score: %d\n", P1.score, P2.score);

            // Traçage du tableau
            printf("   \n    _______ _______ _______ \n   |       |       |       |\n");
            for (i = 0; i < 3; i++)
            {
                for (j = 0; j < 3; j++)
                    printf("   |   %c", jeu[i][j]);
                if (i != 2)
                    printf("   |\n   |_______|_______|_______|\n   |       |       |       |\n");
                else
                    printf("   |\n   |_______|_______|_______|\n\n");
            }

            // Les conditions pour gagner pour le premier joueur
            if ((jeu[0][0] == 'X' && jeu[0][0] == jeu[0][1] && jeu[0][1] == jeu[0][2]) ||
                (jeu[1][0] == 'X' && jeu[1][0] == jeu[1][1] && jeu[1][1] == jeu[1][2]) ||
                (jeu[2][0] == 'X' && jeu[2][0] == jeu[2][1] && jeu[2][1] == jeu[2][2]) ||
                (jeu[0][0] == 'X' && jeu[0][0] == jeu[1][0] && jeu[1][0] == jeu[2][0]) ||
                (jeu[0][1] == 'X' && jeu[0][1] == jeu[1][1] && jeu[1][1] == jeu[2][1]) ||
                (jeu[0][2] == 'X' && jeu[0][2] == jeu[1][2] && jeu[1][2] == jeu[2][2]) ||
                (jeu[0][0] == 'X' && jeu[0][0] == jeu[1][1] && jeu[1][1] == jeu[2][2]) ||
                (jeu[0][2] == 'X' && jeu[0][2] == jeu[1][1] && jeu[1][1] == jeu[2][0]))
            {
                printf("\n   %s gangne!", P1.nom);
                P1.score += 1;
                break;
            }

            // Les conditions pour gagner pour le deuxième joueur
            if ((jeu[0][0] == 'O' && jeu[0][0] == jeu[0][1] && jeu[0][1] == jeu[0][2]) ||
                (jeu[1][0] == 'O' && jeu[1][0] == jeu[1][1] && jeu[1][1] == jeu[1][2]) ||
                (jeu[2][0] == 'O' && jeu[2][0] == jeu[2][1] && jeu[2][1] == jeu[2][2]) ||
                (jeu[0][0] == 'O' && jeu[0][0] == jeu[1][0] && jeu[1][0] == jeu[2][0]) ||
                (jeu[0][1] == 'O' && jeu[0][1] == jeu[1][1] && jeu[1][1] == jeu[2][1]) ||
                (jeu[0][2] == 'O' && jeu[0][2] == jeu[1][2] && jeu[1][2] == jeu[2][2]) ||
                (jeu[0][0] == 'O' && jeu[0][0] == jeu[1][1] && jeu[1][1] == jeu[2][2]) ||
                (jeu[0][2] == 'O' && jeu[0][2] == jeu[1][1] && jeu[1][1] == jeu[2][0]))
            {
                printf("\n   %s gagne!", P2.nom);
                P2.score += 1;
                break;
            }

            if (k == 9)
                break;

            // Le tour du premier joueur
            if (c == 1)
            {
                printf("\n  ---Les cases sont num%Crot%ces de 1 %c 9---\n", 130, 130, 133);
                printf("\n   -%s: choisi une case disponible: ", P1.nom);
                scanf("%d", &choix);
                j = (choix - 1) % 3;
                i = ((choix - 1) / 3) % 3;
                if (choix >= 1 && choix <= 9 && disponible[i][j] == 1)
                {
                    jeu[i][j] = 'X';
                    disponible[i][j] = 0;
                }
                else
                {
                    printf("\n   -Cette case  est idisponible!\n");
                    system("pause");
                    continue;
                }
                c = 2;
            }

            // Le tour du deuxième joueur
            else
            {
                // Pour le premier mode (vs l'ordinateur)
                if (mode == '1')
                {
                    srand(time(NULL));
                    do
                    {
                        choix = 1 + (rand() % 9); // Pour générer un nombre aléatoire entre 1 et 9
                        j = (choix - 1) % 3;
                        i = ((choix - 1) / 3) % 3;
                    } while (disponible[i][j] == 0);
                    jeu[i][j] = 'O';
                    disponible[i][j] = 0;
                }

                // Pour le deuxième mode (deux joueurs)
                else if (mode == '2')
                {
                    printf("\n  ---Les cases sont num%Crot%ces de 1 %c 9---\n", 130, 130, 133);
                    printf("\n   -%s: choisi une case disponible: ", P2.nom);
                    scanf("%d", &choix);
                    j = (choix - 1) % 3;
                    i = ((choix - 1) / 3) % 3;
                    if (choix >= 1 && choix <= 9 && disponible[i][j] == 1)
                    {
                        jeu[i][j] = 'O';
                        disponible[i][j] = 0;
                    }
                    else
                    {
                        printf("\n   -Cette case  est idisponible!\n");
                        system("pause");
                        continue;
                    }
                }
                c = 1;
            }
            k++;

        } while (k <= 9);

        // Rejouer
        printf("\n   -Vous voulez rejouer ?: Appuyez sur 1");
        rejouer = getch();

    } while (rejouer == '1');

    // Le score final
    system("cls");
    printf("--------------------------------JEU DE MORPION---------------------------------\n\n");
    printf("\n\t\tMerci pour jouer!\n\n");
    printf("  Le score final: \n score de %s: %d \tscore de %s: %d\n\n", P1.nom, P1.score, P2.nom, P2.score);
    system("pause");
}

// La fonction main
int main()
{
    // Le mode du jeu
    printf("--------------------------------JEU DE MORPION---------------------------------\n\n");
    printf("  Choisir le mode du jeu: \n\n");
    printf("1. un joueur vs l'ordinateur: Appuyer sur le bouton 1\n");
    printf("2. deux joueurs: Appuyer sur le bouton 2\n\n");
    char mode = getch(); // getch() est une fonction existe dans conio.h qui permet de stocker le bouton appuyé sur le clavier
    playjeu(mode);

    return 0;
}