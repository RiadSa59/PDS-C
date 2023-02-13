#   `do`

#### AUTEURS: Riad SABIR

Ce répertoire correspond à l’exercice
« [Exécutions de commandes](http://www.fil.univ-lille1.fr/~hym/e/pds/tp/tdps-exec.html#do) : `do` ».


> #### Important:
> Toute manipulation(commande) décrite dans ce fichier est effectuée depuis le dossier racine du projet (pds-ps/do).


Présentation du TP et de ses objectifs
---------------------------------------

- Implanter la fonction do, qui retourne un résultat logique des valeurs retournées, et selon les options passées en paramètre avant l'exécution du programme.
- Les n résultats renvoyées par les n commandes passées en paramètre correspondent aux valeurs de retour des fils.
- L'objectif de ce TP est donc :


  1. Mettre en pratique le cours des processus (fork)
  2. Savoir lancer des commandes en C (exec)
  3. Traiter des valeurs de retour, ici celles des fils, à l'aide d'opérations logiques
     Modifier le comportement d'un programme en fonction des options (utilisation de FLAG et opérateurs logiques)

**Les options implantées sont les suivantes:**

```
    -o:    retourne un statut formé par la disjonction des résultats
    -a:    retourne un statut formé par la conjonction des résultats
    -c:    Court-circuite le programme lorsque résultat définitif
    -k:    Tue les processus fils restants si option c activée + résultat définitif
    -h:    affiche l'usage de la commande
```



Arborescence du projet
----------------------

```
$tree
.
├── args.c
├── do.c
├── makeargv.c
├── makeargv.h
├── Makefile
├── README.md
└── test.sh

0 directories, 7 files

```

Comment récupérer le projet
-----------------------------

```
$ git clone git@gitlab-etu.fil.univ-lille1.fr:sasu/pds-ps.git
```

Compilation et exécution des programmes
--------------------------------------------
```
$ make # -> compilation de tous les exécutables
```

```  
$ ./do [opt] "Commande1" "Commande 2"...


```


Compilation et exécution des tests
--------------------------------------------

```  
$ make test
```


Comment "nettoyer" le projet
------------------------------

```
$ make realclean
```

> #### Note:
> Cela supprimera les fichiers compilés
