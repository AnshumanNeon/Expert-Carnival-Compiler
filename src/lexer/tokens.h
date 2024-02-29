#pragma once

#ifndef TOKEN_DEF

#define TOKEN_DEF

// tokens

enum
  {
    ADDITION_TOKEN,
    SUB_TOKEN,
    MUL_TOKE,
    DIV_TOKEN,
    MOD_TOKEN,
    EXP_TOKEN,
    EQUAL_TOKEN,

    // comparison
    EQUAL_COMP_TOKEN,
    GREATER_THAN_TOKEN,
    LESSER_THAN_TOKEN,
    NOT_EQUAL_TOKEN,
    NOT_TOKEN,
    AND_TOKEN,
    OR_TOKEN,
  } oprator_tokens;

enum
  {
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
    FALSE_TOKEN
  } keyword_tokens;

enum
  {
    INT_TOKEN,
    FLOAT_TOKEN,
    STR_TOKEN,
    BOOL_TOKEN
  } var_type_type;

enum
  {
    COMMENT_TOKEN,
    BRACKETS_TOKEN,
    SEMICOLON_TOKEN,
  } symbol_token;

#endif
