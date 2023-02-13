#   Processus légers

#### AUTEURS: Riad SABIR 

Ce répertoire correspond à l’exercice
« [Applications à des exemples
concrets](http://www.fil.univ-lille1.fr/~hym/e/pds/tp/tdth-concrets.html) ».


> #### Important:
> Toute manipulation(commande) décrite dans ce fichier est effectuée depuis le dossier racine du projet (pds-multithread).


Présentation du TP et de ses objectifs
---------------------------------------

- Réutiliser un algorithme de parcours et de tri opérationnels de façon multithreadé
- Créer un "wrapper"
- Savoir synchroniser des processus (utilisation des mutex ainsi que des conditions)
- Analyser des données graphiques

Arborescence du projet
----------------------

```
$tree
.
├── aleazard.c
├── compteur-gc.c
├── compteur-gc.dat
├── compteur-gc.gp
├── compteur-gc.png
├── main.c
├── main.h
├── Makefile
├── pile.c
├── pile.h
├── rapide.c
├── rapide.h
├── README.md
├── res.txt
├── test.sh
├── tri.c
├── tri.h
├── tri_rapide.dat
├── tri-rapide.gp
└── tri-rapide.png

0 directories, 20 files


```

Comment récupérer le projet
-----------------------------

```
$ git@gitlab-etu.fil.univ-lille1.fr:deroissart/pds-multithread.git
```

Compilation et exécution des programmes
----------------------------------------
```
$ make exec-compteur
$ make exec-rapide
```




Génération des fichiers dat
------------------------------------------

```  
$ make dat-compteur
$ make dat-rapide
```

Génération des fichiers png
------------------------------------------

```  
$ make gnuplot-compteur
$ make gnuplot-rapide
```


Comment "nettoyer" le projet
------------------------------

```
$ make realclean (ou clean plus léger)
```

> #### Note:
> Cela supprimera les fichiers compilés ainsi que les fichiers .dat .txt et .png
