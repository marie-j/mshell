/* mshell - a job manager */

#include <stdio.h>
#include <string.h>
#include "pipe.h"

void do_pipe(char *cmds[MAXCMDS][MAXARGS], int nbcmd, int bg) {
    
    int ito,fd[2],res;

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

    return;
}
