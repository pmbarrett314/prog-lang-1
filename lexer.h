//*****************************************************************************
// purpose: CSE 4713 / 6713 Assignment 1: Lexical Analyzer
// created: 8-25-2015
//  author: Paul Barrett
//*****************************************************************************
 
#ifndef LEXER_H
#define LEXER_H

// Include standard IO streams
#include <stdio.h>

// The lexical analyzer global variables and functions
extern int   yylex();
extern FILE *yyin;         // input stream
extern FILE *yyout;        // output stream
extern int   yyleng;       // length of current lexeme
extern char *yytext;       // text of current lexeme
extern int   yyLine;
// Maximum lexeme length
#define MAX_LEXEME_LEN 100

// List of token codes


#define TOK_COMBINATOR   1001
#define TOK_EVALUATE     1002
#define TOK_DICTIONARY   1003
#define TOK_SET          1004
#define TOK_INT          1100
#define TOK_FLOAT        1101
#define TOL_STRING       1102
#define TOK_SEMICOLON    2000
#define TOK_OPENPAREN    2001
#define TOK_CLOSEPAREN   2002
#define TOK_OPENBRACKET  2003
#define TOK_CLOSEBRACKET 2004
#define TOK_OPENBRACE    2005
#define TOK_CLOSEBRACE   2006
#define TOK_COMMA        2007
#define TOK_SLASH        3000
#define TOK_DOT          3001
#define TOK_PLUS         3002
#define TOK_MINUS        3003
#define TOK_MULTIPLY     3004
#define TOK_DIVIDE       3005
#define TOK_ASSIGN       3006
#define TOK_EQUALTO      3007
#define TOK_LESSTHAN     3008
#define TOK_GREATERTHAN  3009
#define TOK_NOTEQUALTO   3010
#define TOK_AND          3011
#define TOK_OR           3012
#define TOK_NOT          3013
#define TOK_LENGTH       3014
#define TOK_IDENTIFIER   4000
#define TOK_CIDENTIFIER  4001
#define TOK_INTLIT       4002
#define TOK_FLOATLIT     4003
#define TOK_STRINGLIT    4004
#define TOK_EOF          5000  // end of file
#define TOK_EOF_SL       5001  // end of file while parsing string literal
#define TOK_UNKNOWN      6000  // unknown lexeme

#endif

