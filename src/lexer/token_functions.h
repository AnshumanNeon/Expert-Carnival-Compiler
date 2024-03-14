#include "./tokens.h"

Token convert_to_operator_token()
{
  Token token;
  token.token_type = 0;
  token.token[token.token_type] = ADDITION_TOKEN;

  return token;
}

Token convert_to_keyword_token()
{
  Token token;
  token.token_type = 1;
  token.token[token.token_type] = TRUE_TOKEN;

  return token;
}

Token convert_to_var_type_token()
{
  Token token;
  token.token_type = 2;
  token.token[token.token_type] = BOOL_TOKEN;

  return token;
}

Token convert_to_symbol_token()
{
  Token token;
  token.token_type = 3;
  token.token[token.token_type] = COMMENT_TOKEN;

  return token;
}
