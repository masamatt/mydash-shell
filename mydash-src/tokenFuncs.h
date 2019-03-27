#ifndef __TOKENFUNCS_H
#define __TOKENFUNCS_H

#include "mydash.h"



/**
 * Wrapper function for function, parseInput(...)
 * <p>
 * Purpose is only to integrate/hide the null termination of
 * the output double pointer to tokens
 *
 * @param  s a string to be tokenized
 * @param  delimiter the characters on which to split the string
 * @param  numTokens number of tokens
 * @return char double pointer to tokens
 */ 
char **parseInputToTokens(char *s, char *delimiter, int *numTokens);



/**
 * Parses a string (s) into tokens based on the delimiters (delimiter) given.
 * <p>
 * The number of token generated is available in the pointer to int argument,
 * numTokens. This function is used unmodified from string-ex4.c
 *
 * @param  s a string to be tokenized
 * @param  delimiter the characters on which to split the string
 * @param  numTokens number of tokens
 * @return char double pointer to tokens
 */ 
char **parseInput(char *s, char *delimiter, int *numTokens);



/**
 * Free's the memory associated with tokens
 *
 * @param  toks char double pointer to tokens
 * @param  numtoks integer number of tokens
 */ 
void   freeTokens(char **toks, int numtoks);



/**
 * Trim the background job character (&) from the end of token
 *
 * @param  tok char pointer to a token
 * @return char pointer to token without background job character
 */ 
char  *trimTokenBG(char *tok);



/**
 * Make a copy of a set of tokens
 *
 * @param  toks char double pointer to tokens
 * @param  numtoks number of tokens in toks
 * @return char double pointer to a copy of the original tokens
 */ 
char **copyTokens(char **toks, int numtoks);



/**
 * Print string representation of a set of tokens to the terminal
 *
 * @param  toks char double pointer to tokens
 * @param  numtoks number of tokens in toks
 */ 
void   printTokens(char **toks, int numtoks);

#endif /* __TOKENFUNCS_H */
