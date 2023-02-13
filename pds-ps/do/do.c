
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<sys/wait.h>
#include<sys/types.h>
#include<errno.h>
#include "makeargv.c"
#include "makeargv.h"
#include <sys/types.h>
#include <signal.h>

/* Valeurs prédéfinies des différentes options, utilisées pour modifier comportement mdo */

#define DEFAULT_FLAG 0
#define O_FLAG 1
#define A_FLAG 2
#define C_FLAG 4
#define K_FLAG 12

int status_global; /** Si conjonction -> 1
                     * Si Disjonction -> 0
                     */


void usage () {
 printf("Usage de do : [opt] Commande1 Commande 2...\n");
 fputs(("\n\
 Options:\n\
 \n\
 -o:    retourne un statut formé par la disjonction des résultats\n\
 -a:    retourne un statut formé par la conjonction des résultats\n\
 -c:    Court-circuite le programme lorsque résultat définitif \n\
 -k:    Tue les processus fils restants si option c activée + résultat définitif \n\
 -h:    affiche l'usage de la commande\n\
 \n"), stdout);

}


void init (int *status_global, int FLAGS)
{
  switch(FLAGS & 0b111) /* masque binaire, 111 = cao */
  {
    case(DEFAULT_FLAG): case(O_FLAG): case (C_FLAG):  case(O_FLAG + C_FLAG): /* Si disjonction */
      *status_global = 1; /* Utilisé pour la disjonction ( 1 & val retour commande) */
      break;

    case(A_FLAG): case(C_FLAG + A_FLAG): /* Si conjonction */
      *status_global = 0; /* Utilisé pour la conjonction (0 | val retour commande) */
      break;

    default:
    ;
  }
}


int mdo(int argc, char **argv, int FLAGS){
    int status_global, status_proc;
    int i = 0;
    int coupe_circuit = 0; /* Si coupe circuit = 1, on arrête d'évaluer valeurs retours */
    pid_t all_pid[argc - i]; /* Liste des pid enfants */
    init (&status_global, FLAGS); /* Initialisation de status global en fct des options */

    for(; i<argc; i++){ /* exécution des i commandes par i processus fils */
        switch(all_pid[i] = fork()){
            case -1:
                perror("Fork error");
                break;
            case 0:
                execvp(makeargv(argv[i])[0], makeargv(argv[i])); /* execute i-ème commande. premier paramètre = nom commande | second paramètre = nom commande + option(s) */
                perror(strerror(errno));
                exit(EXIT_FAILURE);
                break;
            default:
                break;
        }
    }

    i = 0;
    for(; i < argc; i++){ /* On récupère successivement le résultat des fils */

        if (!coupe_circuit)
        {
          waitpid(all_pid[i],&status_proc,0); /* On récupère le résultat de chaque fils en respectant l'ordre des arguments */
          if(WIFEXITED(status_proc)){
            status_proc = WEXITSTATUS(status_proc); /*Valeur de retour du i-ème fils */
            printf("Résultat de %s : %d\n" ,argv[i] , status_proc);
            fflush(stdout);

            switch(FLAGS & 0b111) /*Traitement de cette valeur en fct des options */
            {
              case(DEFAULT_FLAG): case(O_FLAG):
                status_global = status_global & status_proc;
                break;

              case(A_FLAG):
                status_global = status_global | status_proc;
                break;

              case(C_FLAG | DEFAULT_FLAG): case(C_FLAG | O_FLAG):
                  status_global = status_global & status_proc;
                  if(!status_global) /* Si disjonction et valeur = 0 (vrai) */
                  {
                    coupe_circuit = 1;
                  }
                break;

              case(C_FLAG | A_FLAG):
                status_global = status_global | status_proc;
                if(status_global) /* Si conjonction et valeur = 1 (faux) */
                {
                  coupe_circuit = 1;
                }
              break;


          }
        }
        else /*Erreur W_ISEXITED */
        {
          printf("erreur W_ISEXITED \n");
          fflush(stdout);
          exit(EXIT_FAILURE);
        }
      }
      else /* Si coupe_circuit sur 1 (option -c + valeur finale trouvée)*/
      {

        if (FLAGS >= K_FLAG) /*Si option k activée */
        {
          for (; i < argc ; i++ ) /* On tue tous les fils */
          {
            printf("Destruction du processus %d qui a exécuté la commande %s\n", i,argv[i]);
            kill(all_pid[i], SIGKILL);
          }
        }
      }
    }
    printf("Résultat final : %d\n\n" , status_global);
    exit(status_global); /* Résultat de mdo */
  }

int main(int argc, char **argv){

    int FLAGS = 0;
    char ch;

    while ((ch = getopt(argc, argv, "oackh")) != -1) { /* On remplit une variable FLAGS à l'aide opérations logiques, cela modifie le comportement de mdo */
       switch (ch) {
         case 'o':
           FLAGS = FLAGS | O_FLAG;
           break;
         case 'a':
           FLAGS = FLAGS | A_FLAG;
           break;
         case 'c':
           FLAGS = FLAGS | C_FLAG;
           break;
         case 'k':
           FLAGS = FLAGS | K_FLAG;
           break;
         case 'h':
           usage();
           exit(EXIT_SUCCESS);
         default:
         usage();
         exit(EXIT_FAILURE);
       }

     if ((FLAGS & 0b11) == 0b11) /* Si option oa */
     {
       printf("Option oa impossible \n");
       exit (EXIT_FAILURE);
     }
   }
   argc -= optind;
   argv += optind;

  return mdo(argc, argv, FLAGS);
}
