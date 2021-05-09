#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>

char mine = 'X';
int n_mines;
char jeu[12][12];
char tableau[10][10];
int disponible[10][10];

void init()
{
    int i, j;
    for (i = 0; i < 12; i++)
        for (j = 0; j < 12; j++)
            jeu[i][j] = ' ';
}

void genereJeu(int ligne, int colonne)
{
    init();
    int k, i, j;
    srand(time(NULL));
    for (k = 0; k < 20; k++)
    {
        do
        {
            i = 1 + (rand() % 10);
            j = 1 + (rand() % 10);
        } while ((jeu[i][j] == mine) ||
                 ((i == ligne - 1) && (j == colonne - 1)) ||
                 ((i == ligne - 1) && (j == colonne)) ||
                 ((i == ligne - 1) && (j == colonne + 1)) ||
                 ((i == ligne) && (j == colonne - 1)) ||
                 ((i == ligne) && (j == colonne)) ||
                 ((i == ligne) && (j == colonne + 1)) ||
                 ((i == ligne + 1) && (j == colonne - 1)) ||
                 ((i == ligne + 1) && (j == colonne)) ||
                 ((i == ligne + 1) && (j == colonne + 1)));
        jeu[i][j] = mine;
    }

    int c = 0;
    for (i = 1; i <= 10; i++)
        for (j = 1; j <= 10; j++)
            if (jeu[i][j] != mine)
            {
                if (jeu[i - 1][j - 1] == mine)
                    c += 1;
                if (jeu[i - 1][j] == mine)
                    c += 1;
                if (jeu[i - 1][j + 1] == mine)
                    c += 1;
                if (jeu[i][j - 1] == mine)
                    c += 1;
                if (jeu[i][j + 1] == mine)
                    c += 1;
                if (jeu[i + 1][j - 1] == mine)
                    c += 1;
                if (jeu[i + 1][j] == mine)
                    c += 1;
                if (jeu[i + 1][j + 1] == mine)
                    c += 1;
                jeu[i][j] = c + '0';
                c = 0;
            }
}

int caseZero(int i, int j)
{
    tableau[i - 1][j - 1] = jeu[i][j];
    disponible[i - 1][j - 1] = 0;
    if (jeu[i][j] != '0')
        return 0;
    if ((i != 1) && (j != 1) && (disponible[i - 2][j - 2] == 1))
        caseZero(i - 1, j - 1);
    if ((i != 1) && (disponible[i - 2][j - 1] == 1))
        caseZero(i - 1, j);
    if ((i != 1) && (j != 10) && (disponible[i - 2][j] == 1))
        caseZero(i - 1, j + 1);
    if ((j != 1) && (disponible[i - 1][j - 2] == 1))
        caseZero(i, j - 1);
    if ((j != 10) && (disponible[i - 1][j] == 1))
        caseZero(i, j + 1);
    if ((j != 1) && (i != 10) && (disponible[i][j - 2] == 1))
        caseZero(i + 1, j - 1);
    if ((i != 10) && (disponible[i][j - 1] == 1))
        caseZero(i + 1, j);
    if ((i != 10) && (j != 10) && (disponible[i][j] == 1))
        caseZero(i + 1, j + 1);
}

void afficheJeu()
{
    int i, j;
    system("cls");
    printf("--------------------------------JEU DE DEMINEUR---------------------------------\n\n");
    printf("\n                       Mines trouv%ces: %d - 20\n", 130, n_mines);
    printf("   \n        1     2     3     4     5     6     7     8     9    10  ");
    printf("   \n      _____ _____ _____ _____ _____ _____ _____ _____ _____ _____ \n     |     |     |     |     |     |     |     |     |     |     |\n");
    for (i = 1; i <= 10; i++)
    {
        if (i != 10)
            printf(" %d ", i);
        else
            printf(" %d", i);
        for (j = 1; j <= 10; j++)
            printf("  |  %c", jeu[i][j]);
        if (i != 10)
            printf("  |\n     |_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|\n     |     |     |     |     |     |     |     |     |     |     |\n");
        else if (i == 10)
            printf("  |\n     |_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|\n\n");
    }
}

int playGame()
{
    char rejouer = '1';

    do
    {
        int i, j;

        for (i = 0; i < 10; i++)
            for (j = 0; j < 10; j++)
                tableau[i][j] = ' ';

        for (i = 0; i < 10; i++)
            for (j = 0; j < 10; j++)
                disponible[i][j] = 1;

        int choix_ligne, choix_colonne;
        int choix;
        int k = 0;
        n_mines = 0;

        do
        {
            system("cls");
            printf("--------------------------------JEU DE DEMINEUR---------------------------------\n\n");
            printf("\n                       Mines trouv%ces: %d - 20\n", 130, n_mines);
            printf("   \n        1     2     3     4     5     6     7     8     9    10  ");
            printf("   \n      _____ _____ _____ _____ _____ _____ _____ _____ _____ _____ \n     |     |     |     |     |     |     |     |     |     |     |\n");
            for (i = 0; i < 10; i++)
            {
                if (i != 9)
                    printf(" %d ", i + 1);
                else
                    printf(" %d", i + 1);
                for (j = 0; j < 10; j++)
                    printf("  |  %c", tableau[i][j]);
                if (i != 9)
                    printf("  |\n     |_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|\n     |     |     |     |     |     |     |     |     |     |     |\n");
                else if (i == 9)
                    printf("  |\n     |_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|\n\n");
            }

            if (n_mines == 20)
                break;

            printf("\n   choisi une ligne: ");
            scanf("%d", &choix_ligne);
            printf("\n   choisi une colonne: ");
            scanf("%d", &choix_colonne);

            if ((1 > choix_ligne) || (choix_ligne > 10) || (1 > choix_colonne) || (choix_colonne > 10) || disponible[choix_ligne - 1][choix_colonne - 1] == 0)
            {
                printf("\n   -Cette case  est indisponible!\n");
                system("pause");
                continue;
            }

            if (k == 0)
                genereJeu(choix_ligne, choix_colonne);

            k = 1;
            printf("\n   Choisi la case: appuyez sur 1\n");
            printf("   Marque une mine: appuyez sur 2\n");
            choix = getch();
            if (choix == '1')
            {
                if (jeu[choix_ligne][choix_colonne] == mine)
                {
                    afficheJeu();
                    printf("                vous avez perdu!\n\n");
                    break;
                }
                if (jeu[choix_ligne][choix_colonne] == '0')
                    caseZero(choix_ligne, choix_colonne);
                else
                {
                    tableau[choix_ligne - 1][choix_colonne - 1] = jeu[choix_ligne][choix_colonne];
                    disponible[choix_ligne - 1][choix_colonne - 1] = 0;
                }
            }
            else if (choix == '2')
            {

                if (jeu[choix_ligne][choix_colonne] != mine)
                {
                    afficheJeu();
                    printf("                vous avez perdu!\n\n");
                    break;
                }
                tableau[choix_ligne - 1][choix_colonne - 1] = mine;
                disponible[choix_ligne - 1][choix_colonne - 1] = 0;
                n_mines++;
            }
        } while (n_mines <= 20);

        if (n_mines == 20)
            printf("\n\n\n   BRAVO! Vous avez ganger\n");

        // Rejouer
        printf("\n   -Vous voulez rejouer ?: Appuyez 1\n");
        rejouer = getch();
    } while (rejouer == '1');

    return 0;
}

// La focntion main()
int main()
{
    playGame();

    return 0;
}