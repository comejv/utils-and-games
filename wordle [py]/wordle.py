from random import randint
from unidecode import unidecode
from dic import dic_accents

# Support des couleurs ANSI dans windows
from os import system
system("")

COLOR = {
    "RED": "\x1b[91m",
    "GREEN": "\x1b[92m",
    "BLUE": "\x1b[94m",
    "BOLD": "\x1b[1m",
    "BOLDR": "\x1b[1;91m",
    "BOLDG": "\x1b[1;92m",
    "ENDC": "\x1b[0m"
}


def input_valide(secret: str, tour: int):
    """Prend une entrée standard et la renvoie quand elle satisfait les conditions, sauf si "stop"

    Args:
        secret (str): mot à deviner

    Returns:
        tuple: mot sans accents et mot avec accents du dic
    """
    prop = unidecode(input(f"Proposition {tour}/6 :\n"))

    while (not(prop in dic_sans_accents) or len(prop) != len(secret)) and prop != "stop":
        if not(prop in dic_sans_accents):
            prop = input(
                "Votre mot n'est pas dans notre dictionnaire, réessayez :\n")
        elif len(prop) < len(secret):
            prop = input("Mot trop court :\n")
        elif len(prop) > len(secret):
            prop = input("Mot trop long :\n")
    if prop == "stop":
        return "stop"
    else:
        print("\x1b[2F")
        return (list(prop), list(dic_accents[dic_sans_accents.index(prop)]))


def output(secret: list, prop: list):
    """Donne les indices pour chaque lettre

    Args:
        secret (list): mot secret à deviner
        prop (list): mot proposé par le joueur

    Returns:
        output (list): rouge mauvaise lettre, bleu mauvais emplacement, vert bon emplacement
    """
    output = []
    secret_sans_accent = [unidecode(l) for l in secret]
    for i in range(len(secret)):
        if unidecode(secret[i]) == unidecode(prop[i]):
            output.append(COLOR["GREEN"] + "◉" + COLOR["ENDC"])
        elif unidecode(prop[i]) in secret_sans_accent:
            output.append(COLOR["BLUE"] + "◉" + COLOR["ENDC"])
        else:
            output.append(COLOR["RED"] + "◉" + COLOR["ENDC"])
    return output


def main():
    """Exécute une partie

    Args:
        mot_secret (str): mot à deviner

    Returns:
        jeu (str): 'oui' pour rejouer, autre pour quitter
    """
    mot_secret_accents = dic_accents[randint(0, len(dic_accents)-1)]
    mot_secret = unidecode(mot_secret_accents)

    mot_secret_accents = list(mot_secret_accents)
    mot_secret = list(mot_secret)

    print("Votre mot est composé de ", len(mot_secret), " lettres.\n")

    for chance in range(1, 7):
        prop_mot = input_valide(mot_secret, chance)

        if prop_mot == "stop":
            return "non"

        if prop_mot[0] == mot_secret:
            print(COLOR["GREEN"] + "\nBravo !" + COLOR["ENDC"], "Vous avez deviné le mot " +
                  COLOR["BOLDG"] + ''.join(map(str, mot_secret_accents)) + COLOR["ENDC"], ".")
            return input("\nPour rejouer entrez 'oui'.\n")

        indices = output(mot_secret, prop_mot[0])

        print(COLOR["BOLD"] + ' '.join(map(str, prop_mot[1])))
        print(*indices, sep=' ')
    print(COLOR["RED"] + "\nDomage, " + COLOR["ENDC"] + "vous avez épuisé votre nombre de chances.\nLe mot était ",
          COLOR["BOLDR"] + ' '.join(map(str, mot_secret_accents)) + COLOR["ENDC"])
    return input("Pour rejouer entrez 'oui'.\n")


dic_sans_accents = []
for e in dic_accents:
    dic_sans_accents.append(unidecode(e))

print(COLOR["BOLD"] + "Trouvez le mot secret en proposant des mots de même taille !" + COLOR["ENDC"] +
      "\nUne lettre est absente du mot secret si marquée" + COLOR["RED"] + " rouge" + COLOR["ENDC"] +
      ", présente mais au mauvais emplacement avec" + COLOR["BLUE"] + " bleu" + COLOR["ENDC"] +
      ", et au bon emplacement avec" + COLOR["GREEN"] + " vert" + COLOR["ENDC"] + ".\nEntrez 'stop' à tout moment pour quitter le jeu.",
      "\nBonne chance !")


jeu = 'oui'
while jeu == 'oui':
    try:
        jeu = main()
    except KeyboardInterrupt:
        print("\rA bientôt !")
        exit(1)
print("A bientôt !")
