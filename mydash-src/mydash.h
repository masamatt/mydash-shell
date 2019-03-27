#ifndef	__MYDASH_H
#define	__MYDASH_H

#include	<sys/types.h>	    /* required for some of our prototypes */
#include	<sysexits.h>
#include	<stdio.h>	
#include	<stdlib.h>		
#include	<string.h>
#include	<unistd.h>	


#define MAX_TOKS        100         /* max number of tokens per line */
#define MAX_TOK_SIZE   2048         /* max token length */
#define	MAXLINE	       4096	    /* max line length */
#define MAX_PROMPT       50      
#define BG_JOB            1         /* Background job                 */
#define FG_JOB            0         /* Foreground job                 */
#define BUILTIN_CMD       1
#define NONBUILTIN_CMD    0


/* default file access permissions for new files */
#define	FILE_MODE      (S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)
/* default permissions for new directories */					
#define	DIR_MODE       (FILE_MODE | S_IXUSR | S_IXGRP | S_IXOTH)


/* prototypes for error handling functions */
void	err_dump(const char *, ...);
void	err_msg(const char *,  ...);
void	err_quit(const char *, ...);
void	err_ret(const char *,  ...);
void	err_sys(const char *,  ...);


#endif	/* __MYDASH_H */
