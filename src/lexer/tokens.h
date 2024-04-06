#pragma once
#include <stdlib.h>

typedef enum {
  // operator tokens
  // -----
  ADDITION_TOKEN,
  SUB_TOKEN,
  MUL_TOKEN,
  DIV_TOKEN,
  MOD_TOKEN,
  EXP_TOKEN,
  EQUAL_TOKEN,

  // Brackets
  LEFT_PAREN_TOKEN, // (
  RIGHT_PAREN_TOKEN, // )
  LEFT_BRACE_TOKEN, // {
  RIGHT_BRACE_TOKEN, // }
  LEFT_SQR_PAREN_TOKEN, // [
  RIGHT_SQR_PAREN_TOKEN, // ]

  DOT_TOKEN, // .

  // comparison
  EQUAL_EQUAL_TOKEN,
  GREATER_OR_EQUAL_TOKEN,
  LESSER_OR_EQUAL_TOKEN,
  GREATER_THAN_TOKEN,
  LESSER_THAN_TOKEN,
  NOT_EQUAL_TOKEN,
  NOT_TOKEN,
  AND_TOKEN,
  AND_OR_TOKEN,
  OR_TOKEN,
  
  //keyword tokens
  // -----
  // functions
  FUNC_TOKEN,
  RETURN_TOKEN,

  ARRAY_TOKEN,

  // definition
  VAR_TOKEN,
  CONST_TOKEN,

  // conditions
  IF_TOKEN,
  ELSE_TOKEN,

  // loops
  WHILE_TOKEN,
  FOR_TOKEN,

  // switch-case
  CASE_TOKEN,
  DEFAULT_TOKEN,
  SWITCH_TOKEN,

  // bools
  TRUE_TOKEN,
  FALSE_TOKEN,

  // var type tokens
  // ---
  INT_TOKEN,
  FLOAT_TOKEN,
  STR_TOKEN,
  BOOL_TOKEN,

  // symbol tokens
  // ----
  COMMENT_TOKEN,
  BRACKETS_TOKEN,
  SEMICOLON_TOKEN,

  // error token
  // ---
  ERROR_TOKEN,
} token_type;

typedef struct
{
  token_type type;
  char* token;

  // debug info
  unsigned int line, col;
} Token;

typedef struct
{
  Token* tokens;
  unsigned int length;

  unsigned int MAX_SIZE;
} Tokens;

Tokens init_token() {
  Tokens tokens;

  // allocate
  tokens.MAX_SIZE = 50;
  tokens.tokens = (Token*)malloc(tokens.MAX_SIZE * sizeof(Token));

  // set length
  // 0 because no element is set right now
  tokens.length = 0;

  return tokens;
}

void free_tokens(Tokens tokens) {
  free(tokens.tokens);
  tokens.length = 0;
}

Tokens realloc_list(Tokens tokens) {
  if(tokens.length > tokens.MAX_SIZE) {
    tokens.MAX_SIZE = tokens.MAX_SIZE * 2;
    tokens.tokens = (Token*)realloc(tokens.tokens, tokens.MAX_SIZE * sizeof(Token));
  }

  return tokens;
}

Tokens add_token(Tokens tokens, token_type type, char* token, unsigned int line, unsigned int col) {
  Token new_token;
  new_token.type = type;
  new_token.token = token;
  new_token.line = line;
  new_token.col = col;
  
  tokens.tokens[tokens.length] = new_token;
  tokens.length = tokens.length + 1;

  tokens = realloc_list(tokens);
  
  return tokens;
}
