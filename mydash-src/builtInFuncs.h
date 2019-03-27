#ifndef __BUILTINFUNCS_H
#define __BUILTINFUNCS_H

#include "JobList.h"
#include "mydash.h"



/**
 * Implementation of the cd (change directory) command.
 * <p>
 * If the command <code>cd</code> is issued without a directory
 * input argument, then the shell will move to the default
 * location of <code>/home/$USER</code>
 *
 * @param  token_dir char pointer to a directory path
 * @return integer indication of success (0) or failure (non-zero)
 */ 
int  mydash_cd(char *token_dir);



/**
 * Implementation of the exit command.
 *<p>
 * This command cleans up, then calls exit
 *
 * @param  tokens double char pointer to command tokens
 * @param  numTokens number of command tokens
 * @param  joblist pointer to a JobList struct instance
 * @return integer indication of success (0) or failure (non-zero)
 */ 
int  mydash_exit(char **tokens, int numTokens, JobListPtr joblist);



/**
 * Implementation of the history command.
 * <p>
 * Prints a numbered list of commands entered during the session. 
 *
 * @return integer indication of success (0) or failure (non-zero)
 */
int  mydash_history();


#endif /* __BUILTINFUNCS_H  */
