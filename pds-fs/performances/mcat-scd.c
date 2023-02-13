/*
*
* mcat-scd - un programme qui reproduit la fonction cat, via des appels système
* à open, read, close.
* Un tampon est alloué de façon dynamique afin de limiter les appels système.
*
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>


/* buffer lecture*/
char *buffer = NULL;

/* Taille du buffer */
int buf_size;


int read_file (int fd){
   ssize_t bytes_read;
   while((bytes_read = read(fd, buffer, buf_size)) > 0){
     write(STDOUT_FILENO, buffer, bytes_read);
   }
   return 0;
}


int main(int argc, char **argv){
  int fd;
  assert(argc == 2);
  buf_size = atoi(getenv("MCAT_BUFSIZ"));

  buffer = (char *) malloc (buf_size);
  assert(buffer != NULL);

  fd = open(argv[1],  O_RDONLY);
  read_file(fd);
  close(fd);
  free(buffer);
  return EXIT_SUCCESS;
}
