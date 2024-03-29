from random import randint
from time import sleep
from dic import dic_accents
from sys import stderr, executable, exit
from subprocess import check_call, CalledProcessError

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


def clear():
    print("\x1b[2J\x1b[H")


def wprint(text, *args, **kwargs) -> None:
    print(COLOR["BOLD"] + "Warning :", text +
          COLOR["ENDC"], *args, file=stderr, **kwargs)


def binput(prompt) -> bool:
    str_input = input(COLOR['BOLD'] + prompt + COLOR['ENDC'])
    bool_input = ['true', '1', 't', 'y', 'yes', 'i',
                  'false', '0', 'f', 'n', 'no', 'p']

    while str_input not in bool_input:
        str_input = input("\x1b[1F\x1b[K" +
                          COLOR["BOLD"] + prompt + COLOR["ENDC"])
    if str_input.lower() in bool_input[:6]:
        return True
    return False


clear()
try:
    from unidecode import unidecode
except ImportError:
    wprint("Unidecode module necessary but not found.")
    b_install = binput(
        "Do you want to install it with pip or quit this game ?\n(y : install / n : quit))")
    if b_install is True:
        try:
            check_call(
                [executable, "-m", "pip", "install", "unidecode"])
        except CalledProcessError:
            wprint("Unable to install unidecode.")
            print("Quitting...")
            exit(1)
        from unidecode import unidecode
        print("Unidecode installed.")
        sleep(1)
        clear()

    else:
        wprint("Unidecode is necessary to run this game.")
        print("Quitting...")
        exit(1)


def input_valide(secret: str, tour: int) -> tuple:
    """Prend une entrée standard et la renvoie quand elle satisfait les conditions, sauf si "stop"

    Args:
        secret (str): mot à deviner

    Returns:
        tuple: mot sans accents et mot avec accents du dic
    """
    prop = unidecode(input(f"Proposition {tour}/6 :\n")).lower()
    prop_in_dic = prop in dic_sans_accents
    while (not prop_in_dic or len(prop) != len(secret)) and prop != "stop":
        if not prop_in_dic:
            prop = unidecode(input(
                "Votre mot n'est pas dans notre dictionnaire, réessayez :\n")).lower()
        elif len(prop) < len(secret):
            prop = unidecode(input("Mot trop court :\n")).lower()
        elif len(prop) > len(secret):
            prop = unidecode(input("Mot trop long :\n")).lower()
        prop_in_dic = prop in dic_sans_accents

    if prop == "stop":
        return "stop"
    else:
        print("\x1b[2F")
        return (list(prop), list(dic_accents[dic_sans_accents.index(prop)]))


def output(secret: list, prop: list) -> list:
    """Donne les indices pour chaque lettre

    Args:
        secret (list): mot secret à deviner
        prop (list): mot proposé par le joueur

    Returns:
        output (list): rouge mauvaise lettre, bleu mauvais emplacement, vert bon emplacement
    """
    output = []
    secret_sans_accent = [letter for letter in secret]
    for i in range(len(secret)):
        if prop[i] == secret_sans_accent[i]:
            output.append(COLOR["GREEN"] + "◉" + COLOR["ENDC"])
            secret_sans_accent[i] = "*"
        elif prop[i] in secret_sans_accent:
            output.append(COLOR["BLUE"] + "◉" + COLOR["ENDC"])
            secret_sans_accent[i] = "*"
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
      ", et au bon emplacement avec" + COLOR["GREEN"] + " vert" + COLOR["ENDC"] +
      ".\nEntrez 'stop' à tout moment pour quitter le jeu.",
      "\nBonne chance !")


jeu = 'oui'
while jeu == 'oui':
    try:
        jeu = main()
    except KeyboardInterrupt:
        print("\rA bientôt !")
        exit(1)
print("A bientôt !")
