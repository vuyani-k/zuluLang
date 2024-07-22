#include "gen.h"

char* gen_asm(struct ast *tree){
	printf("generating assembly...\n\n");

	size_t g = sizeof(".globl ");
	size_t fname = strlen(tree->func->name) + 1;
	printf(".globl _%s \n _%s: \n", tree->func->name, 
			tree->func->name);
	printf("movl $%i, %%eax \n ret \n", tree->func->body->stmnt->constant);
}
