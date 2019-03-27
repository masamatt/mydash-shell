/*
 * JobList structure + functions
 */
#include "JobList.h"



int nextJobNumber(JobListPtr jlist)
{
    int next_num = 0;
    if (getSize(jlist) != 0)
        next_num = getJobNum(jlist->tail->obj);
    return ++next_num;
}



JobNodePtr createJobNode(char **cmd_tokens, int num_tokens,  \
                         pid_t jpid, int jnum, int *pstatus)
{
    JobPtr newJob  = createJobBG(cmd_tokens, num_tokens, jpid, jnum, pstatus);
    return createNode(newJob);
}



void addJobNode(JobListPtr jlist, JobNodePtr jnode)
{
    addAtRear(jlist, jnode);
    return;
}



JobNodePtr  removeJobNode(JobListPtr jlist, JobNodePtr jnode)
{
    return removeNode(jlist, jnode);
}



void freeJobNode(void *jnode)
{
    freeNode((JobNodePtr) jnode, freeJob);
    return;
}



void printJobList(const JobListPtr jlist)
{
    printList(jlist);
    return;
}


