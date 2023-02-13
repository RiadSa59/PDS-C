#   `mshell`

#### AUTEURS: Riad SABIR 

Ce dépôt correspond au TP de PDS
« [mshell](http://www.fil.univ-lille1.fr/~hym/e/pds/tp/tdjobs.html) ».

Présentation du TP et de ses objectifs
---------------------------------------

- Implanter un shell
- Programmation des commandes.
- Programmation des tubes et gestionnaires de signaux.
- L'objectif de ce TP est donc :


  1. Mettre en pratique le cours des communication inter-processus (signaux, tubes)
  2. Programmer et assurer un bonne gestion des processus (jobs)
  3. Créer un environnement stable pour qui communique avec le noyau d'une manière sécurisé.


Arborescence du projet
----------------------

```
$ tree
.
├── cmd.c
├── cmd.h
├── common.c
├── common.h
├── jobs.c
├── jobs.h
├── Makefile
├── mshell.c
├── pipe.c
├── pipe.h
├── README.md
├── sighandlers.c
└── sighandlers.h

0 directories, 13 files
```

Comment récupérer le projet
-----------------------------

```
$ git clone git@gitlab-etu.fil.univ-lille1.fr:sasu/pds-mshell.git
```

Compilation et exécution des programmes
--------------------------------------------
```
$ make   # -> compilation du programme mshell
$ ./mshell
$ ./mshell -v # pour lancer le mode verobse
```


Comment "nettoyer" le projet
------------------------------

```
$ make clean # -> efface les fichier objet (.o)
$ make realclean # -> efface l'exécutable "mshell"
```

Commandes disponibles
------------------------------

```
mshell> help
available commands are:
 exit - cause the shell to exit
	 exit
 jobs - display status of jobs in the current session
	 jobs
 fg   - run a job identified by its pid or job id in the foreground
	 fg pid|jobid
 bg   - run a job identified by its pid or job id in the background
	 bg pid|jobid
 stop - stop a job identified by its pid or job id
	 stop pid|jobid
 kill - kill a job identified by its pid or job id
	 kill pid|jobid
 help - print this message
	 help

ctrl-z and ctrl-c can be used to send a SIGTSTP and a SIGINT, respectively

```


Bugs et problèmes non résolus
------------------------------
**1. Le traitement de signaux pour les tubes:**


   Le signal SIGTSTP(ctrl-z) bloque le shell, donc on peut pas tester
   les autres signaux comme SIGCONT, etc.

> #### Note:
> On peut toujours arrêter "tubes" les tubes avec ctrl-c.

Le warnings
------------------------------
```
$ make
gcc -Wall -Wextra -ansi -pedantic -D_XOPEN_SOURCE=500 -g -c mshell.c
gcc -Wall -Wextra -ansi -pedantic -D_XOPEN_SOURCE=500 -g -c common.c
gcc -Wall -Wextra -ansi -pedantic -D_XOPEN_SOURCE=500 -g -c sighandlers.c
sighandlers.c: In function ‘sigchld_handler’:
sighandlers.c:36:26: warning: unused parameter ‘sig’ [-Wunused-parameter]
 void sigchld_handler(int sig) {
                          ^
sighandlers.c: In function ‘sigint_handler’:
sighandlers.c:78:25: warning: unused parameter ‘sig’ [-Wunused-parameter]
 void sigint_handler(int sig) {
                         ^
sighandlers.c: In function ‘sigtstp_handler’:
sighandlers.c:109:26: warning: unused parameter ‘sig’ [-Wunused-parameter]
 void sigtstp_handler(int sig){
                          ^
gcc -Wall -Wextra -ansi -pedantic -D_XOPEN_SOURCE=500 -g -c jobs.c
gcc -Wall -Wextra -ansi -pedantic -D_XOPEN_SOURCE=500 -g -c cmd.c
gcc -Wall -Wextra -ansi -pedantic -D_XOPEN_SOURCE=500 -g -c pipe.c
gcc -g -o mshell mshell.o common.o sighandlers.o jobs.o cmd.o pipe.o
```
