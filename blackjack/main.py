from random import randint, shuffle

# Cartes et stratégie bots
CARD_DIC = {"AS": "As de Pique", "2S": "Deux de Pique", "3S": "Trois de Pique", "4S": "Quatre de Pique", "5S": "Cinq de Pique", "6S": "Six de Pique",
            "7S": "Sept de Pique", "8S": "Huit de Pique", "9S": "Neuf de Pique", "0S": "Dix de Pique", "JS": "Valet de Pique", "QS": "Dame de Pique", "KS": "Roi de Pique",
            "AD": "As de Carreau", "2D": "Deux de Carreau", "3D": "Trois de Carreau", "4D": "Quatre de Carreau", "5D": "Cinq de Carreau", "6D": "Six de Carreau",
            "7D": "Sept de Carreau", "8D": "Huit de Carreau", "9D": "Neuf de Carreau", "0D": "Dix de Carreau", "JD": "Valet de Carreau", "QD": "Dame de Carreau", "KD": "Roi de Carreau",
            "AH": "As de Coeur", "2H": "Deux de Coeur", "3H": "Trois de Coeur", "4H": "Quatre de Coeur", "5H": "Cinq de Coeur", "6H": "Six de Coeur",
            "7H": "Sept de Coeur", "8H": "Huit de Coeur", "9H": "Neuf de Coeur", "0H": "Dix de Coeur", "JH": "Valet de Coeur", "QH": "Dame de Coeur", "KH": "Roi de Coeur",
            "AC": "As de Trefle", "2C": "Deux de Trefle", "3C": "Trois de Trefle", "4C": "Quatre de Trefle", "5C": "Cinq de Trefle", "6C": "Six de Trefle",
            "7C": "Sept de Trefle", "8C": "Huit de Trefle", "9C": "Neuf de Trefle", "0C": "Dix de Trefle", "JC": "Valet de Trefle", "QC": "Dame de Trefle", "KC": "Roi de Trefle"}
# 1 = rester ; 2 tirer
STRATEGIE_DE_BASE = [[1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2],
                     [1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2],
                     [1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2],
                     [1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2],
                     [2, 2, 2, 1, 1, 1, 2, 2, 2, 2, 2],
                     [2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2],
                     [2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2],
                     [2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2]]

BOTS = ['Alpha', 'Beta', 'Gamma', 'Delta', 'Epsilon']


def paquet():
    """Crée un paquet de 52 cartes

    Returns:
        [liste]: 52 items
    """
    return [item for item in CARD_DIC]


def initPioche(n=6):
    """Ajoute à la pioche n paquets de 52 cartes et les mélange

    Args:
        n (entier, optionnel): nombre de joueurs -> nombre de paquets ; par défaut 1

    Returns:
        [liste]: liste mélangée de n fois 52 cartes
    """
    pioche = []
    for i in range(n):
        pioche += paquet()
    shuffle(pioche)
    return pioche


def piocheCarte(pioche):
    """Renvoie un item au hasard de la liste donnée : pioche une carte parmi la pioche

    Args:
        pioche (liste): liste de cartes créée avec la fonction initPioche

    Returns:
        string: une carte séléctionnée au hasard dans la pioche, carte enlevée de la liste de pioche
    """
    return pioche.pop(0)    # Le sommet de la pioche est en indice 0


def valeurCarte(carte, joueur, scores):
    """Renvoie la valeur d’une carte donnée et gère le choix de la valeur de l’as en fonction de qui joue (croupier, bot, joueur)
    Args:
        carte (string): carte dont on veut connaître la valeur
        joueur (string): nom du joueur
        scores (dictionnaire): dictionnaire qui contient le score, le portefeuille, la mise et les cartes piochées de chacun
    Returns:
        (entier): valeur numérique de la carte
    """
    valeur = carte[0]
    if 48 < ord(valeur) < 58:
        return int(valeur)
    elif valeur in "JQK0":
        return 10
    elif valeur == 'A':
        if joueur == 'Croupier' or joueur in BOTS:
            if scores['Croupier'][0]+11 <= 21:

                return 11
            else:

                return 1
        else:
            print(
                f"{joueur}, vous avez pioché un As, quelle valeur voulez-vous qu'il prenne ?")
            rep = input(
                "Répondez 1 ou 11.")
            while not(rep == '1' or rep == '11'):
                rep = input("Veuillez répondre par 1 ou 11.")
            return int(rep)


def initJoueurs(n):
    """Créée une liste des personnes qui jouent

    Args:
        n (entier): nombre de joueurs

    Returns:
        liste: liste des noms
    """
    liste_des_noms = []
    print("Attention, vous ne pouvez pas donner deux fois le même nom pour deux joueurs.")
    for i in range(n):
        liste_des_noms.append(
            input(f"~~Veuillez entrez le nom du joueur {i+1} ~~\n"))
    return liste_des_noms


