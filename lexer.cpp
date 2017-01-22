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
#include <cstring>
#include <regex>


//*****************************************************************************
// Do the lexical parsing
char lexeme[MAX_LEXEME_LEN];  // Character buffer for lexeme

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
        case '<': return TOK_LESSTHAN; break;
        case '>': return TOK_GREATERTHAN; break;
        case '=': return -2; break;
        case ':': return -3; break;
        default: return -1; break;
  }

}

int check_keyword_tokens(){
    if(strncmp(lexeme, "combinator", 11)==0) return TOK_COMBINATOR;
    if(strncmp(lexeme, "evaluate", 9)==0) return TOK_EVALUATE;
    if(strncmp(lexeme, "dictionary", 11)==0) return TOK_DICTIONARY;
    if(strncmp(lexeme, "set", 4)==0) return TOK_SET;
    if(strncmp(lexeme, "int", 4)==0) return TOK_INT;
    if(strncmp(lexeme, "float", 6)==0) return TOK_FLOAT;
    if(strncmp(lexeme, "string", 7)==0) return TOL_STRING;
    if(strncmp(lexeme, "and", 4)==0) return TOK_AND;
    if(strncmp(lexeme, "or", 3)==0) return TOK_OR;
    if(strncmp(lexeme, "not", 4)==0) return TOK_NOT;
    if(strncmp(lexeme, "length", 7)==0) return TOK_LENGTH;
    return -1;
}

char store_and_read_char(char c) {
  lexeme[yyleng++] = c;
  return fgetc( yyin );
}

char skip_space(char c){
  while(isspace(c)){
    if(c=='\n') yyLine++;
    c=fgetc(yyin);
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


int yylex()
{
  static char c = -1;         // Have we read the first character yet?
  //int char_type;              // Hold the character type

  // Prepare the buffer to hold the lexeme
  for( int i = 0; i < MAX_LEXEME_LEN; i++ )
    lexeme[i] = '\0';
  yytext = lexeme;
  yyleng = 0;

  // If the very first character has not yet been read, read it
  if( c < 0 )
    c = fgetc( yyin );
 
  c=skip_space(c);
  c=skip_comments(c);

  // Test for end of file
  if( feof(yyin) ) {
    // Ready for next time
    c = -1; 
    // Done!
    return( TOK_EOF );
  }

  // Store current character and read the next
  c = store_and_read_char(c);

  //there's some simple one and two character tokens
  int return_code=check_single_char_tokens(lexeme[0]);
  if(return_code>0){
    if(return_code==TOK_LESSTHAN) {
      if(c=='>') {
        c = store_and_read_char(c);
        return TOK_NOTEQUALTO;
      }
      else {
        return TOK_LESSTHAN;
      }
    }
    return return_code;
  }
  if(c=='=') {
      if(return_code==-2) {
        c = store_and_read_char(c);
        return TOK_EQUALTO;
      }
      else if(return_code==-3){
        c = store_and_read_char(c);
        return TOK_ASSIGN;
      }
  }

  //string literal
  if(lexeme[0]=='"'){
    while(c!='"'){
      c = store_and_read_char(c);

      if( feof(yyin) ) {
        // Ready for next time
        c = -1; 
        // Done!
        return( TOK_EOF_SL );
      }
    }
    c = store_and_read_char(c);
    return TOK_STRINGLIT;
  }

  //c-identifier
  if(lexeme[0]=='$' && isalpha(c)) {
    while(isalnum(c)||c=='_'){
      c = store_and_read_char(c);
    }
    return TOK_CIDENTIFIER;
  }

  //ints and floats
  if(isdigit(lexeme[0])) {
    bool is_float=false;
    while(isdigit(c)||c=='.') {
      c = store_and_read_char(c);
      if(c=='.') {
        c = store_and_read_char(c);
        is_float=true;
        break;
      }
    }
    while(isdigit(c)){
      c = store_and_read_char(c);
    }
    if(is_float) {
      return TOK_FLOATLIT;
    }
    return TOK_INTLIT;
  }

  //keywords and identifiers
  if(isalpha(lexeme[0])) {
    while(isalnum(c)||c=='_'){
      c = store_and_read_char(c);
    }
    return_code=check_keyword_tokens();
    if(check_keyword_tokens()>0) return return_code;

    return TOK_IDENTIFIER;
  }

  // We don't yet know how to recognize any lexemes
  return( TOK_UNKNOWN );
}
