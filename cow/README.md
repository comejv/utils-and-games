<div id='top'></div>

# PROJET COW
Projet final d'INF 203 de Côme VINCENT.

<details>
  <summary>Sommaire</summary>
  <ol>
    <li><a href="#execution">Execution</a></li>
    <li><a href="#options">Options</a></li>
    <li><a href="#animations-et-couleurs">Animations et couleurs</a></li>
    <li><a href="#modeles-speciaux">Modèles spéciaux</a></li>
    <li><a href="#exemples">Exemples</a></li>
    <li><a href="#bash">Bash</a></li>
  </ol>
</details>

## C
<div id="execution">

### Execution :
Pour exécuter cow, téléchargez le fichier binary nommé main et lancez le à partir d'une invite de commande ou compilez le vous-même avec la commande :<dd> ```gcc -O2 affiche_vache.h jeux.h main.c -o main```
</div>
<div id="options">

### Options possibles :
Notez qu'une option est qualifiée de "suffisante" si son utilisation seule permet au programme de s'éxécuter normalement. Toutes les options qui la suive seront ignorées.

* -y : permet de choisir le charactère utilisé pour les yeux
* -p : permet de choisir le charactère utilisé pour les pis
* -l : permet de choisir le caractère utilisé pour la langue
* -a : permet de choisir le type d'animation et couleurs. Voir "Animations et couleurs" pour les choix possibles.
* -t : permet de choisir le texte de la bulle de la vache ("Bonjour !" par défaut). Ne prend pas en charge les caractères accentués.
* -j : (suffisante) essayez de garder votre vache en vie en la nourissant ! Ne prend aucune option.
* -r : (suffisante) demande à la vache de lire le texte donné avec -t lettre par lettre.
* -d : (suffisante) permet de jouer à un jeu de devinette avec la vache. Pensez à un nombre et guidez la vache pour qu'elle le trouve.
* -v : (suffisante) permet de préciser un type de vache à afficher. Voir "Modèles spéciaux" pour les choix possibles.
* -h : (suffisante) affiche le manuel du programme.
</div>
<div id="animations-et-couleurs">

### Animation et couleurs :
* 0 -> (défaut) pas d'animation, couleur de base
* 1 -> texte animé caractère par caractère
* 2 -> texte coloré arc en ciel
* 3 -> 1 et 2
</div>
<div id="modeles-speciaux">

### Modèles spéciaux :

* portrait : vous avez toujours voulu embellir le mur de votre salon, et la vache a gracieuseument proposé d'y mettre sa tête en gros plan. Voilà la photo qu'elle vous donne. Art par Joan Stark.
* assise : la vache vous a marché sur le pied et vous n'êtes pas content. Vous la faite s'assoir pour la réprimander. Art par Joan Stark.
* sauvage : elle brise les attentes sociétales. Art par mic & dwb.
* canadienne : très polie ! Art par Veronica Karlsson.
</div>
<div id="exemples">

### Exemples :

* ```./cow``` <dd>-> vache par défaut
* ```./cow -y ^``` <dd>-> vache par défaut avec ^ à la place des yeux
* ```./cow -y x -p y``` <dd>-> vache par défaut avec x pour yeux et y pour pis
* ```./cow -s portrait``` <dd>-> vache spéciale portrait
* ```./cow -t "Je suis morte !"``` <dd>-> vache qui dit "Je suis morte !"
* ```./cow -t "Bonjour." -r``` <dd>-> vache qui lit lettre par lettre le mot "Bonjour."
* ```./cow -d``` <dd>-> lance le jeu de devinette
* ```./cow -h -s assise``` <dd>-> affiche l'aide seulement car l'option -h est suffisante
</div>
<div id="bash">

## Bash

Quelques exercices en shell pour utiliser la commande cowsay avec divers paramètres.

* Kindergarten -> Cowsay prononce les chiffres de 1 à 10
* Primary school -> Compte jusqu'à $1
* Highschool -> Affiche les carrés de 1 à $1
* College -> Affiche la suite fibonacci jusqu'à $1
* University -> Affiche les nombres premiers jusqu'à $1
* Smart -> Remplace les yeux de la vache par le résultat d'une expression donnée en $1
</div>
<p align="right">(<a href="#top">Haut du Readme</a>)</p>
