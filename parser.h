#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static struct token *tk;

struct exp {
	int constant;
};

struct statement {
	struct exp *stmnt;
};

struct func_decl {
	char *name;
	char *return_t;
	struct statement *body;
};

struct ast {
	struct func_decl *func;
};

int parse(struct token *t, int n_tks, struct ast *tree);

struct func_decl *parse_func();

struct statement *parse_stmnt();

struct exp *parse_exp();

void p_err(char *msg);