def initScores(joueurs, s=0, p=100, m=0):
    """Assigne à chaque joueur une liste contenant le score et le portefeuille de chaque joueur, le tout dans un dictionnaire

    Args:
        Joueurs (liste): liste créée avec initJoueurs
        s(entier, optionnel): Score de départ des joueurs. 0 par défaut.
        p(entier, optionnel): Portefeuille de départ des joueurs. 100 par défaut
        m(entier, optionnel): mise de départ des joueurs. 0 par défaut.

    Returns:
        dictionnaire: Dictionnaire assignant à chaque nom de joueur son score, son portefeuille et sa mise de départ ; crée une liste vide qui contiendra les cartes piochées.
    """
    joueur_score = {}
    for i in joueurs:
        # Liste vide pour les cartes piochées
        joueur_score[i] = [s, p, m, []]
    for i in BOTS:
        joueur_score[i] = [s, p, m, []]
    joueur_score['Croupier'] = [s, []]
    return joueur_score


def premierTour(joueurs, pioche):
    """initialise 2 cartes par joueurs/bots et distribue une carte au croupier : demande à chacun la mise qu’il souhaite mettre et en choisit une pour les BOTS en fonction de leur probabilité de gagner. Met à jour les points de chacun en fonction des cartes piochées.

    Args:
        joueurs (liste): liste des noms des joueurs
        pioche (liste): contient toutes les cartes mélangées

    Returns:
        dictionnaire: Nom, scores, portefeuille et cartes piochées de chaque joueur après avoir pioché deux cartes
    """
    scores = initScores(joueurs)

    for joueur in joueurs:
        scores[joueur][2] = int(
            input(f"{joueur} combien voulez vous miser ?\nLa mise maximum est de 100 rubis."))
        while scores[joueur][1] - scores[joueur][2] < 0:
            scores[joueur][2] = int(
                input(f"{joueur} Votre solde n'est pas suffisant. Réessayez.\n"))
        while scores[joueur][2] > 100:
            scores[joueur][2] = int(
                input(f"{joueur} Vous ne pouvez pas miser plus de 100 rubis. Réessayez.\n"))
        scores[joueur][1] -= scores[joueur][2]
        scores[joueur][3].append(piocheCarte(pioche))
        scores[joueur][3].append(piocheCarte(pioche))
        scores[joueur][0] += valeurCarte(scores[joueur][3][0], joueur, scores)
        scores[joueur][0] += valeurCarte(scores[joueur][3][1], joueur, scores)
        print(
            f"{joueur}, vous avez {CARD_DIC[scores[joueur][3][0]]} et {CARD_DIC[scores[joueur][3][1]]} comme main de départ. Vous avez {scores[joueur][0]} points \n")

    for bot in BOTS:
        scores[bot][3].append(piocheCarte(pioche))
        scores[bot][3].append(piocheCarte(pioche))
        scores[bot][0] += valeurCarte(scores[bot][3][0], bot, scores)
        scores[bot][0] += valeurCarte(scores[bot][3][1], bot, scores)
        scores[bot][2] = randint(10, 50)
        scores[bot][1] -= scores[bot][2]
    scores['Croupier'][1].append(piocheCarte(pioche))
    scores['Croupier'][0] += valeurCarte(scores['Croupier']
                                         [1][0], 'Croupier', scores)
    return scores


def tourJoueur(joueur, tour, scores):
    """Rappel le nombre de points et la main de celui dont c’est le tour, demande s’il veut piocher , lui donne son nouveau score et le met à jour dans le tableau de score. Supprime sa mise et son score s’il a perdu (dépassé 21). Met à jour la liste JoueEncore en fonction de si le joueur a repioché, s’est couché, a abandonné ou a bust.


    Args:
        joueur (string): nom du joueur dont c’est le tour
        tour (entier): nombre de tour de manche
        scores (dictionnaire): assigne à chaque joueur un score
    """
    print(60*"~")
    print(
        f"C'est le tour {tour} de {joueur}. Vous avez {scores[joueur][0]} points.")
    print("Votre main est : ", sep='')
    print(*[CARD_DIC[i] for i in scores[joueur][3]], sep=', ')
    piocher = input(
        f"{joueur}, voulez-vous piocher une cartes ? Oui(o) ou Non(n)\n").lower()
    while not(piocher in "ouinon"):
        piocher = input(
            f"{joueur}, vous pouvez répondre seulement par Oui(o) ou Non(n)\n").lower()
    if piocher == 'o' or piocher == 'oui':
        scores[joueur][3].append(piocheCarte(pioche))
        scores[joueur][0] += valeurCarte(scores[joueur][3][-1], joueur, scores)
        print(
            f"Vous avez pioché {CARD_DIC[scores[joueur][3][-1]]}.\nVotre nouveau score est de {scores[joueur][0]}.")

    elif piocher == 'n' or piocher == 'non':
        joueEncore[joueur] = ('J', 2)
    if scores[joueur][0] == 21:
        joueEncore[joueur] = ('J', 2)
    if scores[joueur][0] > 21:
        print("Vous avez dépassé 21 : vous avez perdu.")
        joueEncore[joueur] = ('J', 3)
        scores[joueur][2] = 0


