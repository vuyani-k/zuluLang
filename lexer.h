#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "tokens.h"

int lex(FILE *fp, struct token *tokens);

int get_no_of_tokens(FILE *fp);

int tokenize(FILE *fp, struct token *tokens);

enum err_t {sys_err, syn_err, unexpected_err};

void lex_error(char *msg, enum err_t err, FILE *fp, char *token);

void error(char *msg, enum err_t err);

void print_tokens(char* tk);

