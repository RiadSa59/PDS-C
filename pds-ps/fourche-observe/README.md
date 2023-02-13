#   `multif`, `course` et `observe`

#### AUTEURS: Riad SABIR

Ce répertoire correspond à l’exercice `multif` de la section
[Clonage de processus](http://www.fil.univ-lille1.fr/~hym/e/pds/tp/tdps-fork.html#multif)
et aux exercices de la section
[Gestion de processus](http://www.fil.univ-lille1.fr/~hym/e/pds/tp/tdps-ps.html).


> #### Important:
> Toute manipulation(commande) décrite dans ce fichier est effectuée depuis le dossier racine du projet (pds-ps/fourche-observe).


Présentation du TP et de ses objectifs
---------------------------------------

- Implanter la fonction multif, qui ordonne à n processus d'exécuter une fonction qui leur est propre, ordonner au père d'attendre tous les résultats, pour ainsi mettre en conjonction les résultats obtenus (vrai si tous vrai, faux sinon)
- Implanter la fonction course, qui simule une course entre dix processus fils, afin de mettre en éviSi on arrête le processus père on peut avoir des processus marqués comme "<defunct>" - des processus zombie. Ça se passe quand le processus est "gardé"
vivant par son père afin de récupérer le code de retour.
Dans notre programme le processus est zombie tant que on n'introduit pas
la saisie clavier.
dence le partage des ressources entre les processus, ainsi que l'impossibilité de prévoir l'ordre d'exécution (et de terminaison) des processus.
- Implanter la fonction observe, qui consiste à créer n fils, de les mettre en 'veille', de les tuer (ou tuer le père) et enfin d'observer les effets.

Exercice 7
----------
L'ordre de démarrage et d'arrêt des processus n'est pas le même, donc on peut conclure que le temps d'exécution est distribué de manière aléatoire.


Exercice 8
----------

###### Réponse 8.1

```
Pour i allant de 0 à n
  Créer un fils
  Tant que vrai (boucle infinie)
    Afficher pid
    Mettre en veille 5 secondes
  Fin Tant que
Fin Pour

Appel système (ps)

Pour i allant de 0 à n
  Attendre fils qui s'arrête
  Exécution commande kill
  Afficher pid fils arrêté
Fin Pour

Renvoyer 0

```

###### Réponse 8.2

Lorsque le processus père est arrêté, les fils deviennent des orphelins, et qui sont adoptés par le processus init (le PPID des processus créés devient égal au PID du init)- des processus démons.
Ils continuent donc de s'exécuter.

###### Réponse 8.3

**Exemple:**


(après avoir exécuté `kill 17011` dans un autre terminal)
```
PID TTY          TIME CMD
17009 pts/6    00:00:00 observe
17010 pts/6    00:00:00 observe
17011 pts/6    00:00:00 observe <defunct>
17524 pts/6    00:00:00 sh
17525 pts/6    00:00:00 ps
31407 pts/6    00:00:00 bash

```
Si on arrête le processus père on peut avoir des processus marqués comme `<defunct>` - des processus zombie. Ça se passe quand le processus est "gardé"
vivant par son père afin de récupérer le code de retour.
Dans notre programme le processus est zombie tant qu'on ne fait pas
de saisie clavier.


Arborescence du projet
----------------------

```
$tree
.
├── course.c
├── Makefile
├── multif.c
├── observe.c
├── README.md
└── test.sh

0 directories, 6 files

```

Comment récupérer le projet
-----------------------------

```
$ git clone git@gitlab-etu.fil.univ-lille1.fr:sasu/pds-ps.git
```

Compilation et exécution des programmes
--------------------------------------------
```
$ make all  # -> compilation de tous les exécutables
```

```  
$ make multif

$ ./multif [true | false] [true | false] ...

$ make course

$ ./course

$ make observe

$ ./observe [nombre de forks/enfants]
```
> ATTENTION!
> ----------
> Après avoir exécute `./observe` il faut arrêter les processus créés
> en utilisant la commande ```$ kill [id processus]```


Compilation et exécution des tests
--------------------------------------------

```  
$ make all # -> il faut avoir compilé les programmes avant exécuter le test
$ make test
```


Comment "nettoyer" le projet
------------------------------

```
$ make clean
```

> #### Note:
> Cela supprimera les fichiers compilés
