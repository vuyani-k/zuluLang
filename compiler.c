#include "compiler.h"

//https://norasandler.com/2017/11/29/Write-a-Compiler.html

int main(){ 

	FILE *fp;

	fp = fopen("./source.z", "r");

	if(fp == NULL){
		printf("failed to open source code\n");
		return 0;
	}

	printf("compiling...\n\n");

	int num_t = get_no_of_tokens(fp);

	struct token tokens[num_t];

	int parsed;
	struct ast *tree;
	tree = malloc(sizeof(struct ast));
	if(lex(fp, &tokens[0]))
		parsed = parse(&tokens[0], num_t, tree);

	if(parsed)
		gen_asm(tree);

	fclose(fp);

	//TODO free all allocated memory tu!

	return 0;
}

