#include "parser.h"
#include "tokens.h"

int
parse(struct token *t, int n_tks, struct ast *tree){

	printf("\nparsing tokens...\n\n");

	//traversing first token
	tk = t;
	tree->func = parse_func();

	return 1;
}

struct
func_decl *parse_func(){

	struct func_decl *fd;

	//type iden
	///TODO: free tk after assigned
	if(tk->type != IDEN)
		p_err("not a valid method type identifier");

	if(strcmp(tk->tk,"int") != 0)
		p_err("not a recognized method type");
	
	char *ft = malloc(sizeof(tk->tk));
	fd = malloc(sizeof(struct func_decl));
	if(fd == NULL || ft == NULL)
		p_err("unable to allocate memory for method type identifier");

	memcpy(ft, tk->tk, sizeof(tk->tk));
	fd->return_t = ft;

	tk++;

	//name iden
	if(tk->type != IDEN)
		p_err("method has an invalid signature, \
				expected a method name");

	if(strlen(tk->tk) <= 0)
		p_err("method has an invalid signature, \
				expected a method name");

	//get function name
	char *fn = malloc(sizeof(tk->tk));
	if(fn == NULL)
		p_err("unable to allocate memory for method name identifier");

	memcpy(fn, tk->tk, sizeof(tk->tk));
	fd->name = fn;
	tk++;

	//open paren
	if(tk->type != OPEN_PAREN)
		p_err("method has an invalid signature, expected (");

	if(tk->tk[0] != '\0')
		printf("method has an invalid signature, expected (");

	tk++;

	//closed paren
	if(tk->type != CLOSE_PAREN)
		p_err("method has an invalid signature, expected )");

	if(tk->tk[0] != '\0')
		p_err("method has an invalid signature, expected )");

	tk++;

	//colon
	if(tk->type != COLON)
		p_err("method has an invalid signature, expected :");

	if(tk->tk[0] != '\0')
		p_err("method has an invalid signature, expected :");

	tk++;

	//start of func body
	if(tk->type != TAB)
		p_err("invalid syntax, expected TAB");

	tk++;

	fd->body = parse_stmnt();

	printf("function parsed \n \n");

	return fd;

}

struct
statement *parse_stmnt(){

	struct statement *s;

	//buyisa - return
	if(tk->type != RETURN)
		p_err("method missing return statement");

	if(strcmp(tk->tk, "buyisa") != 0)
		p_err("method missing return statement");

	tk++;

	//parse expression
	s = malloc(sizeof(struct statement));
	s->stmnt = parse_exp();

	if(tk->type != TAB)
		p_err("incomplete statement, expected TAB");

	return s;
}

struct exp *parse_exp(){

	struct exp *e;

	//parse digit
	//determine type
	if(tk->type != INT)
		p_err("return type is not an integer");

	e = malloc(sizeof(struct exp));
	if(e == NULL)
		p_err("unable to allocate memory for expression");

	e->constant = atoi(tk->tk);

	tk++;

	return e;
	
}


///TODO free all mem assigned structures here
void p_err(char *msg){

	printf("%s\n\n", msg);

	exit(1);
}

