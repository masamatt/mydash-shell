/*
 * Job struct and methods
 */

#include <string.h>
#include "utilityFuncs.h"
#include "tokenFuncs.h"
#include "Job.h"



JobPtr createJobBG(char **cmd_tokens, int num_tokens,  \
                   pid_t jpid, int jnum, int *pstatus)
{
    JobPtr newJob   = (JobPtr)  malloc(sizeof(Job));
    newJob->toks    = (char **) malloc(sizeof(char *) * num_tokens);

    int i;
    for(i=0; i < num_tokens; i++)  
    {                              
        newJob->toks[i] = (char *) malloc(sizeof(char)*(strlen(cmd_tokens[i])+1));
        strcpy(newJob->toks[i], cmd_tokens[i]);
    }
    newJob->ntoks    =   num_tokens;    
    newJob->num      =   jnum;
    newJob->pid      =   jpid;    
    newJob->pstatus  =   pstatus;

    return newJob;
}



char *cmdToString(const void *job)
{
    JobPtr thisJob = (JobPtr) job;
    char  *cmd_str = (char *) malloc(sizeof(char)*(MAX_TOK_SIZE+1));
    cmd_str[0]     = '\0';

    int i;
    for(i = 0; i < thisJob->ntoks; i++)
    {
        strcat(cmd_str, thisJob->toks[i]);
        strcat(cmd_str, " ");
    }
    
    return cmd_str;
}



/* print for bg job start up */
char *startJobToString(const void *job)
{
    int FORMAT_CHARS  = 20;
    int BUF_SIZE      = MAX_TOK_SIZE + FORMAT_CHARS;
    JobPtr thisJob    = (JobPtr) job;
    char  *cmd_str    = cmdToString(thisJob);    
    char  *job_str    = (char *) malloc(sizeof(char)*BUF_SIZE);
    job_str[0]        = '\0';

    snprintf(job_str,BUF_SIZE,"[%d] %d %s",thisJob->num,thisJob->pid,cmd_str);
    job_str[strlen(job_str)-1] = '\0';
    
    free(cmd_str);
    
    return job_str;
}



void freeJob(void *job)
{
    JobPtr thisJob = (JobPtr) job;
    freeTokens(thisJob->toks, thisJob->ntoks);
    free(thisJob);
}



int jobEquals(const void *job1, const void *job2)
{
    JobPtr jp1 = (JobPtr) job1;
    JobPtr jp2 = (JobPtr) job2;

    return jp1->pid == jp2->pid;
}



/* print for 'jobs' call */
char *jobToString(const void *job)
{
    int FORMAT_CHARS  = 20;
    int BUF_SIZE      = MAX_TOK_SIZE + FORMAT_CHARS;
    
    JobPtr thisJob    = (JobPtr) job;
    char  *cmd_str    = cmdToString(thisJob);
    char  *stat_str   = jobStatusToString(thisJob);
    char  *job_str    = (char *) malloc(sizeof(char)*BUF_SIZE);
    job_str[0]        = '\0';
        
    snprintf(job_str,BUF_SIZE,"[%d] %s %s",thisJob->num,stat_str,cmd_str);
    job_str[strlen(job_str)-1] = '\0';
    
    free(cmd_str);
    free(stat_str);
    
    return job_str;
}



int getJobStatus(JobPtr job)
{
    int stat = -1;                      // < 0: error
    
    if (!WIFEXITED(*(job->pstatus)))    
        stat = 0;                       // = 0: still running
    else
        stat = 1;                       // > 0: done

    return stat;
}



char *jobStatusToString(JobPtr job)
{
    int run_status = 0;
    int STAT_STR_SIZE = 7;
    char *statstring  = (char *)malloc(sizeof(char)*(STAT_STR_SIZE+1));

    run_status = getJobStatus(job);
    
    if (run_status == 0)                   // = 0: still running
        strcpy(statstring,"Running");         
    else if (run_status > 0)               // > 0: done        
        strcpy(statstring,"Done   ");    
    else                                   // < 0: error
        strcpy(statstring,"Error  ");
    statstring[STAT_STR_SIZE] = '\0';

    return statstring;
}



int getJobNum(JobPtr job)
{
    return job->num;
}



pid_t getJobPID(JobPtr job)
{
    return job->pid;
}

