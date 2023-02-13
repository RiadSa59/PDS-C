#   `du`

#### AUTEURS: Riad SABIR

> #### Important:
> Toute manipulation(commande) décrite dans ce fichier est effectuée depuis le dossier racine du projet (pds-fs/du).

Ce répertoire correspond aux exercices de la section
[Parcours d’une hiérarchie](http://www.fil.univ-lille1.fr/~hym/e/pds/tp/tdfs-cmd.html#du).


Présentation du TP et de ses objectifs
---------------------------------------

- Travail avec le système de fichiers.
- Programmation de l'outil `du`

Arborescence du projet
----------------------

```
$ tree
.
├── Makefile
├── mdu
├── mdu.c
├── mdu.o
├── README.md
└── test.sh

```

Comment récupérer le projet
-----------------------------

```
$ git clone git@gitlab-etu.fil.univ-lille1.fr:sasu/pds-fs.git
```

Compilation et exécution des programmes
--------------------------------------------

```  
$ make mdu
```

Compilation et exécution des tests
--------------------------------------------

```  
$ make test
```
> #### Note:
> Cela lance le script bash qui va créer deux arborescences avec des fichiers et des liens symboliques, et ensuite tester  l'outil. Les arborescences créées
sont effacées à la fin du test.

Comment "nettoyer" le projet
------------------------------

```
$ make clean
```

> #### Note:
> Cela supprimera les fichiers compilés ainsi que l'exécutable mdu.

Voici le modèle d'exécution de `mdu` :
-----------------------------------------
```
$ ./mdu [OPTIONS] ... [FICHIER]
```

Les différentes options:

```
-b :  affiche la taille apparente des fichiers (octets)
-L :  permet d'ouvrir et suivre les liens symboliques
-h :  affiche l'usage de la commande
```