def tourBot(tour, bot, scores):
    """Rappel le nombre de points, fait choisir à l'IA si elle veut piocher ou nom et entre son nouveau score. Supprime sa mise de son score si il à perdu. Utilise la variable STRATEGIE_DE_BASE , le score du bot et le score du croupier pour faire son choix.


    Args:
        tour (entier): numéro du tour
        bot (string): nom du bot qui joue
        scores (dictionnaire): dictionnaire ave score, portefeuille, mise et cartes
    """
    print(60*'~')
    print(
        f"C'est le tour {tour} de {bot}. Il a {scores[bot][0]} points.\nLa main de {bot} est :")
    print(*[CARD_DIC[i] for i in scores[bot][3]], sep=', ')
    if scores[bot][0] <= 8:
        scores[bot][3].append(piocheCarte(pioche))
        scores[bot][0] += valeurCarte(scores[bot][3][-1], bot, scores)
        print(
            f"{bot} a pioché {CARD_DIC[scores[bot][3][-1]]}.\nSon nouveau score est de {scores[bot][0]}.")
        joueEncore[bot] = ("B", 1)
    elif scores[bot][0] >= 17:
        joueEncore[bot] = ("B", 2)
    elif STRATEGIE_DE_BASE[scores[bot][0]-9][scores['Croupier'][0]-1] == 2:
        scores[bot][3].append(piocheCarte(pioche))
        scores[bot][0] += valeurCarte(scores[bot][3][-1], bot, scores)
        print(
            f"{bot} a pioché {CARD_DIC[scores[bot][3][-1]]}.\nSon nouveau score est de {scores[bot][0]}.")
        joueEncore[bot] = ("B", 1)
    elif STRATEGIE_DE_BASE[scores[bot][0]-9][scores['Croupier'][0]-1] == 1:
        joueEncore[bot] = ('B', 2)
    if scores[bot][0] == 21:
        joueEncore[bot] = ('B', 2)
    if scores[bot][0] > 21:
        print(f"{bot} a dépassé 21 : il a perdu.")
        joueEncore[bot] = ('B', 3)
        scores[bot][2] = 0


def tourCroupier(tour, scores):
    """Rappelle la carte choisie du croupier et le laisse choisir de piocher ou non pour réussir à battre les joueurs en fonction de sa probabilité d’avoir une carte qui lui ferait dépasser 21. Dans tous les cas, il ne s’arrête pas avant 17 points.

    Args:
        tour (entier): nombre de tour de manche
        scores (dictionnaire): assigne à chaque joueur un score
    """
    print(60*"~")
    print(
        f"C'est le tour {tour} du croupier. Il a {scores['Croupier'][0]} points.")
    print("La main du croupier : ", sep='')
    print(*[CARD_DIC[i] for i in scores["Croupier"][1]], sep=', ')
    if scores["Croupier"][0] >= 17:
        joueEncore["Croupier"] = ("C", 2)
        return False
    elif scores["Croupier"][0] < 17:
        scores["Croupier"][1].append(piocheCarte(pioche))
        scores["Croupier"][0] += valeurCarte(
            scores["Croupier"][1][-1], 'Croupier', scores)
        print(
            f"Le croupier a pioché {CARD_DIC[scores['Croupier'][1][-1]]}.\nSon nouveau score est de {scores['Croupier'][0]}.")
        return True
    elif scores["Croupier"][0] > 21:
        print("Le Croupier à dépassé 21 : il a perdu.")
        joueEncore["Croupier"] = ('C', 3)
        return False
    if 17 <= scores["Croupier"][0] <= 21:
        joueEncore["Croupier"] = ('C', 2)


