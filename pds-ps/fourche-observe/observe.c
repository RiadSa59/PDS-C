#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <assert.h>
#include <stdio.h>


/**
  * Ce fichier contient la fonction correspondant à :
  * Exercice 8 (Observation de processus)
  * <a href = "http://www.fil.univ-lille1.fr/%7Ehym/e/pds/tp/tdps-ps.html">
  * Gestion de processus </a>
  *
  * AUTEURS : Riad SABIR
  */


int init (int n)
{
  int i;
  pid_t pid;

  for (i = 0 ; i < n ; i++)
  {
    switch (pid = fork())
    {
      case -1:
        perror("erreur fork");
        exit (EXIT_FAILURE);
        break;
      case 0:
        while (1)
        {
          printf("Still alive %d %d\n", getpid(), i);fflush(stdout);
          sleep(5);
        }
      default:
        break;
    }
  }

  system ("ps");
  getc(stdin);
  for(i = 0; i < n; i++){
    printf("Process stop: %d\n", wait(NULL));fflush(stdout);

  }

  return 0;
}

int main (int argc, char **argv)
{
  assert (argc == 2);
  return init(atoi(argv[1]));
}
