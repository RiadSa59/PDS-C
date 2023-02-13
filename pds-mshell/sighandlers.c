/* mshell - a job manager */

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <signal.h>
#include <sys/wait.h>
#include <errno.h>
#include <unistd.h>


#include "jobs.h"
#include "common.h"
#include "sighandlers.h"

/*
 * wrapper for the sigaction function
 */
int sigaction_wrapper(int signum, handler_t * handler) {
    struct sigaction sa;
    sa.sa_handler = handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_RESTART;
    if(sigaction(signum, &sa, NULL) < 0){
        perror("SIGNAL HANDLING ERROR");
    }
    return 1;
}

/*

 * sigchld_handler - The kernel sends a SIGCHLD to the shell whenever
 *     a child job terminates (becomes a zombie), or stops because it
 *     received a SIGSTOP or SIGTSTP signal. The handler reaps all
 *     available zombie children
 */
void sigchld_handler(int sig) {
    pid_t pid;
    int status;
    struct job_t *j;

    pid = waitpid(-1, &status, WNOHANG | WUNTRACED);

    if(pid > 0){
        if(WIFEXITED(status)){
          /* le fils s'est terminé normalement */
          /* if(verbose) printf("\nJob finished successfully\n"); fflush(stdout); */
          jobs_deletejob(pid);

          /* write error message if any */
        }

        if(WIFSIGNALED(status)){
          /* le fils s'est terminé à cause d'un signal non intercepté. */
          if(WTERMSIG(status) == SIGINT || WTERMSIG(status) == SIGTERM 
                                        || WTERMSIG(status) == SIGKILL){
            /* if(verbose) printf("Job killed successfully\n"); fflush(stdout);*/
            jobs_deletejob(pid);
          }

        }
        if(WIFSTOPPED(status)){
          /*  le  fils est actuellement arrêté. */
          /* if(verbose) printf("Job suspended successfully\n"); fflush(stdout);*/
          j = jobs_getjobpid(pid);
          j->jb_state = ST;
        }
    }


    return;
}

/*
 * sigint_handler - The kernel sends a SIGINT to the shell whenver the
 *    user types ctrl-c at the keyboard.  Catch it and send it along
 *    to the foreground job.
 */
void sigint_handler(int sig) {
    pid_t pid;


    if((pid = jobs_fgpid()) > 0){
        if(verbose){
            printf("\nmshell: terminating the job [%d]  %d\n", jobs_pid2jid(pid), pid);
            fflush(stdout);
        }


        pid = getpgid(pid);
        if(killpg(pid, SIGINT) < 0){
            unix_error("FAILED TO KILL");
        }


        if(verbose){
            printf("mshell: job [%d] %d terminated successfully \n", jobs_pid2jid(pid), pid);
            fflush(stdout);
        }
    }

    return;
}

/*
 * sigtstp_handler - The kernel sends a SIGTSTP to the shell whenever
 *     the user types ctrl-z at the keyboard. Catch it and suspend the
 *     foreground job by sending it a SIGTSTP.
 */
void sigtstp_handler(int sig){
  pid_t pid;

  if((pid = jobs_fgpid()) > 0){
      if(verbose){
          printf("\nmshell: suspending the job [%d] \n", jobs_pid2jid(pid));
          fflush(stdout);
      }


      pid = getpgid(pid);
      if(killpg(pid, SIGTSTP) < 0){
          unix_error("FAILED TO STOP");
      }


      if(verbose){
          printf("mshell: job [%d] %d suspended successfully \n", jobs_pid2jid(pid), pid);
          fflush(stdout);
      }
  }

  return;
}
