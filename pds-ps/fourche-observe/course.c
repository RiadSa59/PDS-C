#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <assert.h>
#include <stdio.h>

/**
  * Ce fichier contient la fonction correspondant à :
  * Exercice 7 (À vos marques, prêts...)
  * <a href = "http://www.fil.univ-lille1.fr/%7Ehym/e/pds/tp/tdps-ps.html">
  * Gestion de processus </a>
  *
  * AUTEURS : Riad SABIR
  */


/**
  * Cette fonction simule une course entre dix processus dits "frères"
  */

int course (void)
{
  int i; /* nombre fils */
  int j; /* comptage */
  int k ; /*recomptage*/
  int status;
  int ordre_arrivee[10];
  pid_t pid;
  for (i = 1 ; i < 11 ; i++)
  {
    switch (pid = fork())
    {
      case -1:
        perror("erreur fork");
        exit(EXIT_FAILURE);
        break;

      case 0:
        for (j = 0 ; j < 100000000 ; j++){}
        printf("Je suis le fils n°%d et je viens de compter jusqu'à cent millions! Je recompte.. \n" , i);
        fflush(stdout);

        for (k = 0 ; k < 100000000 ; k++){}

        exit (i);
        break;
      default:
      /* père */
      ;
    }
  }

  for (i = 0 ; i < 10 ; i++) /* On attend l'arrivée de tous les fils avant de mettre fin au programme */
  {
    wait(&status);
    if(WIFEXITED(status)){
      ordre_arrivee[i] = WEXITSTATUS(status);
    }
  }

  printf("\n");
  printf("Ordre d'arrivée: ");
  for(i = 0; i < 10; i++){
    printf("%d ", ordre_arrivee[i]);
  }
  printf("\n");
  exit (EXIT_SUCCESS);
}

int main (void)
{
  return course ();
}
