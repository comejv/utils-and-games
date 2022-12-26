#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Lecture à partir d'un fichier
char read_from_file(char *ciphertext)
{
    char path[40];

    // Lecture du chemin d'accès
    if (fgets(path, 40, stdin) == NULL)
    {
        fputs("Erreur lors de la lecture du chemin d'accès.\n", stderr);
        return 1;
    }

    // Suppression du retour chariot
    path[strcspn(path, "\n")] = '\0';

    // Ouverture du fichier
    FILE *cipher_file = fopen(path, "r");
    if (cipher_file == NULL)
    {
        perror(path);
        exit(1);
    }

    // Lecture du texte chiffré
    char c;
    int n = 0;
    while ((c = fgetc(cipher_file)) != EOF)
    {
        ciphertext[n++] = c;
    }
    ciphertext[n] = '\0';

    // Fermeture du fichier
    fclose(cipher_file);
}

// Analyse fréquentielle du texte chiffré
int analyse_frequence(char *cipher)
{
    int freq[26] = {0};

    for (int i = 0; i < strlen(cipher); i++)
    {
        freq[cipher[i] - 'a']++;
    }

    int max = 0;
    int max_i = 0;
    for (int i = 0; i < 26; i++)
    {
        if (freq[i] > max)
        {
            max = freq[i];
            max_i = i;
        }
    }

    printf("La lettre la plus fréquente est : %c\n", max_i + 'a');
    int shift = max_i + 'a' - 'e';

    return shift;
}

// Déchiffrement du texte chiffré
void dechiffrement(char *cipher, int shift, char *plain)
{
    for (int i = 0; i < strlen(cipher); i++)
    {
        if (cipher[i] >= 'a' && cipher[i] <= 'z')
        {
            plain[i] = (cipher[i] - 'a' + 26 - shift) % 26 + 'a';
        }
        else if (cipher[i] >= 'A' && cipher[i] <= 'Z')
        {
            plain[i] = (cipher[i] - 'A' + 26 - shift) % 26 + 'A';
        }
        else
        {
            plain[i] = cipher[i];
        }
    }
}

int main(int argc, char *argv[])
{
    char ciphertext[1024];
    char plaintext[1024];

    printf("\x1b[H\x1b[2J\x1b[4mBienvenue dans le déchiffreur de César.\x1b[24m\n"
           "Veuillez préciser le chemin d'accès au texte chiffré.\n");

    read_from_file(ciphertext);

    printf("Le texte chiffré est :\n%s\n\n", ciphertext);

    // Analyse fréquentielle du texte chiffré
    int shift = analyse_frequence(ciphertext);
    printf("\x1b[1mLe décalage est probablement de : %d\x1b[0m\n\n", shift);

    // Déchiffrement du texte chiffré
    dechiffrement(ciphertext, shift, plaintext);

    printf("Le texte déchiffré est :\n%s\n", plaintext);

    return 0;
}
