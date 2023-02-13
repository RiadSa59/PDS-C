/*open | lseek */
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
/*fopen | getchar*/
#include <stdio.h>
/* exit */
#include <stdlib.h>
/* assert */
#include <assert.h>
/* read | lseek */
#include <unistd.h>

#define FIN_FICHIER 0
#define TAILLE_TAMPON_STUPIDE 1

/*
*
* AUTEURS : Riad Sabir 
*
* mtail- Programme qui reproduit la fonction tail, i.e lit les n dernières
* lignes d'un fichier, 10 par défaut.
*
* La version dite "stupide" consiste à :
* 1- Compter le nombre total de lignes du fichier
* 2- Repositionner la tête de lecture au début (SEEK SET)
* 3- Afficher les lignes à partir de : nombre total de lignes - nombre souhaité de lignes
*
*/



char buffer[TAILLE_TAMPON_STUPIDE];

/**
  * Compte le nombre de retour à la ligne d'un fichier, utilisé pour le mtail_stupide
  */
int nombre_total_lignes_fichier(int fd)
{
  int nb_lignes = 0;
  if (fd == -1) /* Si l'adresse renvoyée par l'appel à open est nulle */
  {
    return 0;
  }


  while (read(fd,buffer,1) > FIN_FICHIER)
  {
    switch(buffer[0]){
      case '\n':
        nb_lignes ++;
        break;
    }
  }
  return nb_lignes;
}

/**
  * Place la tête de lecture à la bonne position pour mtail_stupide
  */

int positionnement_mtail_stupide (int fd, int lignes_a_ne_pas_afficher)
{
  while ((read(fd,buffer,1) > FIN_FICHIER) && lignes_a_ne_pas_afficher > 0)
  {
    switch(buffer[0]){
      case '\n':
        lignes_a_ne_pas_afficher --;
        break;
    }
  }
  return 0;
}

int mtail_stupide (int fd)
{
  ssize_t bytes_read;
  write(STDOUT_FILENO, buffer, 1); /* Pour ne manquer aucun caractère */
  while ((bytes_read = read(fd,buffer,1)) > FIN_FICHIER)
  {
    write(STDOUT_FILENO, buffer, bytes_read);
  }
  return 0;
}

int main (int argc, char **argv)
{
  int ch;
  int fd = open(argv[1],O_RDONLY);
  int lignes_a_ne_pas_afficher;

  int lignes_a_afficher = 10;

  while ((ch = getopt(argc, argv, "n")) != -1) {
    switch (ch) {
      case 'n':
        lignes_a_afficher = atoi(argv[3]);
        if (lignes_a_afficher == 0)
        return 0;
        break;
      default:
        exit(EXIT_FAILURE);
    }
  }
  argc -= optind;
  argv += optind;

  lignes_a_ne_pas_afficher = nombre_total_lignes_fichier (fd) - lignes_a_afficher;
  lseek (fd, 0, SEEK_SET);
  positionnement_mtail_stupide(fd, lignes_a_ne_pas_afficher);
  mtail_stupide (fd);
  close(fd);
  return 0;
}
