# Jeu de la Vie - PigFarm

## Description

Ce projet implémente le célèbre **Jeu de la Vie** de John Conway en C++, en s’appuyant sur les principes de la programmation orientée objet (POO). Le programme propose deux modes d'exécution pour simuler l'évolution d'une grille de cellules selon des règles prédéfinies :

- **Mode Console** : Permet d’afficher l’évolution des cellules directement dans le terminal.
- **Mode Graphique** : Fournit une visualisation dynamique et interactive des cellules dans une fenêtre graphique grâce à la bibliothèque SFML.

Ce projet s'inscrit dans le cadre d'un exercice pédagogique visant à appliquer des concepts fondamentaux de la POO tout en construisant une application fonctionnelle.

---

## Fonctionnalités

Le programme offre une série de fonctionnalités permettant d'explorer les possibilités offertes par le Jeu de la Vie :

1. Initialisation d'une grille à partir d'un fichier de configuration ou de paramètres par défaut.
2. Simulation de l'évolution des cellules selon les règles de naissance, survie et mort du Jeu de la Vie.
3. Deux modes d'affichage :
   - En mode console, chaque itération est affichée sous forme textuelle directement dans les fichiers enregistrés.
   - En mode graphique, l’évolution des cellules est visualisée dans une interface graphique interactive.
4. Navigation et interactions utilisateur intuitives, adaptées à chaque mode.
5. Possibilité pour l'utilisateur de rentrer des données textuelles via les TextBoxes à l'aide de son clavier.

---

## Installation manuelle

Télécharger le fichier .zip via Github : https://github.com/Poney-star/JeuDeLaVie

Extraire l'ensemble des éléments dans le répertoire choisi.

Vous rendre dans le répertoire choisi puis dans JeuDeLaVie/build/bin/Debug.

Afin de lancer le jeu, il suffit de cliquer sur PigFarm.exe. Il est possible de créer un raccourci depuis le bureau vers le jeu.

## Installation automatique (en développement...)

## Structure du Projet

Le projet est structuré en plusieurs fichiers sources et en-têtes afin de favoriser la modularité et la maintenabilité du code. Voici une vue d’ensemble des principaux composants :

- **`main.cpp`** : Point d’entrée du programme qui orchestre le déroulement de la simulation.
- **`cell.hpp` / `cell.cpp`** : Classes représentant les cellules et leurs comportements (état, mise à jour, etc.).
- **`grid.hpp` / `grid.cpp`** : Gestion de la grille, incluant la mise à jour des cellules et les calculs des voisinages.
- **`game.hpp` / `game.cpp`** : Gestion globale du jeu, incluant la logique des itérations et les interactions utilisateur.
- **`menu.hpp` / `menu.cpp`** : Implémentation du menu principal, permettant de configurer la simulation ou de naviguer entre les modes.
- **`button.hpp` / `button.cpp`** : Définition des boutons interactifs utilisés dans l’interface graphique.
- **`graphicsManager.cpp` / `graphicsManager.hpp`** : Gestionnaire des éléments graphiques utilisant la bibliothèque SFML.

---

## Contributions

Les contributions au projet sont les bienvenues. Si vous souhaitez améliorer le code, ajouter des fonctionnalités ou corriger des bugs, vous pouvez soumettre une *pull request* directement sur le dépôt GitHub. Avant de proposer des changements majeurs, nous vous invitons à ouvrir une *issue* afin de discuter de vos idées avec les autres contributeurs.

---

## Licence

Ce projet est distribué sous la licence MIT, ce qui permet une utilisation libre et une modification du code tout en respectant les termes de la licence. Pour plus de détails, consultez le fichier `LICENSE` inclus dans le dépôt.

---

Ce projet constitue une excellente opportunité pour explorer les concepts de la programmation orientée objet tout en travaillant sur une application ludique et visuellement engageante. N’hésitez pas à participer, échanger ou personnaliser cette implémentation pour l’adapter à vos besoins.