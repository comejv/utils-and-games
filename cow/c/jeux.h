#ifndef __JEUX_H__
#define __JEUX_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "affiche_vache.h"

// Devine un nombre entre 0 et 100
void devine_nombre(int i, int s, char *yeux, char *pis, char *langue, int *animation)
{
    int g;
    int n = 1;
    char prompt[50];
    char r;

    // Tant qu'on a pas trouvé le bon nombre
    while (r != '=')
    {
        // On ignore le getchar enter
        if (r != '\n')
        {
            // On devine au milieu des bornes
            g = (i + s) / 2;
            snprintf(prompt, 50, "Je devine %i, est-ce +, - ou = ?", g);
            afficher_vache_defaut(yeux, pis, langue, prompt, *animation);
            scanf("%s", &r);

            switch (r)
            {
            case '+':
                // Si plus grand, on augmente la borne inf
                n++;
                i = g;
                break;
            case '-':
                // Si plus petit on diminue la borne sup
                n++;
                s = g;
                break;
            case '=':
                break;
            default:
                puts("Caractère invalide. Réessayez.");
            }
        }
    }
    printf("Nombre deviné en %i essais !\nMerci d'avoir joué.\n", n);
    exit(0);
}

// Pour faire afficher un texte lettre par lettre
void lecture(char *yeux, char *pis, char *text)
{
    int s_length = strlen(text);
    char buff_text[s_length];
    for (int i = 0; i < s_length; i++)
    {
        // Redondant avec l'option animation mais plus simple que de passer le temps
        // de pause en argument.
        strncat(buff_text, text + i, 1);
        afficher_vache_defaut(yeux, pis, &text[i], buff_text, 0);
        nanosleep((const struct timespec[]){{0, 500000000L}}, NULL);
    }
    exit(0);
}

// Renvoie un entier aléatoire entre 0 et max
int entier_aleatoire(int max)
{
    static int a = 0;

    if (a == 0)
    {
        srand(time(NULL));
        a = 1;
    }
    return (rand() % max);
}

// Automate interactif
void tamagoshi()
{
    // Var affichage vache
    char yeux = 'o';
    char pis = 'w';
    char langue = ' ';
    char text[250] = "Bonjour ! Vous etes mon nouveau gardien ? Le precedent a fuit la queue entre les jambes... Vous pouvez quitter le jeu en entrant 'q' a tout moment. Enfin treve de bavarderies, j'ai faim ! Combien de bottes de foin puis-je manger ?";

    // Var automate
    int sante = 5;
    int stock = 5;
    int n = 0; // Foin donné par user
    int c = 0; // Compte tours

    // Affichage des consignes
    afficher_vache_defaut(&yeux, &pis, &langue, text, 1);
    printf("\x1b[1FStocks = %i\x1b[1E", stock);
    printf("\x1b[5mEntrez un montant...\x1b[25m");
    n = getchar() - 48;
    getchar(); // Pour ignorer le \n de ENTER

    // Tant que la vache est vivante
    while (sante > 0 && sante < 10 && n != 65)
    {
        // On regarde l'écart avec la santé de départ
        switch (abs(sante - 5))
        {
        case 0:
            strcpy(text, "Bonne decision, je me sens tres bien ! Dites moi acombien de bottes de foin j'ai le droit.");
            yeux = 'n';
            break;
        case 1:
            strcpy(text, "Je ne me sens pas si mal ! Qu'est-ce que je mange maintenant ?");
            yeux = 'o';
            break;

        case 2:
        case 3:
            strcpy(text, "Je ne me sens pas au mieux de ma forme... Est-ce que je devrais manger encore ?");
            yeux = '-';
            break;
        case 5:
            strcpy(text, "Je ne me sens vraiment pas bien ! Qu'est-ce que je fait ?");
            yeux = '!';
            break;
        }

        // A n'afficher qu'à partir du tour 1
        if (c != 0)
        {
            afficher_vache_defaut(&yeux, &pis, &langue, text, 1);
            printf("\x1b[1FStocks = %i\x1b[1E", stock);
            printf("\x1b[5mEntrez un montant...\x1b[25m");
            n = getchar() - 48;
            getchar(); //? Pour récupérer le \n
        }

        // On enlève la quantité demandé
        stock -= n;
        // Les stocks augmentent aléatoirement
        stock += entier_aleatoire(3);
        // On nourrit la vache
        sante += n;
        // Sa digestion est aléatoire
        sante -= entier_aleatoire(3);
        // Tour plus 1
        c++;
    }

    // Si on entre le caractère f on met fin au jeu
    if (n == 65)
    {
        yeux = 'u';
        pis = 'w';
        langue = ' ';
        strcpy(text, "Vous partez, comme tous les autres...");
        afficher_vache_defaut(&yeux, &pis, &langue, text, 1);
        printf("Vous avez mis fin au jeu apres %i tours. Votre vache avait un score fitness de %i et il restait %i bottes de foin.\n", c, sante, stock);
        exit(0);
    }

    // Affichage de la dernière vache quand elle meurt
    yeux = 'x';
    pis = '-';
    langue = 'U';
    strcpy(text, "Baaahh...");
    afficher_vache_defaut(&yeux, &pis, &langue, text, 1);
    // Si la vache est morte de faim
    if (sante <= 0)
        printf("Votre vache est morte de faim apres %i tours ! Il vous restait %i bottes de foin.\n", c, stock);
    // Si elle a été trop nourrie
    else if (sante >= 10)
        printf("Votre vache est morte de surpoid apres %i tours ! Il vous restait %i bottes de foin.\n", c, stock);

    exit(0);
}

#endif
