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
#define TAILLE_TAMPON 1024

/*
*
* AUTEURS : Riad SABIR 
*
* mtail- Programme qui reproduit la fonction tail, i.e lit les n dernières
* lignes d'un fichier, 10 par défaut.
*
* La version dite "efficace" consiste à :
* 1- Positionner la tête de lecture en fin de fichier - TAILLE_TAMPON (pour lire dans l'ordre)
* 2- Remplir le buffer de TAILLE_TAMPON caractères
* 3- Compter le nombre de lignes
* 4a- Si nombre de lignes > nombre de lignes souhaité : on affiche les n dernières lignes
* 4b- Si non, on renouvelle l'opération via un appel récursif

*/



typedef struct file_s{
  int fd; /* Identifiant du fichier */
  int position; /* Position dans le buffer */
  char buffer [TAILLE_TAMPON];
}
file_s;


void usage (char *prog) {
 printf("Usage : %s [n] [NOMBRE_LIGNES] [NOM_FICHIER]\n", prog);
 fputs(("\n\
 Options:\n\
 \n\
 -n:    (n=int) on indique le nombre de lignes a afficher\n\
 -h:    affiche l'usage de la commande\n\
 \n"), stdout);

}


/*
 * Fonction récursive qui compte par 'paquets' (tampon) le nombres de sauts
 * de ligne d'un fichier texte parcouru de la fin vers le début
 * Et ce afin de placer justement la tête de lecture à n lignes à afficher
 */
int positionnement_mtail_efficace (file_s* file, int lignes_a_afficher, ssize_t nombre_caractere_restant)
{
  int nombre_caracteres_lus;

  if (nombre_caractere_restant < TAILLE_TAMPON) /* Afin d'éviter une erreur lors de l'appel à lseek (si moins de TAILLE_TAMPON caractères restants)*/
  {
    lseek(file->fd,-nombre_caractere_restant,SEEK_CUR); /* On retourne au début du fichier , un SEEK_SET aurait été possible*/
    file->position = read(file->fd, file->buffer,nombre_caractere_restant)-1;
    nombre_caractere_restant = 0;
  }
  else
  {
    lseek(file->fd,-TAILLE_TAMPON,SEEK_CUR); /* On met la tête de lecture avant la mise en mémoire des TAILLE_TAMPON caractères */
    file->position = read(file->fd, file->buffer,TAILLE_TAMPON)-1;
    nombre_caractere_restant -= TAILLE_TAMPON;
  }

   nombre_caracteres_lus = file->position +1;



  for (;file->position >= 0 ; file->position--)
  {
    if (lignes_a_afficher == 0) /* Lorsqu'on a parcouru les n lignes à imprimer */
    {
      file->position+=2; /* Pour compenser l'incrémentation, et éviter un \n inopportun */
      lseek(file->fd,file->position-nombre_caracteres_lus,SEEK_CUR); /* On place la tête à la bonne position d'écriture */
      return 0;
    }

    if(file->buffer[file->position] == '\n'){
        lignes_a_afficher--;
    }
  }

  if (nombre_caractere_restant == 0) /* On imprime l'intégralité du fichier si moins de n lignes */
  {
    lseek(file->fd,0,SEEK_SET);
    return 0;
  }

  lseek(file->fd,-TAILLE_TAMPON,SEEK_CUR); /* On remet la tête de lecture à la même position qu'avant l'appel à read */
  return positionnement_mtail_efficace (file, lignes_a_afficher, nombre_caractere_restant);
}

int tail_efficace(const char *path, int ntail)
{
  ssize_t nombre_total_caractere;
  file_s* file = (file_s*) malloc (sizeof(file_s));
  file->fd = open(path, O_RDONLY);
  nombre_total_caractere = lseek (file->fd, -1, SEEK_END); /* Positionnement en fin de fichier, AVANT le dernier caractère */
  assert (file->fd != -1); /* On vérifie que l'affectation s'est bien déroulée */
  if (positionnement_mtail_efficace(file,ntail, nombre_total_caractere) != 0) /* Si l'opération s'est mal passée */
  {
    return -1;
  }

  while ((nombre_total_caractere = read(file->fd,file->buffer, TAILLE_TAMPON)) > FIN_FICHIER)
  {
    write(STDOUT_FILENO,file->buffer, nombre_total_caractere);
  }
  close(file->fd);
  free(file);
  return 0;

}


int main (int argc, char **argv)
{
  int ch;
  int lignes_a_afficher = 10;

  while ((ch = getopt(argc, argv, "nh")) != -1) {
    switch (ch) {
      case 'n':
        if(argc > 3)
        {
        lignes_a_afficher = atoi(argv[2]);
        tail_efficace(argv[3], lignes_a_afficher);
        exit (EXIT_SUCCESS);
        }
        break;
      case 'h':
        usage(argv[0]);
        exit(EXIT_SUCCESS);
      default:
        usage(argv[0]);
        exit(EXIT_FAILURE);
    }
  }
  argc -= optind;
  argv += optind;

  tail_efficace(argv[0], lignes_a_afficher);
  exit (EXIT_SUCCESS);
}
