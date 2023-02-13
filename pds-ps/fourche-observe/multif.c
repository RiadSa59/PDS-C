#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<string.h>

typedef int (*func_t) (char *);

int testfunc(char *str){
   return strcmp("true", str) == 0 ? EXIT_SUCCESS : EXIT_FAILURE; 
   
}

int multif (func_t f[], char *args[], int n){
    int i, status, stat_tmp;
    pid_t pid;

    status = 0;
    for(i = 0; i < n; i++){
        pid = fork();
        switch(pid){
            case -1:
                perror("fork error");
                break;
            case 0:
                exit(f[i](args[i]));
                break;
            default:
                wait(&stat_tmp); 
                if(WIFEXITED(stat_tmp)) stat_tmp = WEXITSTATUS(stat_tmp);
                status = status | stat_tmp;
                break;
        }
    }
    return status;
}



int main(int argc, char **argv){
    int i;
    func_t *functions;

    functions = (func_t *) malloc((argc-1)*sizeof(func_t)); 

    for(i = 0; i < argc - 1; i++){
        functions[i] = testfunc;
    }

    return multif(functions, argv + 1, argc -1);
}
