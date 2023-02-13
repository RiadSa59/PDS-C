TP PDS: maccess
===============

#### AUTEURS: Riad SABIR

> #### Important:
> Toute manipulation(commande) décrite dans ce fichier est effectuée depuis le dossier racine du projet (pds-fs/access).


Ce dossier correspond aux exercices de la section

[Vérifier les droits d’accès... et expliquer](http://www.fil.univ-lille1.fr/~hym/e/pds/tp/tdfs-cmd.html#access).


Présentation du TP et de ses objectifs
---------------------------------------

- Mise en place des méthodes de travail (Makefile, git)
- Utilisation des pratiques vues en cours (utilisation efficace de man)
- Utilisation de codes issues de la bibliothèque c (limits.h, unistd.h, errno.h...)
- Et donc des fonctions (getopt, strerror...)
- Réalisation de maccess, avec une option -v qui permet d'affichage du résultat (OK, erreurs..)
- Test des différentes erreurs obtenues (cf: test.sh)


Contenu
-------

Ce dépôt contient les fichiers suivants :

* `README.md`: Présentation et synthèse du TP maccess
* `Makefile` : Permet d'ordonner automatiquement une succession d'instructions shell
* `prlimit.c`: Affiche la valeur des constantes pré-définies NAME_MAX et PATH_MAX
* `maccess.c`: Implantation de la commande maccess, qui teste les droits d'accès à un fichier
* `tests.sh` : bash qui illustre et recense les différentes utilisations et erreurs de maccess


Arborescence Du projet
----------------------

```
$ tree
├── history_tests
├── maccess.c
├── Makefile
├── prlimit.c
├── README.md
└── test.sh
```


Comment récupérer le projet
-----------------------------

```
$ git clone git@gitlab-etu.fil.univ-lille1.fr:sasu/pds-fs.git
```

Compilation et exécution des programmes/test
--------------------------------------------

```  
$ make access
```

> #### Note:
> Cela compilera les fichiers et créera notamment l'exécutable de maccess


Voici le modèle d'exécution de maccess :

```
$ ./maccess [OPTIONS] <nom_fichier> ou <dossier>
```

Les différentes options:

```
-r : -Permet de savoir si un fichier est accessible en lecture
     -Permet de savoir si on peut voir le contenu du dossier
-w : -Permet de savoir si un fichier est accessible en écriture
     -Permet de savoir si on peut ajouter/supprimer des fichiers au dossier
-x : -Permet de savoir si un fichier/dossier est exécutable
     -Permet de savoir si on peut accéder au dossier
-v : -Permet d'afficher le résultat renvoyé par l'appel à maccess (succès, erreurs...)
-h :  affiche l'usage de la commande
```

Lancement du test de maccess
----------------------------

```
$ make test
```

> #### Note:
> Cela lance le script bash contenant les différents tests d'erreurs obtenues à l'aide de maccess


Comment "nettoyer" le projet
------------------------------

```
$ make clean
```

> #### Note:
> Cela supprimera les fichiers compilés ainsi que l'exécutable maccess


Erreurs trouvées
----------------
```
[x] EACCES
[x] ELOOP
[x] ENAMETOOLONG
[x] ENOENT
[x] ENOTDIR
```
> #### Note:
> Les cas d'erreurs sont testés dans les fichiers `test.sh` et `session.txt`
