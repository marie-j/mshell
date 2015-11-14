/* mshell - a job manager */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "pipe.h"

void do_pipe(char *cmds[MAXCMDS][MAXARGS], int nbcmd, int bg) {
    
    int ito,fd[2],res,status;

    if (nbcmd >= 3) {
    	unix_error("too many arguments");
    }

    for (ito = 1; ito < nbcmd; ito++)
    {
    	if (!strcmp(cmds[ito],"to"))
    	{
    		break;
    	}
    }

    if (ito < nbcmd) {
        unix_error("wrong input");
    }

    cmds[ito] = (char *) 0;

    pipe(fd);

    switch(fork()) {
        case -1 : 
            unix_error("fork cmd 1 error");

        case 0 : 
            close(fd[0]);
            dup2(fd[1],STDOUT_FILENO);
            execvp(argv[1],argv +1);
            printf("execvp error\n");
            exit(EXIT_FAILURE);

        default : 
        ;
    }

    switch(fork()) {
        case -1 :
            unix_error("fork cmd 2 error");

        case 0 : 
            close(fd[1]);
            dup2(fd[0],STDIN_FILENO);
            execvp(argv[ito +1],argv +ito +1);
            printf("execvp 2 error\n");
            exit(EXIT_FAILURE);

        default : ; 
    }

    close(fd[0]);
    close(fd[1]);
    wait(&status);

    if (WIFEXITED(status)) {
        res = WEXITSTATUS(status);
    }
    else {
        res = -1;
    }

    wait(&status);

    if (WIFEXITED(status)) {
        res |= WEXITSTATUS(status);
    }
    else {
        res = -1;
    }
    return;
}
