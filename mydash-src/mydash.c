/*
 * Main program for mydash shell implementation.  Needs error.c and mydash.h to compile. 
 */

#include "utilityFuncs.h"
#include "mydash.h"
#include <signal.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <List.h>
#include <Node.h>
#include "JobList.h"
#include "tokenFuncs.h"



int main(int argc, char **argv)
{
    printVersion(argc, argv[1]);

    char      *line;
    char     **tokens      = '\0';
    char      *delimiter   = " ;";        
    int        num_tokens  = 0;
    pid_t      last_pid    = 0;
    char      *prompt      = getPrompt();
    JobListPtr joblist     = createList(jobEquals, jobToString, freeJob);

    init_mydash();


    while ((line = readline(prompt))) {
        if (sig_flag) signalHandler(last_pid, joblist);

        update_history(line);

        tokens   = parseInputToTokens(line, delimiter, &num_tokens);
        last_pid = respondToTokens(tokens, num_tokens, joblist);
        if (last_pid == -1) continue;   // empty command

        freeLoopVariables(line,tokens,num_tokens);
    }
    freeList(joblist);
    exit(EXIT_SUCCESS);
}

