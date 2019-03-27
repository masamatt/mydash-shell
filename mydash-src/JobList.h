#ifndef __JOBLIST_H
#define __JOBLIST_H

#include "List.h"
#include "Node.h"
#include "mydash.h"
#include "Job.h"


typedef struct node   JobNode;     /**< JobNode typedef to node struct, obj=job                 */
typedef struct node  *JobNodePtr;  /**< JobNodePtr typedef pointer to node struct, obj=job      */
typedef struct list   JobList;     /**< JobList typedef to list struct, nodes=job nodes         */
typedef struct list  *JobListPtr;  /**< JobList typedef pointer to list struct, nodes=job nodes */



/**
 * Constructor: creates a new JobNode instance
 *
 * @param  cmd_tokens double pointer to a tokenized command
 * @param  num_tokens number of command tokens
 * @param  jpid job process number
 * @param  jnum job number
 * @param  pstatus pointer to wait status integer
 * @return pointer to a new JobNode instance
 */ 
JobNodePtr   createJobNode(char **cmd_tokens, int num_tokens,  \
                           pid_t jpid, int jnum, int *pstatus);



/**
 * Adds a JobNode instance to a JobList
 *
 * @param  jlist pointer to a JobList instance
 * @param  jnode pointer to a JobNode instance
 */ 
void           addJobNode(JobListPtr jlist, JobNodePtr jnode);



/**
 * Removes a JobNode instance from a JobList
 *
 * @param  jlist pointer to a JobList instance
 * @param  jnode pointer to a JobNode instance
 * @return pointer to the removed JobNode
 */ 
JobNodePtr     removeJobNode(JobListPtr jlist, JobNodePtr jnode);



/**
 * Free's the memory associated with a JobNode instance
 *
 * @param  jnode void pointer, cast as a JobNodePtr
 */ 
void           freeJobNode(void *jnode);



/**
 * Prints the contents of a JobList
 * 
 * @param  jlist pointer to a JobList instance
 */ 
void           printJobList(JobListPtr jlist);



/**
 * Determines the next available job ID number
 *
 * @param  jlist pointer to a JobList struct instance
 * @return next available integer job ID number
 */
int nextJobNumber(JobListPtr jlist);





#endif /* __JOBLIST_H */
