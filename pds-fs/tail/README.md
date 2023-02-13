# Afficher la fin d’un fichier

#### AUTEURS: Riad SABIR 

> #### Important:
> Toute manipulation(commande) décrite dans ce fichier est effectuée depuis le dossier racine du projet (pds-fs/tail).


Ce répertoire correspond aux exercices de la section
[Afficher la fin d’un fichier](http://www.fil.univ-lille1.fr/~hym/e/pds/tp/tdfs-cmd.html#sec13).


Réponse exercice 17
-------------------

D'après la documentation de lseek, les cas suivants renvoient l'erreur ESPIPE :


- fd est associé à :
                    -un tube (pipe)
                    -une socket
                    -une file FIFO

- Afin d'implanter une version dite 'utile' qui permet de se passer de la fonction lseek,
On peut songer à :

      - Un buffer de la taille du nombre d'octets d'un fichier, que l'on charge intégralement via
      un appel à read. On le parcourt ensuite à partir de la fin (à l'image d'une pile) en quête de '\n', et l'on renvoie la partie souhaitée via un appel à write.


Présentation du TP et de ses objectifs
---------------------------------------

- Implanter une fonction similaire à tail
- Prise en main de la fonction lseek, qui permet de positionner la tête de lecture d'un fichier
- Montrer son efficacité en implantant une version dite 'stupide', ainsi qu'une plus efficace (positionnement de la tête en fin de fichier)

Arborescence du projet
----------------------

```
$tree
.
├── Makefile
├── mtail.c
├── mtail_stupide.c
├── README.md
└── test.sh

0 directories, 5 files

```

Comment récupérer le projet
-----------------------------

```
$ git clone git@gitlab-etu.fil.univ-lille1.fr:sasu/pds-fs.git
```
Compilation et exécution des programmes
--------------------------------------------

```  
$ make
(10 lignes par défaut)
$ ./mtail [FICHIER]
(n ligne(s))
$ ./mtail [FICHIER] [-n] [NOMBRE_LIGNES]
```

Compilation et exécution des tests
--------------------------------------------

```  
$ make test
```

> #### Note:
> Cela lance le script bash qui va créer des fichiers et ensuite tester  l'outil. Les fichiers créés sont effacés avec la commande `make clean`.


Comment "nettoyer" le projet
------------------------------

```
$ make clean
```

> #### Note:
> Cela supprimera les fichiers compilés
