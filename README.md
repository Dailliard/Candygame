# Calculatrice-C
Projet collaboratif en langage C développé dans un cadre pédagogique (ECE Paris).
Cette application implémente une calculatrice en ligne de commande, organisée de façon modulaire :
- ‘main.c‘ : interface utilisateur (menu et affichage)
- ‘calculs.c‘ / ‘calculs.h‘ : fonctions de calcul
- ‘tests.c‘ : tests unitaires vérifiant automatiquement le bon fonctionnement des calculs
## Fonctionnalités
- Addition
- Soustraction
- Multiplication
- Division (avec gestion de la division par zéro)
- Tests unitaires automatisés
## Structure du projet
calculatrice-c/
|-- main.c
|-- calculs.c
|-- calculs.h
|-- tests.c
|-- .gitignore
|-- README.md
## Compilation et exécution
### 1. Compiler la calculatrice
gcc main.c calculs.c -o calculatrice
./calculatrice
### 2. Compiler et exécuter les tests
Les tests automatisés vérifient la validité de chaque fonction de calcul via ‘assert()‘.
gcc tests.c calculs.c -o tests
./tests
Si tous les tests réussissent, le programme affichera :
Tous les tests ont réussi.
En cas d’erreur, l’exécution s’arrêtera immédiatement, indiquant quel test a échoué.
## A propos de ‘tests.c‘
Le fichier ‘tests.c‘ contient un ensemble de tests unitaires. Ils permettent de vérifier automatiquement que
,→ les fonctions :
- ‘addition()‘
- ‘soustraction()‘
- ‘multiplication()‘
- ‘division()‘
retournent bien les résultats attendus.
Ces tests garantissent la **fiabilité** et la **stabilité** du code tout au long du développement
,→ collaboratif.
> Recommandation : exécuter les tests après toute modification du code.
## Équipe
- Sarah : Interface utilisateur (‘main.c‘), gestion du dépôt GitHub
- Stéphanie : Développement des fonctions de calcul (‘calculs.c‘, ‘calculs.h‘)
- Samy : Tests unitaires (‘tests.c‘), intégration et relecture
## Objectifs pédagogiques
- Utiliser Git et GitHub dans un vrai workflow collaboratif
- Organiser un projet C modulaire
- Mettre en place des tests unitaires
- Travailler avec branches, pull requests et validation de code
## Dépendances
- Un compilateur C (GCC ou Clang)
- Git (pour la gestion de versions)
## Licence
Projet pédagogique - réutilisation autorisée sous conditions éducatives.
