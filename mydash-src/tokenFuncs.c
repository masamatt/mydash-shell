/*
 * Auxilary functions for working with tokens.
 */

#include <string.h>
#include <stdlib.h>
#include "tokenFuncs.h"



char **parseInputToTokens(char *s, char *delimiter, int *numTokens)
{
    char **toks = parseInput(s, delimiter, numTokens);
    toks[*numTokens] = '\0';
    return toks;
}

    

char **parseInput(char *s, char *delimiter, int *numTokens) 
{
    char  *nextToken;
    char **token = (char **) malloc (sizeof(char *) * MAX_TOKS);    

    /* tokenize the string s */
    nextToken = strtok(s, delimiter);
    *numTokens = 0;
    while (nextToken != NULL) {
        token[*numTokens] = (char *) malloc(sizeof(char) * (strlen(nextToken)+1));
        strcpy(token[*numTokens], nextToken);
        (*numTokens)++;
        nextToken = strtok(NULL, delimiter);
    }
    /*Now the tokens are copied into token[0..numTokens-1];*/
    return token;
}



void freeTokens(char **toks, int numtoks)
{
    int i;
    for(i=0; i < numtoks; i++) { free(toks[i]); }
    free(toks);
}



char *trimTokenBG(char *tok)
{
    char   *trim_tok;
    char   *cpos      = (char *) malloc(sizeof(char)*strlen(tok));
    size_t  clen      = 0;
    
    cpos = strrchr(tok,'&');                 // char position:  '&'
    clen = strlen(tok);                      // char length:    token
    
    if ( cpos && (clen == 1) )               // only the '&'
    {
        trim_tok = (char *) malloc(sizeof(char));        
        trim_tok = '\0';
        
    } else if (cpos && (clen > 1)) {         // more than just '&'
        trim_tok = (char *) malloc(sizeof(char)*clen);
        memset(trim_tok, '\0', (int) clen);
        strncpy(trim_tok,tok,clen-1);
        trim_tok[clen-1] = '\0';
    }
//    free(cpos);
    
    return trim_tok;
}



char **copyTokens(char **toks, int numtoks)
{
  char  **copy_toks  =  (char **) malloc(sizeof(char *) * numtoks);
  int i;
  for(i=0; i < numtoks; i++)
  {
      copy_toks[i]  = (char *) malloc(sizeof(char)*(strlen(toks[i])+1));
      strcpy(copy_toks[i], toks[i]);
  }
  return copy_toks;
}



void   printTokens(char **toks, int numtoks)
{
    int i;
    for(i=0; i<numtoks; i++)
    {
        printf("[%d] %s.\n",i,toks[i]);
    }
    return;
}

