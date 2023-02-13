/* mshell - a job manager */


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "common.h"
#include "pipe.h"
#include "jobs.h"
#include "sighandlers.h"
#include "cmd.h"


void do_pipe(char *cmds[MAXCMDS][MAXARGS], int nbcmd, int bg) {
    int fd[2];
    int i;
    int input; /* placeholder for input */
    pid_t pid, pgid;
    input = STDIN_FILENO;

    pgid = 0; /* init for group id */
    for(i=0; i < nbcmd; i++){
        assert(pipe(fd) != -1);
        switch(pid = fork()){
            case -1:
                unix_error("fork error");
            case 0:
                if(setpgid(0,pgid) < 0) unix_error("setpgid error");
                dup2(input, STDIN_FILENO); /* copying STDIN_FILENO in input file descriptor if the descriptors are different */
                if(i < nbcmd - 1){
                    dup2(fd[1], STDOUT_FILENO); /* if the last command -> the output remains on stdout */
                }

                close(fd[0]);

                execvp(cmds[i][0], cmds[i]);
                printf("%s: Command not found\n", cmds[i][0]);
                exit(EXIT_FAILURE);
            default:
                if(i == 0) pgid = pid;
                close(fd[1]);
                input = fd[0];
        }
    }
    
    assert(jobs_addjob(pgid, (bg == 1 ? BG : FG), cmds[0][0]) == 1);

    for(i=0; i < nbcmd; i++){
        wait(NULL);
    }
    return;
}
