/*
 *      Job.h: Defines a job object struct and associated methods.
 */ 

#ifndef __JOB_H
#define __JOB_H

#include <sys/types.h>
#include "mydash.h"


typedef struct job  Job;    /**< Job typedef to job struct                        */
typedef struct job *JobPtr; /**< JobPtr typedef pointer to job struct             */



/**
 * @brief job struct definition
 * <p>
 * Holds information for different facets of a command submitted for a job.
 *
 */ 
struct job {
    pid_t   pid;            /**< pid, type pid_t, system-wide process ID number    */
    int     num;            /**< num, type int, mydash internal job ID number      */
    int     ntoks;          /**< ntoks, type int, number of tokens                 */
    char  **toks;           /**< toks, type char double pointer, tokenized command */
    int    *pstatus;        /**< pstatus, type int pointer, gives process status   */
};



/**
 * Constructor:  Allocates a new background (BG) Job struct object and
 * initializes its members.
 *
 * @param  cmd_tokens double char pointer to tokenized command string
 * @param  num_tokens integer number of tokens in <code>cmd_tokens</code>
 * @param  jpid job pid
 * @param  jnum job number
 * @param  pstatus pointer to integer process status
 * @return pointer to the Job struct instance
 */
JobPtr createJobBG(char **cmd_tokens, int num_tokens,  \
                   pid_t jpid, int jnum, int *pstatus);



/**
 * Creates and returns a text string representation of a command.
 * 
 * @param   job_obj (void *) cast to Job struct instance 
 * @return  char pointer to command string
 */ 
char  *cmdToString(const void *job_obj);



/**
 * Creates and returns a summary string for a job just starting in the background
 * 
 * @param   job_obj (void *) cast to Job struct instance
 * @return  char pointer to a bg job start-up message
 */ 
char  *startJobToString(const void *job_obj);



/**
 * Free's the memory associated with Job struct instance
 * 
 * @param job_obj (void *) cast to Job struct instance
 */ 
void   freeJob(void *job_obj);



/**
 * Equality comparison given two job instances.
 * <p>
 * The <code>pid</code> Job instance parameter is compared between the
 * two Jobs to determine if they are equal
 * 
 * @param  job_obj1 (void *) cast to 1st Job struct instance
 * @param  job_obj2 (void *) cast to 2nd Job struct instance
 * @return integer <code>1</code> if true, and <code>0</code> if false
 */ 
int    jobEquals(const void *job_obj1, const void *job_obj2);



/**
 * Creates and returns a summary string for a background job
 * 
 * @param  job_obj (void *) cast to Job struct instance
 * @return char pointer to a bg job string message
 */ 
char  *jobToString(const void *job_obj);



/**
 * Get the status of a background job
 *
 * @param   job pointer to a Job struct instance
 * @return  integer status representation
 */
int    getJobStatus(JobPtr job);



/**
 * Gets a string representation of the job status
 * 
 * @param   job pointer to a Job struct instance
 * @return  char pointer to a status string (Running, Done)
 */ 
char  *jobStatusToString(JobPtr job);



/**
 * Gets a background job ID number
 * 
 * @param   job pointer to a Job struct instance
 * @return  integer job number
 */ 
int    getJobNum(JobPtr job);




/**
 * Gets a background job Process ID (PID) number
 * 
 * @param   job pointer to a Job struct instance
 * @return  job <code>pid</code>, type <code>pid_t</code>
 */ 
pid_t  getJobPID(JobPtr job);


#endif /* __JOB_H */
