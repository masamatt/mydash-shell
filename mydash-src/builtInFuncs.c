/*
 * Built in function: mydash implementation
 */

#include <sys/types.h>
#include <stdlib.h>
#include <pwd.h>
#include <stdio.h>           
#include <string.h>
#include <unistd.h>      
#include <dirent.h>       
#include <errno.h>          
#include <readline/readline.h>
#include <readline/history.h>
#include "tokenFuncs.h"
#include "builtInFuncs.h"




int  mydash_exit(char **tokens, int numTokens, JobListPtr joblist)
{
    freeList(joblist);
    freeTokens(tokens,numTokens);
    exit(EXIT_SUCCESS);
}



int mydash_cd(char *token_dir)
{
    int   chdir_status;
    char  cwd_buf[MAX_TOK_SIZE];
    DIR  *dir;

    if (!token_dir) {                           // cd without arg, get user home
        struct passwd *p;            
        p = getpwuid(getuid());
        token_dir = p->pw_dir;
    }
    
    dir = opendir(token_dir);                   // open dir to check existence
    if (dir) {                           
        closedir(dir);                          // dir exists, close it
        chdir_status = chdir(token_dir);        // change directory
        
        if (chdir_status != 0) {                // check: chdir status
            printf("error: non-zero exit status, directory: %s\n",token_dir);
        }
        
        getcwd(cwd_buf, sizeof(cwd_buf));       // get/print current working directory
        printf("%s\n",cwd_buf);
        
    } else if (ENOENT == errno) {               // dir does not exist
        printf("error: %s does not exist.\n",token_dir);
    } else {                                    // opendir() unknown failure
        printf("error: opendir(%s), unknown failure.\n",token_dir);
    }
    return(0);
}



int mydash_history()
{
    register HIST_ENTRY **mydash_hist_list;
    register int i;

    mydash_hist_list = history_list();
    if (mydash_hist_list) {
        for (i=0; mydash_hist_list[i]; i++)
            printf("%d %s\n", i+history_base, mydash_hist_list[i]->line);
    }
    return(0);
}

