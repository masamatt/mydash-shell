/*
 * Auxilary functions to manage flow control, run commands, etc
 */

#include <sys/wait.h>
#include <signal.h>
#include <stdio.h>
#include <unistd.h>            
#include <stdlib.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "tokenFuncs.h"
#include "utilityFuncs.h"



void printVersion(int num_args, char *first_arg)
{
    if (num_args == 2 && (strcmp(first_arg,"-v") == 0)) {
        printf("mydash v%s\n",git_version());
        exit(0);
    }
    return;
}



void init_mydash()
{
    using_history();                  // initialize readline: history
    sig_flag = 0;                     // signal flag initialize to 0
    signal(SIGTERM, signalTERM);      // set signal: Ctrl-D
    signal(SIGINT,  signalINT);       //             Ctrl-C
    signal(SIGTSTP, signalTSTP);      //             Ctrl-Z
}



char *getPrompt()
{
    char *msh_prompt = getenv("DASH_PROMPT");    // custom prompt
    if (!msh_prompt) {
        msh_prompt   = (char *)malloc(sizeof(char)*8);
        strcpy(msh_prompt, "[msh]$ ");           // default prompt
        msh_prompt[7] = '\0';
    }
    return msh_prompt;
}



int isBGJob(char *lastToken)
{
    int bgflag = 0;
    if (strrchr(lastToken,'&'))
        bgflag = 1;
    return bgflag;
}



int isBuiltIn(char *tok1)
{
    int builtin_flag = 0;
    if ((strcmp(tok1,"exit") == 0) || (strcmp(tok1,"cd") == 0) ||       \
        (strcmp(tok1,"jobs") == 0) || (strcmp(tok1,"history") ==0)) 
        builtin_flag = 1;
    return builtin_flag;
}



int respondToTokens(char **toks, int numtoks, JobListPtr jlist)
{
    pid_t pid_stat = -1;     // initialize -1: -> num_tokens = 0
    
    // empty command
    if (numtoks == 0) return pid_stat;     

    // built-in command
    if (isBuiltIn(toks[0]) == BUILTIN_CMD)
        runBuiltIn(toks, numtoks, jlist);
    
    // non-built-in command
    else {
        int     bg_flag        = isBGJob(toks[numtoks-1]);
        char  **copy_toks      = copyTokens(toks, numtoks);        
        int    *process_status = (int *) malloc(sizeof(int));
        pid_t   job_pid        = runJob(toks, numtoks, process_status, bg_flag);

        // background job
        if (bg_flag == BG_JOB) {
            int    job_num = nextJobNumber(jlist);
            JobNodePtr jnp = createJobNode(copy_toks,numtoks,job_pid,job_num,process_status);
            addJobNode(jlist,jnp);
            printf("%s\n",startJobToString(jnp->obj));
            pid_stat = 0;

        // foreground job
        } else {
            pid_stat = job_pid;            
            free(copy_toks);
            free(process_status);
        }
    }
    return(pid_stat);
}




pid_t runJob(char **toks, int numtoks, int *pstatus, int bg_flag)
{
    pid_t cpid, wpid;

    if (bg_flag  == BG_JOB) {
        toks[numtoks-1] = trimTokenBG(toks[numtoks-1]);
        toks[numtoks]   = '\0';
    }
    

    cpid = fork();
    if (cpid < 0)                             /* fork   */
        err_sys("fork error");

    else if (cpid == 0) {                     /* child  */
        execvp(toks[0], toks);
        err_ret("couldn't execute: %s", toks[0]);
        exit(EXIT_FAILURE);
        
    } else {                                       /* parent */
        if (bg_flag == BG_JOB)
            wpid = waitpid(cpid, pstatus, WNOHANG);
        else
            wpid = waitpid(cpid, pstatus, 0);
        
        if ( wpid < 0)
            err_sys("waitpid error");
    }
    return cpid;
}




void runBuiltIn(char **toks, int ntoks, JobListPtr jlist) 
{
    char *firstToken = toks[0];
            
    if (strcmp(firstToken, "exit") == 0) {            // exit
        mydash_exit(toks, ntoks, jlist);

    } else if (strcmp(firstToken, "cd") == 0) {        // cd
        mydash_cd(toks[1]);    


    } else if (strcmp(firstToken, "jobs") == 0) {      // jobs
        printJobList(jlist);
    
    } else if (strcmp(firstToken, "history") == 0 ) { // history
        mydash_history();

    } else {
        printf("other: you should not have landed here.\n");
    }
}



void signalTERM()
{
    sig_flag = 1;
}



void signalINT()
{
    sig_flag = 2;
}



void signalTSTP()
{
    sig_flag = 3;
}



void signalHandler(pid_t last_pid, JobListPtr jlist)
{
    switch(sig_flag) {
        case 0:                // no signal
            break;
        case 1:                // SIGTERM (Ctrl-D)
            if (last_pid > 0)  kill(last_pid, SIGTERM);
            freeList(jlist);
            exit(EXIT_SUCCESS);
            break;
        case 2:                // SIGINT  (Ctrl-C)
            if (last_pid > 0)  kill(last_pid, SIGTERM);            
            else               printf("Caught Control-c\n");
            sig_flag = 0;
            signal(SIGINT,signalINT);
            break;
        case 3:                // SIGTSTP (Ctrl-Z)
            if (last_pid > 0)  kill(last_pid, SIGTSTP);            
            else               printf("Caught Ctrl-z\n");
            sig_flag = 0;
            signal(SIGTSTP,signalTSTP);
            break;
        default:
            printf("Invalid signal: %d\n",sig_flag);
            break;
    }
    return;
}



void update_history(char *input)
{
    char  *hist_line;
    size_t input_length = strlen(input);
    if (input_length != 0)
    {
        hist_line = (char *) malloc(sizeof(char)*(input_length+1));
        strcpy(hist_line,input);
        hist_line[input_length] = '\0';
        add_history(hist_line);
    }
    return;
}



void freeLoopVariables(char *input_line, char **input_tokens, int number_of_tokens)
{
    free(input_line);
    freeTokens(input_tokens, number_of_tokens);
    return;
}

    
