#ifndef	__UTILITY_FUNCS_H
#define	__UTILITY_FUNCS_H

#include "JobList.h"
#include <sys/types.h>
#include "mydash.h"
#include "List.h"
#include "Node.h"
#include "Job.h"
#include "tokenFuncs.h"
#include "builtInFuncs.h"


int sig_flag;                /* signal flag  */


/**
 * Return version number based on git SHA
 */ 
const char *git_version(void);



/**
 * Print the version number of mydash shell
 *
 * @param num_args  number of command line args for ./mydash
 * @param first_arg first command line argument for ./mydash
 */ 
void printVersion(int num_args, char *first_arg);



/**
 * Initialize start-up parameters for the mydash shell
 */
void   init_mydash();



/**
 * Get the text string for the command prompt
 * 
 * @return char pointer to the prompt string
 */
char  *getPrompt();



/**
 * Analyzes the tokens given to see what type of command they represent
 * (background, builtin, ..), then calls the command through the
 * appropriate channels
 *
 * @param  toks char double pointer containing a tokenized command
 * @param  numtoks integer number of tokens contained by toks
 * @param  jlist pointer to a JobList instance
 * @return integer representation of success (0) or failure (non-zero)
 */
int    respondToTokens(char **toks, int numtoks, JobListPtr jlist);



/**
 * Checks if command requested was to be run in the background
 *
 * @param  lastToken char pointer to the last token of command tokens
 * @return integer representation, a bg job (0), a fg job (non-zero)
 */ 
int    isBGJob(char *lastToken);



/**
 * Checks if command requested is one of our builtin implementations (cd, exit, ..)
 *
 * @param  firstToken char pointer to first token of command tokens
 * @return integer representation, builtin (0), not a builtin (non-zero)
 */ 
int    isBuiltIn(char *firstToken);



/**
 * Calls (fork/exec) a non-builtin command
 *
 * @param  toks char double pointer to a tokenized command
 * @param  numtoks integer number of tokens
 * @param  pstatus integer pointer to process status
 * @param  bg_flag integer flag for background jobs bg (1), fg (0)
 * @return pid of the process
 * 
 */ 
pid_t    runJob(char **toks, int numtoks, int *pstatus, int bg_flag);



/**
 * Calls a builtin command
 *
 * @param  toks char double pointer to a tokenized command
 * @param  ntoks integer number of tokens
 * @param  jlist pointer to a JobList instance
 */ 
void   runBuiltIn(char **toks, int ntoks, JobListPtr jlist);



/**
 * Catches SIGTERM (Ctrl-D)
 */ 
void   signalTERM();



/**
 * Catches SIGINT  (Ctrl-C)
 */ 
void   signalINT();



/**
 * Catches SIGTSTP (Crtl-Z)
 */ 
void   signalTSTP();



/**
 * Handles signals: Ctrl-D, Ctrl-C, Ctrl-Z
 *
 * @param last_pid 0: for bg, child_pid: for fg
 * @param jlist pointer to a JobList struct
 */
void signalHandler(pid_t last_pid, JobListPtr jlist);



/**
 * Adds the next command to the history stack
 * <p>
 * Does not add empty commands
 *
 * @param input pointer to char input line
 */
void update_history(char *input);



/**
 * Free's the malloc'd loop variables
 *
 * @param input_line pointer to char input line
 * @param input_tokens double pointer to tokenized input line
 * @param number_of_tokens number of tokens contains in input_tokens
 */
void freeLoopVariables(char *input_line, char **input_tokens, int number_of_tokens);



#endif	/* __UTILITY_FUNCS_H */
