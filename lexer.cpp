//*****************************************************************************
// purpose: CSE 4713 / 6713 Assignment 1: Lexical Analyzer
// created: 8-25-2015
//  author: Paul Barrett
//*****************************************************************************
#include "lexer.h"
#include <ctype.h>
#include <assert.h>
#include <string.h>
#include <cctype>


//*****************************************************************************
// Do the lexical parsing

int check_single_char_tokens(char c){
  switch(c) {
        case ';': return TOK_SEMICOLON; break;
        case '(': return TOK_OPENPAREN; break;
        case ')': return TOK_CLOSEPAREN; break;
        case '[': return TOK_OPENBRACKET; break;
        case ']': return TOK_CLOSEBRACKET; break;
        case '{': return TOK_OPENBRACE; break;
        case '}': return TOK_CLOSEBRACE; break;
        case ',': return TOK_COMMA; break;
        case '\\': return TOK_SLASH; break;
        case '.': return TOK_DOT; break;
        case '+': return TOK_PLUS; break;
        case '-': return TOK_MINUS; break;
        case '*': return TOK_MULTIPLY; break;
        case '/': return TOK_DIVIDE; break;
        case '<': return -2; break;
        case '>': return TOK_GREATERTHAN; break;
        default: return -1; break;
  }

}

char skip_space(char c){
  while(isspace(c)){
    c=fgetc(yyin);
    if(c=='\n') yyLine++;
  }
  return c;
}

char skip_comments(char c) {
    while(1) {
      if(c=='#'){
        while(c!='\n'){
          c=fgetc(yyin);
        }
        yyLine++;
        
      }
      else{
        break;
      }
      c=fgetc(yyin);
      c=skip_space(c);
  }
  return c;

}

char lexeme[MAX_LEXEME_LEN];  // Character buffer for lexeme
int yylex()
{
  static char c = -1;         // Have we read the first character yet?
  int char_type;              // Hold the character type

  // Prepare the buffer to hold the lexeme
  for( int i = 0; i < MAX_LEXEME_LEN; i++ )
    lexeme[i] = '\0';
  yytext = lexeme;
  yyleng = 0;

  // If the very first character has not yet been read, read it
  if( c < 0 )
    c = fgetc( yyin );
 
  // Test for end of file
  if( feof(yyin) ) {
    // Ready for next time
    c = -1; 
    // Done!
    return( TOK_EOF );
  }

  c=skip_space(c);
  c = skip_comments(c);


  // Store current character and read the next
  if(c=='\n') c='~'; //neaten up error output
  lexeme[yyleng++] = c;
  c = fgetc( yyin );



  int return_code=check_single_char_tokens(lexeme[0]);
  if(return_code>0){
    if(return_code==-2) {
      if(c=='>') {
        lexeme[yyleng++] = c;
        c = fgetc( yyin );
        return TOK_NOTEQUALTO;
      }
      else {
        return TOK_LESSTHAN;
      }
    }
    return return_code;
  }




  // We don't yet know how to recognize any lexemes
  return( TOK_UNKNOWN );
}