def gagnant1(scores):
    """Renvoie le nom du gagnant1 (plus proche de 21 sans le dépasser) grâce au tableau de scores trié et transformé en liste

    Args:
        scores (dictionnaire): assigne à chaque joueur un score
    """
    tri_score = sorted(
        scores.items(), key=lambda x: x[1][0])  # On trie selon le score de chacun
    # Ici joueur est un entier, pas le nom du joueur
    for joueur in range(len(tri_score)):
        if joueur == 'Croupier':
            print(f"Le croupier a atteint {scores['Croupier'][0]} points.")
        else:
            print(
                f'{tri_score[joueur][0]} a atteint {tri_score[joueur][1][0]} points. Il lui reste {tri_score[joueur][1][1]} rubis.')
    e = 1
    for joueur in range(len(tri_score)):    # On vérifie si il y a une égalité
        if tri_score[len(tri_score)-1-joueur][1][0] == tri_score[len(tri_score)-joueur-2][1][0] and len(tri_score) > 1:
            e += 1   # Si égalité, il y a e gagnants
        else:
            break
    if e > 1:
        print(f"Il y a égalité entre {e} joueurs. ")
        for i in range(e):
            print(tri_score[-1-i][0])
    elif ('J', 2) in joueEncore.values():
        print(tri_score[-1][0], "a gagné la partie avec",
              tri_score[-1][1][0], "points. Bravo !")
    else:
        print("Personne n'a gagné, dommage !")


def gagnant2(scores):
    """Écrit les noms des gagnants2 (21>score>croupier) grâce au tableau de scores, et met à jour le portefeuille en fonction des gains

    Args:
        scores (dictionnaire): assigne à chaque joueur un score
    """
    # Ici joueur est un entier, pas le nom du joueur
    if scores['Croupier'][0] > 21:
        print("Le croupier a dépassé 21, toutes les personnes encore en manche gagnent 2 fois leur mise.")
        for joueur in scores:
            if joueur != 'Croupier':
                scores[joueur][1] += 2*scores[joueur][2]
                scores[joueur][2] = 0
    else:
        a = 1
        for joueur in scores:
            if 21 >= scores[joueur][0] > scores['Croupier'][0]:
                scores[joueur][1] += 2*scores[joueur][2]
                print(
                    f"{joueur} a gagné face au croupier. Il remporte 2 fois sa mise.")
            else:
                a += 1
            if joueur != 'Croupier':
                scores[joueur][2] = 0
        if a > len(scores):
            print("Le croupier a vaincu tous les joueurs et bots. Dommage !")
    elimines = []
    for joueur in scores:
        if joueur != 'Croupier':
            print(f"{joueur}, votre solde est de {scores[joueur][1]} rubis.")
            if scores[joueur][1] < 10:
                print(
                    joueur, "votre portefeuille est presque vide. Vous ne pouvez plus jouer à cette table.")
                elimines.append(joueur)
    for joueur in elimines:
        del scores[joueur]
        joueurs.remove(joueur)


# Variables de départ
print("~~~~~~Bienvenue dans le jeu du Black jack~~~~~~\n\n")

try:
    joueurs = initJoueurs(
        int(input("----Combien il y aura-t-il de joueurs ?----\n")))
except:
    print("\rVous avez mis fin au jeu. A bientôt !")
    exit(1)

pioche = initPioche()
jeu = True
liste = []
nb_partie = 1


while jeu:
    try:
        scores = premierTour(joueurs, pioche)
        if liste != []:
            for i in range(len(joueurs)):
                joueur = joueurs[i]
                scores[joueur][1] = liste[i]-scores[joueur][2]

        print(f"~~~~~~ Partie n°{nb_partie} ~~~~~~")
        nb_tour = 1
        # Création tuples status de manche : 1 en manche, 2 arrête de piocher, 3 a perdu ; J joueur, B bot, C croupier
        joueEncore = {}
        for joueur in joueurs:
            joueEncore[joueur] = ('J', 1)
        for bot in BOTS:
            joueEncore[bot] = ('B', 1)
        joueEncore['Croupier'] = ('C', 1)
        manche = True
        piocheCroupier = True
        while manche:
            print(
                f"La carte du croupier est : {CARD_DIC[scores['Croupier'][1][0]]}")
            for joueur in joueurs:
                if joueEncore[joueur] == ('J', 1):
                    tourJoueur(joueur, nb_tour, scores)
            for bot in BOTS:
                if joueEncore[bot] == ('B', 1):
                    tourBot(nb_tour, bot, scores)
            nb_tour += 1
            if not(('J', 1) in joueEncore.values() or ('B', 1) in joueEncore.values()):
                manche = False

        nb_tour = 2
        while piocheCroupier == True:
            piocheCroupier = tourCroupier(nb_tour, scores)
            nb_tour += 1

        gagnant2(scores)
        if len(pioche) < 54:
            jeu = False
        nb_partie += 1
        a = input("Voulez vous continuer ? Oui (o) ou Non (n).\n")
        a.lower()
        while not(a in "ouinon"):
            a = input("Répondez par Oui ou Non")
        if a == "oui" or a == "o":
            jeu = True
        else:
            jeu = False
        for joueur in joueurs:
            liste.append(scores[joueur][1])
        for bot in BOTS:
            liste.append(scores[bot][1])
    except KeyboardInterrupt:
        print("\rVous avez mis fin au jeu. A bientôt !")
        exit(1)
