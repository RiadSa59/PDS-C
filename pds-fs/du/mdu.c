/*
*
* mdu - un programme qui renvoie la taille de l'arborescence de façon recursive
*
* Deux tailles peuvent être prises en compte pour un fichier :
* - la taille apparente, qui est le nombre d’octets contenus dans le fichier ;
* - la taille réelle, qui correspond effectivement au nombre de blocs disque utilisés par le fichier.
*
*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <limits.h>
#include <dirent.h>
#include <unistd.h>
#include <search.h>

#define HASH_SIZE 1000
#define KEY_SIZE 42 /* 2 unsigned long int + separator + \0 */



static int opt_follow_links = 0;
static int opt_apparent_size = 0;

void usage (char *prog) {
 printf("Usage : %s [Lbh] file\n", prog);
 fputs(("\n\
 Options:\n\
 \n\
 -b     affiche la taille apparente des fichiers (octets)\n\
 \n\
 -L     permet d'ouvrir et suivre les liens symboliques\n\
 -h     affiche l'usage de la commande\n" ), stdout);

}

int du_file(const char *pathname)
{
  struct stat st;
  int status;
  int size;
  DIR* dossier;
  struct dirent *drt;
  char *path_key=NULL;
  ENTRY e;

  /* init */
  size = 0;

  if(opt_follow_links){
    status = stat(pathname, &st);
  } else {
    status = lstat(pathname, &st);
  }


  assert (status == 0);

  /* on construit la clé */
  path_key = (char *)malloc(KEY_SIZE);
  snprintf(path_key, KEY_SIZE, "%lu-%lu", st.st_dev, st.st_ino);
  e.key = path_key;

  if(hsearch(e, FIND) == NULL){
	hsearch(e, ENTER);
  } else {
	return 0;
  }

  if (opt_apparent_size) /* -b */
  {
    size += st.st_size;
  }
  else /* real size */
  {
    size += st.st_blocks;
  }
  if (S_ISDIR (st.st_mode))
  {
    dossier = opendir (pathname);
    assert (dossier != NULL);
    while ((drt = readdir(dossier)) != NULL )
    {
      char xpathname[PATH_MAX];

      if (strcmp(drt->d_name, ".") != 0 && strcmp(drt->d_name, "..") != 0)
      {
        snprintf(xpathname,PATH_MAX,"%s/%s",pathname, drt->d_name);
        size += du_file (xpathname);
      }
    }
    closedir(dossier);

  }

  printf("%-8d %s\n", size,  pathname);

  return size;
}



int main (int argc, char **argv) {
 int ch;

 hcreate(HASH_SIZE);
 opt_follow_links = 0;
 opt_apparent_size = 0;

 while ((ch = getopt(argc, argv, "Lbh")) != -1) {
   switch (ch) {
     case 'L':
       opt_follow_links = 1;
       break;
     case 'b':
       opt_apparent_size = 1;
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

 du_file(argv[argc-1]);
 hdestroy();
 exit(EXIT_SUCCESS);
}
