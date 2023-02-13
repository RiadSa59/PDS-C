 /*
 *maccess - un programme qui teste les droits d'accès à un fichier
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <limits.h>
#include <unistd.h>
#include <errno.h>


int vflag, rflag, wflag, xflag;

void usage (char *prog) {
	printf("usage : %s [rvwx] file\n", prog);
}



/* On teste les droits d'accèss */
int maccess (int argc, char **argv) {
	return access(argc[argv - 1], (rflag * R_OK) |
		               (xflag * X_OK) |
		               (wflag * W_OK)   );
}


/* Choix du message imprimé */
void print_message(int status, char *path){
	if(vflag == 1 && status != 0){
		fprintf(stderr, "maccess: %s: %s\n", path, strerror(errno));
	}
	if(vflag == 1 && status == 0){
		fprintf(stdout, "maccess: OK \n");
	}
}



int main (int argc, char **argv) {
	int ch;
	int out;

	out = 0;
	vflag = 0;
	rflag = 0;
	wflag = 0;
	xflag = 0;
	while ((ch = getopt(argc, argv, "vrwxh")) != -1) {
		switch (ch) {
			case 'v':
				vflag = 1;
				break;
			case 'r':
				rflag = 1;
				break;
			case 'w':
				wflag = 1;
				break;
			case 'x':
				xflag = 1;
				break;
			case 'h':
			default:
				usage(argv[0]);
		}
	}

	argc -= optind;
	argv += optind;

	out = maccess(argc,argv);
	print_message(out, argv[argc-1]);
	exit(out == 0 ? EXIT_SUCCESS : EXIT_FAILURE);
}
